#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "final_link.h"

void _link_init(link_t** link) {
	*link = (link_t*) malloc(sizeof(link_t));
	link_t* l = *link;
	l->next = NULL;
	l->prior = NULL;
}
void _link_add(link_t* link, link_t* which) {
	if(link == NULL) print_error("link coudn^t be NULL");
	if(which == NULL) print_error("link can^t add a NULL link");

	if(link->next != NULL)
		link->next->prior = which;
	which->next = link->next;
	which->prior = link;
	link->next = which;
}
void _link_del(link_t* link) {
	if(link == NULL) print_error("op link_del link coudn^t be NULL");

	link->next->prior = link->prior;
	link->prior->next = link->next;
	link->next = NULL;
	link->prior = NULL;
}
void _link_update(link_t* link, link_t* which) {
	if(link == NULL) print_error("op link_update link coudn^t be NULL");

	if(which == NULL) {
		link->next = NULL;
		link->prior = NULL;
		return;
	}
	link->next = which->next;
	link->prior = which->prior;
}
void _link_find(link_t* head, size_t index, link_t** ans) {
	if(head == NULL) print_error("op link_find head coudn^t be NULL");
	if(ans == NULL) print_error("op link_find ans coudn^t be NULL");

	link_t* tmp = NULL;
	if(head->next == NULL) {
		tmp = head->prior;
		while(index--) {
			if(tmp == NULL) {
				print_error("index is too long!");
				*ans = NULL;
				return;
			}
			tmp = tmp->prior;
		}
		*ans = tmp;

	} else {
		tmp = head->next;
		while(index--) {
			if(tmp == NULL) {
				print_error("index is too long!");
				*ans = NULL;
				return;
			}
			tmp = tmp->next;
		}
		*ans = tmp;
	}

}


void bind_link_bo(link_o* lbo) {
	if(lbo == NULL) print_error("bind_link_bo lbo coudn^t be NULL");

	lbo->init = &_link_init;
	lbo->add = &_link_add;
	lbo->del = &_link_del;
	lbo->update = &_link_update;
	lbo->find = &_link_find;
}

