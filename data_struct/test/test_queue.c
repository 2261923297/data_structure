
#define elem_t link_node_t
#include "queue.h"
#include "util.h"



void test_base() {
	queue_t *q = (queue_t*)malloc(sizeof(queue_t));	

	if(sizeof(elem_t) != sizeof(data_t)) {
		init_queue(q, init_qst_link, init_qbo);
	} else {
		init_queue(q, init_qst_array, init_qbo);
	}
	bind_queue(q);

	for(int i = 0; i < 5; i++) {
		q->push(q, &i);
	}
	traverse(q, print_stdout);

	int pt = 0;
	for(int i = 0; i < 5; i++) {
		q->top(q, &pt);
		print_val(pt, d);
		q->pop(q, &pt);
		print_val(pt, d);
	}
	traverse(q, print_stdout);
}

int main(int argc, char* argv) {
	test_base();
	print_val("hello, world!", s);


	return 0;
}
