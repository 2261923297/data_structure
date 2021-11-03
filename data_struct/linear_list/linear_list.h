#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "linear_list_type.h"
#ifndef data_t
#define data_t int
#endif // ElemType

#include "elem_types.h"

#ifndef ElemType 
#define ElemType int  
#endif

struct __linear_list {
	ElemType*  elems;
	uint32_t length;
	uint32_t size;
};

#define LIST_INIT_SIZE 12
#define LIST_INCREMENT 4 * 32

#define print_val(val, type) \
	printf("[info] " #val " = %" #type " \n", val);

#define list_traverse(list, func) _list_traverse(list, func, #func)

#define EMPTY_RETURN(val)  \
	if(val == 0) { \
		printf("[error] %s:%d { %s } can^t be 0\n", __FILE__, __LINE__, #val);	\
		return; \
	}

typedef struct __linear_list  __linear_list;

void init_list(__linear_list **list);
void destory_list(__linear_list *list);
void clear_list(__linear_list *list);

int list_empty(const __linear_list* list);
void list_length(const __linear_list* list, uint32_t *len);

void get_elem(const __linear_list* list, uint32_t i, ElemType*esult); 
void locate_elem(const __linear_list* list, ElemType* result, int compare(const ElemType* e));
void prior_elem(const __linear_list* list, ElemType *cur, ElemType* result);
void next_elem(const __linear_list* list,  ElemType *cur, ElemType* result);
void list_insert(__linear_list* list, uint32_t i, ElemType* e);
void list_delete(__linear_list* list, uint32_t i, ElemType* delete_val);
void _list_traverse(__linear_list* list, void visit(ElemType* e), const char* profix);

int compare(const ElemType* e);
void set_zero(ElemType* e);
void print_stdout(ElemType* e);

void init_elem(ElemType** e);

