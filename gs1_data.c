#include "gs1.h"
#include <string.h>
#include <stdio.h>

int gs1_data_size(gs1_data_elem_t *list) {
	if (list->type == gs1_data_elemtype_string) {
		return strlen(list->string) + strlen("\"\" ");
	} else if (list->type == gs1_data_elemtype_list) {
		int size = strlen(" [ ") + strlen(" ] ");
		for (int i=0; i<(list->nsub); i++) {
			size += gs1_data_size(&(list->sub[i]));
		}
		return size;
	}
}

void gs1_data_encode(gs1_data_elem_t *list, char* data) {
	if (list->type == gs1_data_elemtype_string) {
		sprintf(data, "\"%s\" ", list->string);
	} else if (list->type == gs1_data_elemtype_list) {
		int offset = 0;
		sprintf(data, " [ ");
		offset += strlen(" [ ");
		for (int i=0; i<(list->nsub); i++) {
			gs1_data_encode(&(list->sub[i]), data+offset);
			offset += gs1_data_size(&(list->sub[i]));
		}
		sprintf(data+offset, " ] ");
	}
}


