#include "gs1.h"
#include <stdlib.h>

void gs1_PrepareSuccessPassword(struct GS1ArenaPacket *reply, int *data_size_ptr, char **data_ptr) {
	reply->MsgID = GS1ArenaMsgID_Success;
	gs1_data_elem_t str_struct = { .type = gs1_data_elemtype_string, .string= "74" };
	gs1_data_elem_t gs1_data = { .type = gs1_data_elemtype_list, .sub = &str_struct, .nsub = 1 };
	int data_size = gs1_data_size(&gs1_data) + 1;
	char *data = malloc(data_size);
	gs1_data_encode(&gs1_data, data);
	*data_size_ptr = data_size;
	*data_ptr = data;
}

void gs1_PrepareStillAlive(struct GS1ArenaPacket *reply, int *data_size_ptr, char **data_ptr) {
	reply->MsgID = GS1ArenaMsgID_StillAlive;
	*data_size_ptr = 1;
	*data_ptr = malloc(*data_size_ptr);
	(*data_ptr)[0] = '\0';
}
