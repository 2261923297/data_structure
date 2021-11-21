#include "str.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

struct __str_bo* strbo_mapper_get(struct __strbo_mapper* sm, size_t bo_type) {
	return sm->bos + bo_type;
}
void strbo_mapper_add(struct __strbo_mapper* sm, size_t bo_type, struct __str_bo* bo) {
	sm->bos[bo_type] = *bo;
}

// static void INIT_STR_BO_MAPPER(struct __strbo_mapper** sm);
void INIT_STR_BO_MAPPER(struct __strbo_mapper** sm) {
	if(*sm != NULL) {
		print_info("*sm is inited");
		return;
	}

	*sm = (struct __strbo_mapper*)malloc(sizeof(struct __strbo_mapper));
	memset((*sm)->bos, 0, sizeof((*sm)->bos));

	(*sm)->get = &strbo_mapper_get;
	(*sm)->add = &strbo_mapper_add;

	struct __str_bo array_bo;
	struct __str_bo link_bo;
	INIT_ARRAY_STR_BO(&array_bo);
	INIT_LINK_STR_BO(&link_bo);

	(*sm)->add(*sm, TYPE_NUMBER_ARRAY, &array_bo);
	(*sm)->add(*sm, TYPE_NUMBER_LINK, &link_bo);
}
static void INIT_LINK_STR_BO(struct __str_bo* bo) {
	bo->type_number = TYPE_NUMBER_LINK;
	bo->elem_size = sizeof(struct __link_str);

	bo->create = &str_link_create;  	
	bo->destory = &str_link_destory;

	bo->len = &str_len;

	bo->add = &str_link_add;
	bo->del = &str_link_del;
	bo->update = &str_link_update;
	bo->find = &str_link_find;

	bo->traverse = &str_link_traverse;
}
static void INIT_ARRAY_STR_BO(struct __str_bo* bo) {
	bo->type_number = TYPE_NUMBER_ARRAY;
	bo->elem_size = sizeof(struct __array_str);

	bo->create = &str_array_create;  	
	bo->destory = &str_array_destory;

	bo->len = &str_len;

	bo->add = &str_array_add;
	bo->del = &str_array_del;
	bo->update = &str_array_update;
	bo->find = &str_array_find;

	bo->traverse = &str_array_traverse;
}



void str_array_create(str_s* new_str, size_t elem_size, size_t type_number) {
	EMPTY_RETURN(new_str);
	new_str->elems = malloc(elem_size);
	array_str_s* ass = (array_str_s*)new_str->elems;
	new_str->elem_size = elem_size;
	new_str->type_number = type_number;
	new_str->len = 0;

	ass->datas = malloc(sizeof(data_t) * 32);
	if(type_number == TYPE_NUMBER_ARRAY) {
		ass->cap = 32;
	}
}
void str_array_destory(str_s* ss) {
	ss->elem_size = 0;
	ss->type_number = 0;

	free(ss);
}

// insert = 5~12 len
size_t str_len(str_s* ss) {
	return ss->len;
}

void str_array_add(str_s* ss, size_t index, data_t* data) {
	EMPTY_RETURN(ss);
	EMPTY_RETURN(data);

	array_str_s* ass = (array_str_s*)ss->elems;
	EMPTY_RETURN(ass->cap > index);
	
	for(size_t i = ss->len; i > index; i--) {
		ass->datas[i] = ass->datas[i - 1];
	}
	ass->datas[index] = *data;
	ss->len++;
}
void str_array_del(str_s* ss, size_t index, data_t* data) {
	array_str_s* ass = (array_str_s*)ss->elems;
	EMPTY_RETURN(ss->len > 0);
	EMPTY_RETURN(ss->len > index);

	*data = ass->datas[index];
	for(size_t i = index; i < ss->len - 1; i++) {
		ass->datas[i] = ass->datas[i + 1];
	}
	memset(ass->datas + ss->len, 0, sizeof(data_t));
	
	ss->len--;
}
void str_array_update(str_s* ss, size_t index, data_t* data) {
	array_str_s* ass = (array_str_s*)ss->elems;
	EMPTY_RETURN(ss->len > 0);
	EMPTY_RETURN(ss->len > index);
	
	ass->datas[index] = *data;
}
void str_array_find(str_s* ss, size_t index, data_t* data) {
	array_str_s* ass = (array_str_s*)ss->elems;
	EMPTY_RETURN(ss->len > 0);
	EMPTY_RETURN(ss->len > index);
	
	*data = ass->datas[index];
}

void str_array_traverse(str_s* ss, void (*work)(data_t*), const char* profix) {
	array_str_s* ass = (array_str_s*)ss->elems;
	print_info(profix);
	print_val(ss->len, lu);

	for(size_t i = 0; i < ss->len; i++) {
		work(ass->datas + i);
	}
	printf("\n");
}

