#include <stdio.h>
#include <stdlib.h>

#include "linear_list.h"

#define split_line(desc) \
	printf("\n\n-------------------------" #desc "-----------------------\n");  \

typedef __linear_list linear_list;
void test_middle() {
	linear_list *ll = NULL;
	init_list(&ll);
	for(int i = 0; i < 10; i++) {
		ElemType* e = NULL;
		init_elem(&e);
		list_insert(ll, 0, e);
	}

	list_traverse(ll, print_stdout);
	print_val(ll->length, d);

	ElemType* del_val = NULL;
	init_elem(&del_val);
	for(int i = 0; i < 10; i++) {
		list_delete(ll, 0, del_val);
		_list_traverse(ll, print_stdout, "del ");
	}
	print_val(ll->length, d);
	list_traverse(ll, print_stdout);
	
	for(int i = 0; i < 10; i++) {
		ElemType* e = NULL;
		init_elem(&e);
		list_insert(ll, 0, e);
	}
	
	print_val(list_empty(ll), d);
	
	uint32_t len = 0;
	list_length(ll, &len);
	print_val(len, d);

	ElemType* result = NULL;
	init_elem(&result);
	for(int i = 0; i < ll->length; i++) {
		get_elem(ll, i, result);
		print_val(result->next, p);

		prior_elem(ll, result, result);
		print_val(result->next, p);

		next_elem(ll, result, result);
		print_val(result->next, p);
		
		printf("\n");
	}

	free(result);
	_list_traverse(ll, print_stdout, "for_destory");
	destory_list(ll);
	_list_traverse(ll, print_stdout, "for_destory");

}

int main() {
	test_middle();
//	test_base();
//	

//	printf("hello, linear_list\n");
	return 0;
}
