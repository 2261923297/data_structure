#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "elem_type.h"
#include "util.h"

#ifndef data_t 
#define data_t int
#endif


#ifndef elem_t

	#ifdef STORAGE_LINK
		#define elem_t link_node_t 
	#else 
		#define elem_t data_t
	#endif

#endif

// 底层数据
typedef struct __link_node {
	data_t* data;
	struct  __link_node* prior;
	struct  __link_node* next;
} link_node_t;

// 存储
typedef struct __queue_st {
	elem_t* head;
	elem_t* peer;

	size_t len;
	size_t cap;

} queue_st;

// 基本操作
typedef struct __queue_bo {
	void (*init_st)(struct __queue_bo* bo, queue_st* st);
	void (*init_elem)(elem_t* elem, data_t* data);

	bool (*empty)(queue_st* st);
	void (*add)(queue_st* st, size_t index, data_t* data);
	void (*del)(queue_st* st, size_t index, data_t* data);
	void (*update)(queue_st* st, size_t index, data_t* data);
	int  (*find)(queue_st* st, bool cmp(data_t*), data_t* data);
	elem_t* (*posi)(queue_st* st, size_t index);

	void (*traverse)(queue_st* st, void visit(data_t* data), const char* profix);
} queue_bo;

// 封装
typedef struct queue {
	queue_st*     st;
	queue_bo*	  bo;

	void (*push)(struct queue* queue, data_t* rt);
	void (*pop) (struct queue* queue, data_t* val);
	int (*top) (struct queue* queue, data_t* rt);
	
} queue_t;


// 初始化模块， 绑定函数
void init_queue(queue_t* t, void init_st(struct __queue_bo *bo, queue_st* st), void init_bo(queue_bo* bo));
void bind_queue(queue_t* q);
void init_qbo(queue_bo* bo);
void init_qst_array(struct __queue_bo* bo, queue_st* st); 
void init_qst_link(struct __queue_bo* bo, queue_st* st);
void init_elem_array(elem_t* elem, data_t* data); // array
void init_elem_link(elem_t* elem, data_t* data);  // link

// queue 需求模块
void queue_push(queue_t* q, data_t* val);
void queue_pop(queue_t* q, data_t* rt);
int  queue_top(queue_t* st, data_t* rt);


// array_op 模块
bool array_empty(queue_st* st);
elem_t* array_posi(queue_st* st, size_t index);

void array_add(queue_st* st, size_t index, data_t* data);
void array_del(queue_st* st, size_t index, data_t* data);
void array_update(queue_st* st, size_t index, data_t* data);
int  array_find(queue_st* st, bool cmp(data_t*), data_t* data);
void array_traverse(queue_st* st, void visit(data_t* data), const char* profix);


// link_op 模块 
bool link_empty(queue_st* st);
elem_t* link_posi(queue_st* st, size_t index);

void link_add(queue_st* st, size_t index, data_t* data);
void link_del(queue_st* st, size_t index, data_t* data);
void link_update(queue_st* st, size_t index, data_t* data);
int  link_find(queue_st* st, bool cmp(data_t*), data_t* data);
void link_traverse(queue_st* st, void visit(data_t* data), const char* profix);



// callbake 模块
void print_stdout(data_t* elem);
bool find_top_cb(data_t* data);