void str_link_create(str_s* new_str, size_t elem_size, size_t type_number) {
	EMPTY_RETURN(new_str);
	new_str->elems = malloc(elem_size);
	new_str->len = 0;
	new_str->elem_size = elem_size;
	new_str->type_number = type_number;
	new_str->link_bo = (link_o*)malloc(sizeof(link_o));
	bind_link_bo(new_str->link_bo);

	link_str_s* lss = (link_str_s*)new_str->elems;
	lss->head = (link_data_t*)malloc(sizeof(link_data_t));
	lss->peer = (link_data_t*)malloc(sizeof(link_data_t));
	((link_t*)(lss->head))->prior = NULL;
	((link_t*)(lss->peer))->prior = NULL;

	((link_t*)(lss->head))->next = (link_t*)(lss->peer);
	((link_t*)(lss->peer))->prior = (link_t*)(lss->head);

	lss->head->datas = NULL;
	lss->peer->datas = NULL;
	lss->data_size = sizeof(link_data_t);
}
void str_link_destory(str_s* ss) {
		
}

void str_link_add(str_s* ss, size_t index, data_t* data) {
	EMPTY_RETURN(ss);
	EMPTY_RETURN(data);

	link_str_s* lss = (link_str_s*)ss->elems;
	size_t cur_len = 0;

	int is_add = 0;
	link_data_t* block = (link_data_t*)((link_t*)lss->head)->next;
	while(block != lss->peer) {
		if(cur_len + block->cap > index) {
			size_t abs_index = index - cur_len;
			for(size_t i = block->len - 1; i > abs_index; i--) {
				block->datas[i] = block->datas[i - 1];
			}				
			block->datas[abs_index] = *data;
			is_add = 1;
			block->len++;
			ss->len++;
			break;
		}		
		cur_len += block->len;
		block = (link_data_t*)((link_t*)block)->next;
	}		
	if(!is_add) {
		print_info("need add block");
		// alloc mem
		// issue sub
		/**
		 *	issue
		 *	src_file	test_str.c
		 *	func:		test_str_manager, 
		 *	line:		sm_copy->copy(74)
		 *
		 *	assert_desc: test_str.o: 
		 *	malloc.c:2379: sysmalloc: 
		 *	Assertion `(old_top == initial_top (av) && old_size == 0) 
		 *	|| ((unsigned long) (old_size) >= MINSIZE 
		 *		 && prev_inuse (old_top) 
		 *		 &&	((unsigned long) old_end 
		 *			  & (pagesize - 1)) == 0)' failed.) 
		 * */
		link_data_t* nb = (link_data_t*)malloc(sizeof(link_data_t));

		// init data
		nb->len = 0;
		nb->cap = 32;
		nb->datas = (data_t*)malloc(nb->len);
		memset(nb->datas,(data_t)0, nb->len);

		// link
		link_t* nbl = &nb->link;
		link_t* obl = &block->link;
		nbl->next = obl;
		nbl->prior = obl->prior;
		obl->prior->next = nbl;
		obl->prior = nbl;

		print_val((link_data_t*)lss->head->link.next == nb, d);
		// assign
		nb->len = 1;
		nb->datas[0] = *data;
		ss->len++;
	}		
}			
void str_link_del(str_s* ss, size_t index, data_t* data) {
	EMPTY_RETURN(ss);
	EMPTY_RETURN(data);
	EMPTY_RETURN(ss->len > index);

	link_str_s* lss = (link_str_s*)ss->elems;
	size_t cur_len = 0;

	link_data_t* block = (link_data_t*)((link_t*)lss->head)->next;
	while(block != lss->peer) {
		if(cur_len + block->len > index) {
			size_t abs_addr = index - cur_len;
			*data = block->datas[abs_addr];
			for(size_t i = abs_addr; i < block->len - 1; i++) {
				block->datas[i] = block->datas[i + 1];
			}
			block->len--;
			ss->len--;
			break;
		}

		cur_len += block->len;
		block = (link_data_t*)((link_t*)block)->next;
	}

	if(block->len == 0) {
		print_info("need del block");
	}
}
void str_link_update(str_s* ss, size_t index, data_t* data) {
	EMPTY_RETURN(ss);
	EMPTY_RETURN(data);
	EMPTY_RETURN(ss->len > index);

	link_str_s* lss = (link_str_s*)ss->elems;
	size_t cur_len = 0;

	link_data_t* block = (link_data_t*)((link_t*)lss->head)->next;
	while(block != lss->peer) {
		if(cur_len + block->len > index) {
			size_t abs_addr = index - cur_len;
			block->datas[abs_addr] = *data;
			break;
		}
		cur_len += block->len;
		block = (link_data_t*)((link_t*)block)->next;
	}
}
void str_link_find(str_s* ss, size_t index, data_t* data) {
	EMPTY_RETURN(ss);
	EMPTY_RETURN(data);
	EMPTY_RETURN(ss->len > index);

	link_str_s* lss = (link_str_s*)ss->elems;
	size_t cur_len = 0;

	*data = -1;
	link_data_t* block = (link_data_t*)((link_t*)lss->head)->next;
	while(block != lss->peer) {
		if(cur_len + block->len > index) {
			size_t abs_addr = index - cur_len;
			*data = block->datas[abs_addr];
			break;
		}
		cur_len += block->len;
		block = (link_data_t*)((link_t*)block)->next;
	}

}

