#include "gs1.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>

#define PORTNUM 18723

#define MAX_CLIENTS 1024

int gs1_server_clients;

typedef struct {
	pthread_t thread;
	int socket;
}client_t;

void* session(void *socket_ptr);

int main() {
	client_t clients[MAX_CLIENTS];
	gs1_server_clients = 0;

	int client = 0;
	struct sockaddr_in dest;
	struct sockaddr_in serv;
	int serv_socket = socket(AF_INET, SOCK_STREAM, 0);
	int sock_size = sizeof(struct sockaddr_in);
	memset(&serv, 0, sizeof(serv));
	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = INADDR_ANY;
	serv.sin_port = htons(PORTNUM);

	bind(serv_socket, (struct sockaddr *)&serv, sizeof(struct sockaddr));

	listen(serv_socket, 1);
	printf("GS1 Router ready, waiting for connections on port %d\n", PORTNUM); 
	while (client < MAX_CLIENTS) {
		clients[client].socket = accept(serv_socket, (struct sockaddr *)&dest, &sock_size);
		printf("Connected from %s\n", inet_ntoa(dest.sin_addr));
		pthread_create(&(clients[client].thread), NULL, session, &(clients[client].socket));
		client++;
	}
	return 0;
}

void dump_message(int sock, struct GS1ArenaPacket header, char *data) {
	printf("(%d)/%d [%d][%d]%s <%s>\n", ntohs(header.Size), header.IsGameMsg, header.Source, header.Target, ArenaMsgTxt[header.MsgID], data);
}

#define CHECK_READ(s) \
	if (s <= 0) { \
		if (s == 0) { \
			printf("Connection closed\n"); \
		} else { \
			perror("Read"); \
		} \
		pthread_exit(NULL); \
		return NULL; \
	}

void* session(void *socket_ptr) {
	int socket = *((int*)socket_ptr);
	struct GS1ArenaPacket header;
	char data[1024];
	ssize_t size;
	uint16_t hsize, dsize;
	while (1) {
		int offset = 0;
		do {
			size = read(socket, ((char*)&header)+offset, sizeof(struct GS1ArenaPacket) - offset);
			CHECK_READ(size);
			offset += size;
			if (offset < sizeof(struct GS1ArenaPacket)) {
				usleep(100);
			} else {
				break;
			}
		} while (1);
		offset = 0;
		hsize = ntohs(header.Size);
		dsize = hsize - sizeof(struct GS1ArenaPacket);
		do {
			size = read(socket, data+offset, dsize - offset);
			CHECK_READ(size);
			offset += size;
			if (offset < dsize) {
				usleep(100);
			} else {
				break;
			}
		} while (1);

		dump_message(socket, header, data);

		struct GS1ArenaPacket reply = { .Reserved = 0, .IsGameMsg = 0 };
		int reply_size = sizeof(struct GS1ArenaPacket);
		reply.Source = GS1ArenaMsgEP_Router;
		reply.Target = GS1ArenaMsgEP_Client;
		char *data;
		int data_size;

		switch(header.MsgID) {
			case GS1ArenaMsgID_StillAlive:
				gs1_PrepareStillAlive(&reply, &data_size, &data);
				break;
			case GS1ArenaMsgID_CheckPassword:
				gs1_PrepareSuccessPassword(&reply, &data_size, &data);
				break;
			case GS1ArenaMsgID_GetLastNews:
				gs1_PrepareNews(&reply, &data_size, &data);
				break;
			case GS1ArenaMsgID_GetServers:
				gs1_PrepareServerList(&reply, &data_size, &data);
				break;
			case GS1ArenaMsgID_ConnectionRequest:
				gs1_PrepareSuccessSconnect(&reply, &data_size, &data);
			default:
				printf("Message %s : not implemented\n", ArenaMsgTxt[header.MsgID]);
				/* Ignore */
			case GS1ArenaMsgID_GetRouters:
			case GS1ArenaMsgID_Connect:
				continue;
		}
		reply_size += data_size;
		reply.Size = htons(reply_size);
		dump_message(socket, reply, data);
		write(socket, &reply, sizeof(struct GS1ArenaPacket));
		write(socket, data, data_size);
		free(data);
	}
	return NULL;
}
