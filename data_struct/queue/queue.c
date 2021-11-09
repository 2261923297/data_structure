#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "queue.h"

void init_queue(queue_t* q
		, void init_st(struct __queue_bo *bo, queue_st* st)
		, void init_bo(queue_bo* bo))
{
	EMPTY_RETURN(q->st == NULL);
	q->st = (queue_st*)malloc(sizeof(queue_st));
	q->bo = (queue_bo*)malloc(sizeof(queue_bo));


	init_bo(q->bo);
	init_st(q->bo, q->st);
}

void bind_queue(queue_t* q) {	
	q->push = &queue_push;
	q->pop = &queue_pop;
	q->top = &queue_top;
}

void init_qst_array(struct __queue_bo* bo, queue_st* st) {
	data_t d;
	const size_t capacity = 5;
	memset(&d, 0, sizeof(d));
	st->head = (elem_t*)malloc(sizeof(data_t) * capacity);
	st->peer = NULL;

	st->len = 0;
	st->cap = capacity;
} 
void init_qbo(queue_bo* bo) {
	if(sizeof(elem_t) == sizeof(link_node_t)) {
		bo->init_st = &init_qst_link;
		bo->init_elem = &init_elem_link;

		bo->posi = &link_posi;
		bo->add = &link_add;
		bo->del = &link_del;
		bo->empty = &link_empty;
		bo->update = &link_update;
		bo->find = &link_find;

		bo->traverse = &link_traverse;

	} else {
		bo->init_st = &init_qst_array;
		bo->init_elem = &init_elem_array;

		bo->posi = &array_posi;
		bo->add = &array_add;
		bo->del = &array_del;
		bo->empty = &array_empty;
		bo->update = &array_update;
		bo->find = &array_find;

		bo->traverse = &array_traverse;

	}


}



void queue_push(queue_t* q, data_t* val) {
	q->bo->add(q->st, q->st->len, val);
}
void queue_pop (queue_t* q, data_t* rt) {
	q->bo->del(q->st, 0, rt);
}
int queue_top(queue_t* q, data_t* rt) {
	EMPTY_RETURN_VAL(q, -1);
	EMPTY_RETURN_VAL(rt, -1);

	if(q->bo->empty(q->st)) {
		printf("queue is empty, can^t get top\n");
		return -1;
	}
	q->bo->find(q->st, find_top_cb, rt);
	return true;
}



void init_elem_array(elem_t* elem, data_t* data) {
	EMPTY_RETURN((elem && data));

	int size = sizeof(data_t);
	size_t i = 0;
	for(i = 0; i < size; i++) {
		((char*)(elem))[i] = ((char*)data)[i];
	}

	// if link		
	int elem_size = sizeof(elem_t);
	for(size_t j = i; j < elem_size; j++) {
		((char*)(elem))[i] = 0;
	}
}
bool array_empty(queue_st* st) {
	EMPTY_RETURN_VAL(st, false);
	return st->len == 0;
}
elem_t* array_posi(queue_st* st, size_t index) {
	return st->head + index;
}
void array_add(queue_st* st, size_t index, data_t* data) {
	EMPTY_RETURN(st);
	EMPTY_RETURN(index <= st->len);
	EMPTY_RETURN(data);
	EMPTY_RETURN(st->cap > st->len);

	for(size_t i = st->len; i > index; i--) {
		st->head[i] = st->head[i - 1];
	}
	((data_t*)(st->head))[index] = *data;
	st->len++;
}
void array_del(queue_st* st, size_t index, data_t* data) {
	EMPTY_RETURN(st);
	EMPTY_RETURN(index <= st->len);
	EMPTY_RETURN(data);
	EMPTY_RETURN(st->cap >= st->len);

	*data = ((data_t*)(st->head))[index];
	for(size_t i = index; i < st->len - 1; i++) {
		st->head[i] = st->head[i + 1]; 
	}
	st->len--;
}
void array_update(queue_st* st, size_t index, data_t* data) {
	EMPTY_RETURN(st);
	EMPTY_RETURN(index <= st->len);
	EMPTY_RETURN(data);
	
	((data_t*)(st->head))[index] = *data;
}
int array_find(queue_st* st, bool cmp(data_t*), data_t* data) {
	EMPTY_RETURN_VAL(st, -1);
	EMPTY_RETURN_VAL(data, -1);
	for(size_t i = 0; i < st->len; i++) {
		if(cmp((data_t*)st->head + i)) {
			*data = ((data_t*)(st->head))[i];
		}
		return i;
	}
	return -1;
}
void array_traverse(queue_st* st, void visit(data_t* data), const char* profix) {
	printf("queue_traverse: %s\n", profix);
	for(size_t i = 0; i < st->len; i++) {
		visit((data_t*)st->head + i);
	}
	printf("\n");
}
void print_stdout(data_t* data) {
	printf("%d, ", *data);
}



