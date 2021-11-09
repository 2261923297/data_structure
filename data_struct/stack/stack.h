#pragma once
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

#include "macro.h"
#define elem_t int
/**
 *	__stack_st      // 存储层
 *	__stack_b_op	// 基操层 crud
 *	_stack			// 应用层 // 封装层
 *
 * */

typedef struct stack_structure {
	elem_t* elems;
	size_t  len;
	size_t  capacity;

} __stack_st;

#ifndef st_t 
#define st_t __stack_st
#endif 
typedef struct base_operation {
	st_t* (*create)(st_t *st, size_t capacity);
	st_t* (*recreate)(st_t *st, size_t capacity);
	void  (*destory)(st_t* st);
	
	bool (*empty)(st_t* st);
	size_t (*len)(st_t* st);
	size_t  (*capacity)(st_t* st);

	// 0: 全部执行成功, other: visit失败的index
	// visit 没有异常反回0, 有异常反回errno
	uint32_t (*traverse)(st_t* st, bool visit(elem_t* elem), const char* profix);
	
} __stack_op;


typedef struct _stack {
	__stack_st		*ss;
	__stack_op       *bo;
	
	void (*push)(struct _stack* s, elem_t* e);
	void (*pop)(struct _stack* s, elem_t* e);

} _stack;

//static void StackInit(stack* s);

st_t* stack_recreate(st_t* st, size_t capacity);
st_t* stack_create(st_t* st, size_t capacity);
void stack_destory(st_t* st);

bool stack_empty(st_t* st);
size_t stack_len(st_t* st);
size_t stack_capacity(st_t* st);

// 0: 全部执行成功, other: visit失败的index
uint32_t stack_traverse(st_t* st, bool visit(elem_t* elem), const char* profix);

void stack_push(_stack* s, elem_t* e);
void stack_pop(_stack* s, elem_t* e);

/*
typedef struct stack {
	_stack s;
	
	void create(size_t capacity);
	void destory();

	bool empty();
	uint64_t len();

	void push(elem_t *e);
	void pop(elem_t *e);
	
} stack;

*/
