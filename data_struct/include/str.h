#pragma once

#include <stdint.h>
#include "final_link.h"

#define size_t uint64_t 

#ifndef data_t 
#define data_t int
#endif // data_t

/*
#ifndef elem_t 
#define elem_t data_t
#endif // elem_t
*/
// data + save_struct = elem
//
// user: elem_t
//
// programer: data
//

/**
 *	data_t: uintxx_t, float, double
 *	data_bo: add, del, update, find
 *
 *  elem_t: link, array, tree{ for search }, graph { for real }
 *			data_t + struct_run_in_memory
 *	elem_bo: base_on_need
 *
 * */

/**
 *	question: static __strbo_mapper* STRBO_MAPPER init default
 *	
 * */

#define TYPE_NUMBER_ARRAY 0
#define TYPE_NUMBER_LINK 1

// link_data_t
typedef struct __link_data {
	link_t link;
	data_t* datas;

	size_t len;
	size_t cap;
} link_data_t;

// link_elem
typedef struct __link_str {
	link_data_t* head;
	link_data_t* peer;

	size_t data_size;
} link_str_s;

// array_elem
typedef struct __array_str {
	data_t* datas;
	size_t cap;
} array_str_s;


typedef struct __str_st {
	void *elems;
	
	size_t len;
	size_t elem_size;
	size_t type_number;
	size_t n_link;
	link_o* link_bo;
} str_s;

typedef struct __str_bo {
	size_t type_number; //use for strbo_mapper
	size_t elem_size;		// use for str_bo->create(, sizeof(str_st), )
	// old_str = NULL, init, not_bull assign
	void (*create)(str_s* new_str, size_t elem_size, size_t type_number);
	void (*destory)(str_s* ss);

	size_t (*len)(str_s* ss);

	void (*add)(str_s* ss, size_t index, data_t* data);
	void (*del)(str_s* ss, size_t index, data_t* data);
	void (*update)(str_s* ss, size_t index, data_t* data);
	void (*find)(str_s* ss, size_t index, data_t* data);
	
	void (*traverse)(str_s* ss, void (*work)(data_t*), const char* profix);
} str_o;

typedef struct __str_ap {
	str_o* bo;
	str_s* st;

	void (*assign) (struct __str_ap* str, data_t* datas, size_t data_size);
	void (*copy) (struct __str_ap* str, struct __str_ap* elems);
	int  (*compare)(struct __str_ap* self, struct __str_ap* other);

	int  (*empty) (struct __str_ap* str);
	void (*length)(struct __str_ap* str, size_t* ans);
	void (*index) (struct __str_ap* str, data_t* data, size_t* ans);

	void (*sub)   (struct __str_ap* str, size_t index, size_t len, struct __str_ap* ans);
	void (*concat)(struct __str_ap* head, struct __str_ap* peer);
	void (*clear) (struct __str_ap* str);

} str_mg;

typedef struct __strbo_mapper {
	struct __str_bo bos[16];

	struct __str_bo* (*get)(struct __strbo_mapper* sm, size_t bo_type);
	void (*add)(struct __strbo_mapper* sm, size_t bo_type, struct __str_bo* bo);
} strbo_mapper_t;

void init_str_ap(str_mg** sm, strbo_mapper_t** smp, size_t type_number);


struct __str_bo* strbo_mapper_get(struct __strbo_mapper* sm, size_t bo_type);
void stbo_mapper_add(struct __strbo_mapper* sm, size_t bo_type, struct __str_bo* bo);


void INIT_STR_BO_MAPPER(struct __strbo_mapper** sm);   // only run once;
static void INIT_LINK_STR_BO(struct __str_bo* bo);
static void INIT_ARRAY_STR_BO(struct __str_bo* bo);


void str_array_create(str_s* new_str, size_t elem_size, size_t type_number);
void str_array_destory(str_s* ss);

size_t str_len(str_s* ss);
size_t str_cap(str_s* ss);

void str_array_add(str_s* ss, size_t index, data_t* data);
void str_array_del(str_s* ss, size_t index, data_t* data);
void str_array_update(str_s* ss, size_t index, data_t* data);
void str_array_find(str_s* ss, size_t index, data_t* data);
void str_array_traverse(str_s* ss, void (*work)(data_t*), const char* profix);


void str_link_create(str_s* new_str, size_t elem_size, size_t type_number);
void str_link_destory(str_s* ss);

size_t str_len(str_s* ss);
size_t str_cap(str_s* ss);

void str_link_add(str_s* ss, size_t index, data_t* data);
void str_link_del(str_s* ss, size_t index, data_t* data);
void str_link_update(str_s* ss, size_t index, data_t* data);
void str_link_find(str_s* ss, size_t index, data_t* data);
void str_link_traverse(str_s* ss, void (*work)(data_t*), const char* profix);


void str_assign (str_mg* str, data_t* elems, size_t size);
void str_copy (str_mg* str, str_mg* other);
int  str_compare(str_mg* self, str_mg* other);

int  str_empty (str_mg* str);
void str_length(str_mg* str, size_t* ans);
void str_index (str_mg* str, data_t* data, size_t* ans);

void str_sub   (str_mg* str, size_t index, size_t len, str_mg* ans);
void str_concat(str_mg* head, str_mg* peer);
void str_clear (str_mg* str);

