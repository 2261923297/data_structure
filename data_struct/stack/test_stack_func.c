#include "stack.h"
#include <stdio.h>

#define traverse(st, func) \
	(st)->bo->traverse((st)->ss, func, #func);
bool print_stdout(elem_t* e) {
	printf("%d, ", *e);
}
void init_stack(_stack* st, size_t capacity) {
	printf("init_beg\n");
	st->ss = (__stack_st*)malloc(sizeof(__stack_st));
	st->bo = (__stack_op*)malloc(sizeof(__stack_op));
	st->ss->elems = NULL;

	st->push = &stack_push;
	st->pop = &stack_pop;
	st->bo->create = &stack_create;
	st->bo->recreate = &stack_recreate;
	st->bo->destory = &stack_destory;

	st->bo->empty = &stack_empty;
	st->bo->len = &stack_len;
	st->bo->capacity = &stack_capacity;
	st->bo->traverse = &stack_traverse;

	st->bo->create(st->ss, capacity);
	printf("init_end\n");
}

void show_data(_stack* st) {
	
}
void test_base() {
	printf("base_beg\n");
	_stack st;
	
	init_stack(&st, 8);
	for(int i = 0; i < 20; i++) {
		st.push(&st, &i);
		traverse(&st, print_stdout);
	}

	elem_t elem;
	/*
	for(int i = 1; i < 20; i++) {
		st.pop(&st, &elem);
		printf("\npop_elem = %d, ", elem);
		traverse(&st, print_stdout);
	}
	*/
}
int main() {
	printf("hello stack!\n");
	test_base();
	return 0;
}
