#include "final_link.h"

#define elem_t int

typedef __link_node_st {
	elem_t		elem;
	link_t  fl;
} link_node_t;

typedef __link_list_st {
	link_node_t head;
	link_node_t peer;
	size_t  elem_size;
	size_t  len;
	size_t  cap;

} link_list_t;

typedef __link_list_bo {
	link_o* op;
	
	

}
