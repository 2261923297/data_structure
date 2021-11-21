#include "linear_list.h"
#include <inttypes.h>
/*
 * 实现说明
 *
 * 由于大部分返回值为void 
 *     所以需要所有函数实现可靠
 *
 * */

#define EMPTY_RETURN_VALUE(point, rt) \
	if((point) == 0) { \
		printf("[error] %s couldn^t be NULL! \n", #point); \
		return rt; \
	} \

int compare(const ElemType* e) {
	if(*e > 0) return 1;
	else return 0;
}
void set_zero(ElemType* e) { 
	*e = 0; 
 }

void print_stdout(ElemType* e) { printf("%5d, ", *e); }

void init_elem(ElemType** e) {
	if(*e == NULL) {
		*e = (ElemType*)malloc(sizeof(ElemType*));
	}
	set_zero(*e);
}

void init_list(__linear_list **_list) {
	EMPTY_RETURN(_list);
	if(*_list != NULL) {
		printf("[error] liste is defined\n");
		return ;
	}

	*_list = (__linear_list*)malloc(sizeof(__linear_list));
	__linear_list* list = *_list;
	list->length = 0;
	list->size = LIST_INIT_SIZE;
	list->elems = (ElemType*)malloc(sizeof(ElemType) * list->size);
	if(list->elems == NULL) {
		perror("init_list::malloc");
		list->size = list->length = 0;
		return ;
	}
	printf("[info] elems: %p, is created\n", list->elems);
	list_traverse(list, print_stdout);	
}

void destory_list(__linear_list *list) {
	EMPTY_RETURN(list);
	if(list->elems != NULL) {
		printf("[info] elems: %p will be destoried!\n", list->elems);
		free(list->elems);
	}	
	list->elems = NULL;
	list->length = 0;
	list->size = 0;
}

void clear_list(__linear_list *list){
	EMPTY_RETURN(list);
	if(list->elems == NULL) {
		printf("list->elem is NULL, needn^t clear!");
	}
	list->length = 0;
}

int list_empty(const __linear_list* list){
	EMPTY_RETURN_VALUE(list, 1);
	return list->length == 0;
}

void list_length(const __linear_list* list, uint32_t* len){
	EMPTY_RETURN(list);
	*len = list->length;
}
void get_elem(const __linear_list* list, uint32_t i, ElemType* result){
	EMPTY_RETURN(list);
	EMPTY_RETURN(list->elems);
	EMPTY_RETURN(list->length > i);

	*result = *(list->elems + i);
}
void locate_elem(const __linear_list* list, ElemType* result, int compare(const ElemType* e)) {
	EMPTY_RETURN(list);
	EMPTY_RETURN(list->elems);
	EMPTY_RETURN(result);

	for(uint32_t i = 0; i < list->length; i++) {
		if(compare(list->elems + i)) {
			*result = list->elems[i];
			break;
		}
	}
}

void prior_elem(const __linear_list* list, ElemType *cur, ElemType* result) {
	EMPTY_RETURN(list);
	EMPTY_RETURN(list->elems);
	if(result == NULL || cur == NULL) {
		printf("[error] result || cur couldn^t be NULL\n");
		return;
	}
	// void* 4byte    int 4byte 0xff ff ff ff, 
	// cur_addr = 0x ff ff ff ff
	//
	uint64_t cur_addr = (uint64_t)cur, elems_head_addr = (uint64_t)list->elems;

	if(cur_addr <= elems_head_addr || cur_addr > elems_head_addr + sizeof(ElemType) * list->length) {
		printf("[error] error cur_addr || cur_addr have no prior\n");
		return;
	}

	uint64_t cur_index = (cur_addr - elems_head_addr) / sizeof(ElemType);
	*result = list->elems[cur_index - 1];
}

void next_elem(const __linear_list* list, ElemType *cur, ElemType* result) {
	EMPTY_RETURN(list);
	EMPTY_RETURN(list->elems);
	if(result == NULL || cur == NULL) {
		printf("[error] result || cur couldn^t be NULL\n");
		return;
	}
	uint64_t cur_addr = (uint64_t)cur, elems_head_addr = (uint64_t)list->elems;
	printf("elems_head_addr = %" PRIu64 ",  ", elems_head_addr);
	printf("cur_addr = %" PRIu64 "\n", cur_addr);
	if(cur_addr < elems_head_addr || cur_addr >= elems_head_addr + sizeof(ElemType) * list->length) {
		printf("[error] error cur_addr || cur_addr have no next\n");
	}
	uint64_t cur_index = (cur_addr - elems_head_addr) / sizeof(ElemType);
	*result = list->elems[cur_index + 1];
}

int reset(__linear_list* list) {
	EMPTY_RETURN_VALUE(list, 0);
	// elems  = list->elems
	// list->elems = rellac(list->size + LIST_INCREAMENT);
	printf("[fatal] reset falure, need define reset!\n");
	return 0;
}
void list_insert(__linear_list* list, uint32_t i, ElemType* e) {
	EMPTY_RETURN(list);
	EMPTY_RETURN(e);
	EMPTY_RETURN(list->elems);

	if(list->length >= list->size) {
		EMPTY_RETURN(reset(list));	
	}
	if(i > list->length) {
		printf("[error] you need control that i <= list->length = %d\n", list->length);
		return;
	}
	for(uint32_t j = list->length; j > i; j--) {
		list->elems[j] = list->elems[j - 1];
	}
	list->elems[i] = *e;
	list->length++;
}

void list_delete(__linear_list* list, uint32_t i, ElemType* delete_val) {
	EMPTY_RETURN(list);
	EMPTY_RETURN(delete_val);
	EMPTY_RETURN(list->elems);
	EMPTY_RETURN(list->length);

	*delete_val = list->elems[i];
	for(uint32_t j = i; j < list->length; j++) {
		list->elems[j] = list->elems[j + 1];
	}
	list->length--;
}

void _list_traverse(__linear_list* list, void visit(ElemType* e), const char* profix) {
	EMPTY_RETURN(list);
	EMPTY_RETURN(list->elems);

	printf("list_traverse, %s: \n", profix);
	for(uint32_t i = 0; i < list->length; i++) {
		visit(list->elems + i);
	}

	printf("\n");
}