void init_qst_link(struct __queue_bo* bo, queue_st* st) {
	st->head = (elem_t*)malloc(sizeof(elem_t)); 
	st->peer = (elem_t*)malloc(sizeof(elem_t)); 

	link_node_t *head = (link_node_t*)st->head, 
				*peer = (link_node_t*)st->peer;
	
	head->data = peer->data = NULL;
	head->prior = NULL;
	peer->next = NULL;
	head->next = peer;
	peer->prior = head;

	st->len = 0;
	st->cap = -1;


}
void init_elem_link(elem_t* _elem, data_t* data) {
	EMPTY_RETURN(_elem);
	EMPTY_RETURN(data);

	link_node_t* elem = (link_node_t*)_elem;
	elem->data = (data_t*)malloc(sizeof(data_t));
	*elem->data = *data;
	elem->next = NULL;
	elem->prior = NULL;
}
bool link_empty(queue_st* st) {
	return st->len == 0;
}
void show_link_node(link_node_t* ln, const char* profix) {
	printf("[info] %s:%d> %s:\t", __FILE__, __LINE__, profix);
	printf("ln = %p, data = %p, prior = %p, next = %p\n", ln, ln->data, ln->prior, ln->next);
}
elem_t* link_posi(queue_st* st, size_t index) {
	EMPTY_RETURN_VAL(st, NULL);
	EMPTY_RETURN_VAL(index <= st->len, NULL);
	EMPTY_RETURN_VAL(index >= 0, NULL);

	size_t peer_dis = st->len - index;
	size_t dist = 0;
	link_node_t* ans = NULL;

	if(peer_dis < index) {
		dist = peer_dis + 1;
		ans = (link_node_t*)st->peer;
		while(dist--) {
			ans = ans->prior;
		}
	} else {
		dist = index;
		ans = (link_node_t*)st->head;
		while(dist--) {
			ans = ans->next;
		}
	}
	return (elem_t*)ans;
}
void link_add(queue_st* st, size_t index, data_t* data) {
	EMPTY_RETURN(data);

	link_node_t* posi = (link_node_t*)link_posi(st, index);
	EMPTY_RETURN(posi);

	link_node_t* ln_data = (link_node_t*)malloc(sizeof(link_node_t));
	ln_data->data = (data_t*)malloc(sizeof(data_t));
	*ln_data->data = *data;
	ln_data->next = ln_data->prior = NULL;
	
	ln_data->next = posi->next; 
	ln_data->prior = posi;

	posi->next->prior = ln_data;
	posi->next = ln_data;

	st->len++;
}
void link_del(queue_st* st, size_t index, data_t* data) {
	EMPTY_RETURN(data);
	
	link_node_t* posi = (link_node_t*)link_posi(st, index);
	posi = posi->next;
	EMPTY_RETURN(posi);

	posi->prior->next = posi->next;
	posi->next->prior = posi->prior;
	free(posi->data);
	free(posi);	

	st->len--;
}
void link_update(queue_st* st, size_t index, data_t* data) {
	EMPTY_RETURN(data);
	
	link_node_t* posi = (link_node_t*)link_posi(st, index);
	EMPTY_RETURN(posi);

	*posi->data = *data;
}
int  link_find(queue_st* st, bool cmp(data_t*), data_t* data) {
	EMPTY_RETURN_VAL(st, -1);
	EMPTY_RETURN_VAL(data, -1);
	size_t len = st->len;
	link_node_t* ln = ((link_node_t*)(st->head))->next;
	for(int i = 0; i < len; i++) {
		if(cmp(ln->data)) {
			*data = *ln->data; 
			return i;
		}
		ln = ln->next;
	}


	return -1;
}
void link_traverse(queue_st* st, void visit(data_t* data), const char* profix) {
	printf("[info] %s:%d link_traverse: \n", __FILE__, __LINE__);
	EMPTY_RETURN(st);
	size_t len = st->len;
	link_node_t* ln = ((link_node_t*)(st->head))->next;
	print_val(st->len, lu);
	for(int i = 0; i < len; i++) {
		visit(ln->data);
		ln = ln->next;
	}
	printf("\n");
}

bool find_top_cb(data_t* data) { return true; }




