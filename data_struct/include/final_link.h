#pragma once

#include "util.h"


#ifndef data_t 
#define data_t int
#endif // data_t

typedef struct __final_link_st {
	struct __final_link_st* next;
	struct __final_link_st* prior;
} link_t;

typedef struct __link_base_operator {
	void (*init)(link_t** link);
	void (*add)(link_t* link, link_t* which);
	void (*del)(link_t* link);
	void (*update)(link_t* link, link_t* which);
	void (*find)(link_t* head, size_t index, link_t** ans);
} link_o;

void _link_init(link_t** link);
void _link_add(link_t* link, link_t* which);
void _link_del(link_t* link);
void _link_update(link_t* link, link_t* which);
void _link_find(link_t* head, size_t index, link_t** ans);

void bind_link_bo(link_o* lbo);

