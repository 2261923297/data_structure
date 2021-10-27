#include <stdio.h>
#include <stdlib.h>

#include "linear_list.h"

#define split_line(desc) \
	printf("\n\n-------------------------" #desc "-----------------------\n");  \
//
typedef __linear_list linear_list;
/*
void test_base() {
	__linear_list *ll = NULL;
	printf("base ll = %p\n", ll);
	init_list(&ll);
	printf("init_end\n");

	ElemType result;
	for(int  i = 0; i < 13; i++) {
		list_insert(ll, i, &i);
	}


	clear_list(ll);


	print_val(list_empty(ll), d);

	uint32_t len;
	list_length(ll, &len);
	print_val(len, d);

	for(int  i = 0; i < 13; i++) {
		list_insert(ll, i, &i);
	}

	//get_lem
	split_line(get_elem);
	for(int i = 0; i < 1; i++) {
		get_elem(ll, i, &result);
		print_val(*result.data, d);
	}

	split_line(locate_elem);
	//locate_elep 
	locate_elem(ll, &result, compare);
	
	print_val(*result.data, d);

	split_line(prior_elem);
	//prior_elem
	ElemType* cur = ll->elems - 2;
	for(int i = 0; i < 4; i++) {
		prior_elem(ll, cur + i, &result); // error, error, 0
		print_val(*result.data, d); // error error 0	
	}

	split_line(next_elem);
	//next_elem
	for(int i = ll->length - 2; i < ll->length + 1; i++) {
		next_elem(ll, cur + i + 2, &result);
		print_val(result, d);  //11, error, error;
	}

	split_line(list_delete);
	// list_delete
	for(int i = 0; i < ll->length;) {
		list_delete(ll, i, &result);
		_list_traverse(ll, print_stdout, "delete_)list");
	}
	
	destory_list(ll);
	free(ll);
	printf("-------------test_base------------\n\n\n");
}

void test_crud() {
	linear_list *ll = NULL;
	printf("crud ll = %p\n", ll);
	init_list(&ll);

	for(int i = 0; i < 13; i++) {
		list_insert(ll, i, &i);
	}
	printf("insert result: ");
	list_traverse(ll, print_stdout);
	// delete
	uint32_t len = 0;
	list_length(ll, &len);
	print_val(len, d);

//	for(int i = 0; i <)
	// update
	
	// locate
	free(ll);
}
*/
void test_middle() {
	linear_list *ll = NULL;
	init_list(&ll);
	for(int i = 0; i < 10; i++) {
		ElemType* e = NULL;
		init_elem(&e);
		list_insert(ll, 0, e);
	}

	list_traverse(ll, print_stdout);
	ElemType* del_val = (ElemType*)malloc(sizeof(ElemType));
	init_elem(&del_val);

	for(int i = 0; i < 10; i++) {
		list_delete(ll, 0, del_val);
		_list_traverse(ll, print_stdout, "del ");
	}
	
	list_traverse(ll, print_stdout);
}
int main() {
	test_middle();
//	test_base();
//	

//	printf("hello, linear_list\n");
	return 0;
}
