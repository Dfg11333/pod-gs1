#include "gs1.h"
#include <stdlib.h>
#include <stdio.h>

void gs1_PrepareServerList(struct GS1ArenaPacket *reply, int *data_size_ptr, char **data_ptr) {
	reply->MsgID = GS1ArenaMsgID_ServerList;
	gs1_data_elem_t serv_elems[4];
	for (int i=0; i<4; i++) {
		serv_elems[i].type = gs1_data_elemtype_string;
	}
	serv_elems[0].string = "GS-1";
	serv_elems[1].string = "DDDD";
	serv_elems[2].string = malloc(5);
	sprintf(serv_elems[2].string, "%d", gs1_server_clients);
	serv_elems[3].string = "0"; /* Ping limit */
	gs1_data_elem_t serv = { .type = gs1_data_elemtype_list, .sub = serv_elems, .nsub = 4 };
	gs1_data_elem_t gs1_data = { .type = gs1_data_elemtype_list, .sub = &serv, .nsub = 1 };
	int data_size = gs1_data_size(&gs1_data) + 1 /* \0 */;
	char *data = malloc(data_size);
	gs1_data_encode(&gs1_data, data);
	*data_size_ptr = data_size;
	*data_ptr = data;
}

void gs1_PrepareSuccessSconnect(struct GS1ArenaPacket *reply, int *data_size_ptr, char **data_ptr) {
	reply->MsgID = GS1ArenaMsgID_Success;
	gs1_data_elem_t root_elems[2];
	gs1_data_elem_t serv_elems[4];
	gs1_data_elem_t player_elems[5];

	root_elems[0].type = gs1_data_elemtype_string;
	root_elems[0].string = "4";
	
	root_elems[1].type = gs1_data_elemtype_list;
	root_elems[1].sub = serv_elems;
	root_elems[1].nsub = 4;
	
	serv_elems[0].type = gs1_data_elemtype_string;
	serv_elems[0].string = "127.0.0.1";
	
	gs1_data_elem_t gs1_data = { .type = gs1_data_elemtype_list, .sub = root_elems, .nsub = 2 };
        int data_size = gs1_data_size(&gs1_data) + 1 /* \0 */;
        char *data = malloc(data_size);
        gs1_data_encode(&gs1_data, data);
        *data_size_ptr = data_size;
        *data_ptr = data;
}
