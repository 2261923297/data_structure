#include "final_link.h"
#include <stdlib.h>

void show_link(link_t* link, const char* profix) {
	link_t* tmp = link;
	printf("%s: \n", profix);
	link_t* self = NULL;
	link_t* next = NULL;
	link_t* prio = NULL;
	while(tmp != NULL) {
		self = tmp;
		next = tmp->next;
		prio = tmp->prior;
		print_val(prio, p);
		print_val(self, p);
		print_val(next, p);
		tmp = tmp->next;
		printf("\n");
	}
}

void init_link(link_o* lbo, link_t** head, link_t** peer) {
	lbo->init(head);
	lbo->init(peer);

	lbo->add(*head, *peer);
}

void test_add(link_o* lbo, link_t* head, int n_add) {
	link_t* mid = NULL;
	while(n_add--) {
		lbo->init(&mid);
		lbo->add(head, mid);
		mid = NULL;
	}	
}

void test_find(link_o* lbo, link_t* head, int n_find) {
	link_t* ans = NULL;
	for(int i = 0; i < n_find; i++) {
		printf("find: %d: ", i);
		lbo->find(head, i, &ans);
		printf("%p\n", ans);
	}
}

void test_update(link_o* lbo, link_t*head, int n_update) {

}

void test_del(link_o* lbo, link_t* head, int n_del) {
	link_t* l_del = NULL;
	for(int i = 0; i < n_del; i++) {
		l_del = head->next;
		lbo->del(l_del);
		free(l_del);
	}
}
void test_base() {
	link_o* lbo = (link_o*)malloc(sizeof(link_o));
	bind_link_bo(lbo);

	link_t* head = NULL;
	link_t* peer = NULL;

	init_link(lbo, &head, &peer);
	const int nlink = 3;

	test_add(lbo, head, nlink);
	show_link(head, "test_base");

	test_find(lbo, head, nlink);

	test_update(lbo, head, nlink);

	test_del(lbo, head, nlink);
	show_link(head, "del");

}

int main(int argc, char** argv) {
	print_val("hello, world!", s);
	test_base();

	return 0;
}
