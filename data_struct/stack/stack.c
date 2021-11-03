#include "stack.h"

st_t* stack_create(st_t* st, size_t capacity) {
	if(st->elems != NULL) {
		free(st->elems);
	}
	st->elems = (elem_t*)malloc(sizeof(elem_t) * capacity);

	st->len = 0;
	st->capacity = capacity;

	return st;

}
st_t* stack_recreate(st_t* st, size_t capacity) {
	if(st == NULL) {
		printf("[error] stack_recreate: st can^t be NULL\n");
		return st;
	}
	if(st->elems == NULL) {
		printf("[error] stack_recreate: st->elems can^t be NULL\n");
		return st;
	}
	// 申请新的空间
	st->capacity += 8;
	elem_t* new_elems = (elem_t*)malloc(sizeof(elem_t) * st->capacity);

	// 复制原值
	for(size_t i = 0; i < st->len; i++) {
		new_elems[i] = st->elems[i];
	}

	// 释放原空间
	free(st->elems);

	// 新旧替换
	st->elems = new_elems;

}
void stack_destory(st_t* st) {
	free(st->elems);
	st->elems = NULL;
	st->len = 0;
	st->capacity = 0;
}

bool stack_empty(st_t* st) {
	return st->len == 0;
}
size_t stack_len(st_t* st) {
	return st->len;
}
size_t stack_capacity(st_t* st) {
	return st->capacity;
}

// 0: 全部执行成功, other: visit失败的index
uint32_t stack_traverse(st_t* st, bool visit(elem_t* elem), const char* profix) {
	uint32_t ret = 0;
	printf("stack_traverse: %s\n", profix);
	for(size_t i = 0; i < st->len; i++) {
		ret = visit(st->elems + i);
		if(ret == false) {
			ret = (uint32_t)i;
			break;
		}
	}
	printf("\n");
	return ret;
}

void stack_push(_stack* s, elem_t* e) {
	EMPTY_RETURN(s);
	EMPTY_RETURN(s->ss);
	EMPTY_RETURN(s->bo);
	EMPTY_RETURN(e);
	EMPTY_RETURN(s->ss->elems);
	
	printf("push_beg\n");
	if(s->bo->len(s->ss) >= s->bo->capacity(s->ss)) {
		s->bo->recreate(s->ss, s->bo->capacity(s->ss));
	}
	s->ss->elems[s->ss->len] = *e;
	s->ss->len++;
}
void stack_pop(_stack* s, elem_t* e) { 
	EMPTY_RETURN(s);
	EMPTY_RETURN(s->ss);
	EMPTY_RETURN(s->bo);
	EMPTY_RETURN(e);
	EMPTY_RETURN(s->ss->elems);
	
	*e = s->ss->elems[s->ss->len - 1];
	s->ss->len--;
}