void str_link_traverse(str_s* ss, void (*work)(data_t*), const char* profix) {	
	EMPTY_RETURN(ss);
	link_str_s* lss = (link_str_s*)ss->elems;

	size_t len = 0;
	len = ss->len;
	char msg[256] = { 0 };
	sprintf(msg, "str_link_traverse: len = %lu, %s", len, profix);
	print_info(msg);
	link_data_t* block = (link_data_t*)((link_t*)lss->head)->next;
	while(block != lss->peer) {
		for(size_t i = 0; i < block->len; i++) {
			work(block->datas + i);
		}
		block = (link_data_t*)((link_t*)block)->next;
	}
	printf("\n");
}


void init_str_ap(str_mg** sm, strbo_mapper_t** smp, size_t type_number) {
	EMPTY_RETURN((*sm) == NULL);

	((*sm)) = (str_mg*)malloc(sizeof(str_mg));
	EMPTY_RETURN((*sm) != NULL);

	(*sm)->st = (str_s*)malloc(sizeof(str_s));
	(*sm)->bo = (str_o*)malloc(sizeof(str_o));
	
	if(*smp == NULL)
		INIT_STR_BO_MAPPER(smp);
	(*sm)->bo = (*smp)->get(*smp, type_number);

	(*sm)->bo->create((*sm)->st, (*sm)->bo->elem_size, (*sm)->bo->type_number);
	
	(*sm)->assign = &str_assign;
	(*sm)->copy = &str_copy;
	(*sm)->compare = &str_compare;
	(*sm)->empty = &str_empty;
	(*sm)->length = &str_length;
	(*sm)->index = &str_index;
	(*sm)->sub = &str_sub;
	(*sm)->concat = &str_concat;
	(*sm)->clear = &str_clear;

}
void str_assign (str_mg* str, data_t* datas, size_t data_size) {
	for(size_t i = 0; i < data_size; i++) {
		print_val(i, lu);
		str->bo->add(str->st, i, datas + i);
	}		
}
void str_copy (str_mg* str, str_mg* other) {
	size_t len = 0;
	str_mg *elems = other;

	elems->length(elems, &len);
	data_t data;

	for(size_t i = 0; i < len; i++) {
		elems->bo->find(elems->st, i, &data);
		str->bo->add(str->st, i, &data);
	}
//	str->st->len = elems->st->len; // to profict strage
}

int  str_compare(str_mg* self, str_mg* other) {
	return 1;	
}

int  str_empty (str_mg* str) {
	return str->st->len == 0;
}
void str_length(str_mg* str, size_t* ans) {
	*ans = str->st->len;
}
void str_index (str_mg* str, data_t* data, size_t* ans) {
	data_t inner_data;
	*ans = -1;
	for(size_t i = 0; i < str->st->len; i++) {
		str->bo->find(str->st, i, &inner_data);
		if(inner_data == *data) {
			*ans = i;
			break;
		}
	}
}

void str_sub(str_mg* str, size_t index, size_t len, str_mg* ans) {
	size_t loop_size = index + len;
	data_t tmp_data;
	for(size_t i = index; i < loop_size; i++) {
		str->bo->find(str->st, i, &tmp_data);
		print_val(tmp_data, d);
		ans->bo->add(ans->st, i - index, &tmp_data);
	} 
}


void str_concat(str_mg* head, str_mg* peer) {
	size_t loop_size, index = 0;
	peer->length(peer, &loop_size);
	data_t tmp_data;

	if(head->st->type_number == TYPE_NUMBER_LINK) {
		link_t* phead = &((link_str_s*)peer->st->elems)->head->link;
		link_t* ppeer = &((link_str_s*)peer->st->elems)->peer->link;

		link_t* hpeer = &((link_str_s*)head->st->elems)->peer->link;
		hpeer->prior->next = phead->next;
		phead->next->prior = hpeer->prior;

		ppeer->prior->next = hpeer;
		hpeer->prior = ppeer->prior;
		head->st->len += peer->st->len;
	} else if(head->st->type_number == TYPE_NUMBER_ARRAY) {
		data_t tmp_data;
		for(size_t i = 0; i < peer->st->len; i++) {
			print_val(i, lu);
			peer->bo->find(peer->st, i, &tmp_data);
			head->bo->add(head->st, head->st->len, &tmp_data);
		}
	}
}
void str_clear (str_mg* str) {
	str->st->len = 0;
}


