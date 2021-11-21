#pragma once

#include <stdint.h>


#ifndef data_t  
#error "please define 'data_t' "
#endif

typedef struct link_list {
	data_t* data;	
	struct link_list* next;
	struct link_list* prior;
} link_list;


