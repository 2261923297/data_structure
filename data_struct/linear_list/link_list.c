#include "linear_list.h"
void set_zero(ElemType* e) {
	if(e->data == NULL)
		e->data = (data_t*)malloc(sizeof(data_t));
	*e->data = 0;
	e->next = NULL;
	e->prior = NULL;

}

void init_elem(ElemType** e) {
	if(*e == NULL) 
		*e = (ElemType*)malloc(sizeof(ElemType));

	set_zero(*e);	
}
void print_stdout(ElemType* e) {
	printf("%5d", *e->data);
}

int compare(const ElemType* e) {
	if(*e->data > 0) 
		return 1;
	else 
		return 0;
}
void print_link(ElemType* e) {
	printf("\tdata = %d, next = %p, prior = %p \n", 
			*(e->data), e->next, e->prior);
}


void _init_link_list(link_list* link_node, int data) {
	link_node->data = (int*)malloc(sizeof(int));
	*link_node->data = data;
	link_node->next = NULL;
	link_node->prior = NULL;
}

void init_link_list(link_list* link_node) {
	_init_link_list(link_node, 0);
}

void init_list(__linear_list **_list) {
	EMPTY_RETURN(!*_list);
	*_list = (__linear_list*)malloc(sizeof(__linear_list));
	
	__linear_list* list = *_list; 
	list->elems = (ElemType*)malloc(sizeof(ElemType));
	init_link_list(list->elems);

}


void destory_list(__linear_list *list) {
	
}
void clear_list(__linear_list *list) {

}

int list_empty(const __linear_list* list) {
	
	return 0;

}

void list_length(const __linear_list* list, uint32_t *len) {

}

void get_elem(const __linear_list* list, uint32_t i, ElemType*esult) {

}
void locate_elem(const __linear_list* list, ElemType* result, int compare(const ElemType* e)) {

}
void prior_elem(const __linear_list* list, ElemType *cur, ElemType* result) {

}

void next_elem(const __linear_list* list,  ElemType *cur, ElemType* result) {

}

void list_insert(__linear_list* list, uint32_t i, ElemType* e) {
	EMPTY_RETURN(list);
	EMPTY_RETURN(list->length >= i);

	ElemType *tmp = list->elems, *middle_next = NULL;
	while(i--) {  // index
		tmp = tmp->next;
		EMPTY_RETURN(tmp);
	}

	middle_next = tmp->next;

	tmp->next = e;
	e->next = middle_next;
	e->prior = tmp;

}
void list_delete(__linear_list* list, uint32_t i, ElemType* delete_val) {
	EMPTY_RETURN(list);
	

	ElemType *tmp = list->elems->next, *middle_prior = NULL;
	while(i--) {
		tmp = tmp->next;
		EMPTY_RETURN(tmp);
	}

	*delete_val->data = *tmp->data;
	tmp->prior->next = tmp->next;
	if(tmp->next != NULL)
		tmp->next->prior = tmp->prior;
	
	free(tmp);
//	free(tmp->data);
	tmp = NULL;
}
void _list_traverse(__linear_list* list, void visit(ElemType* e), const char* profix) {
	printf("list_traverse: %s\n", profix);
	ElemType* tmp = list->elems->next;
	while(tmp != NULL) {
		visit(tmp);
		tmp = tmp->next;
	}
	printf("\n");
}

void traver_stdout(__linear_list* list) {
	_list_traverse(list, print_link, "stdout");
		
}

