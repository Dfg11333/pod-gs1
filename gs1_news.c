#include "gs1.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define RMOTD_PATH "router-motd.txt"

void gs1_PrepareNews(struct GS1ArenaPacket *reply, int *data_size_ptr, char **data_ptr) {
	reply->MsgID = GS1ArenaMsgID_News;
	char *text;
	struct stat st;
	int ret = stat(RMOTD_PATH, &st);
	if (ret) { /* File not found / readable / ... */
		text = malloc(1);
		text[0] = '\0';
	} else {
		int filesize = st.st_size;
		int motdfd = open(RMOTD_PATH, O_RDONLY);
		text = malloc(filesize);
		read(motdfd, text, filesize); 
		close(motdfd);
	}
	gs1_data_elem_t str_struct = { .type = gs1_data_elemtype_string, .string= text };
	gs1_data_elem_t gs1_data = { .type = gs1_data_elemtype_list, .sub = &str_struct, .nsub = 1 };
	int data_size = gs1_data_size(&gs1_data) + 1;
	char *data = malloc(data_size);
	gs1_data_encode(&gs1_data, data);
	*data_size_ptr = data_size;
	*data_ptr = data;
}
