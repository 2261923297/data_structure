#pragma once 


#define print_val(val, type) \
	printf("[info] " #val " = %" #type " \n", val);

#define list_traverse(list, func) _list_traverse(list, func, #func)

#define EMPTY_RETURN(val)  \
	if(val == 0) { \
		printf("[error] %s:%d { %s } can^t be 0\n", __FILE__, __LINE__, #val);	\
		return; \
	}

