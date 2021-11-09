#pragma once 


#define print_val(val, type) \
	printf("[info]  %s:%d " #val " = %" #type " \n", __FILE__, __LINE__, val);

#define traverse(data_structure, visit) data_structure->bo->traverse(data_structure->st, visit, #visit)

#define EMPTY_RETURN(val)  \
	if(val == 0) { \
		printf("[error] %s:%d { %s } can^t be 0\n", __FILE__, __LINE__, #val);	\
		return; \
	}

#define EMPTY_RETURN_VAL(val, rt)  \
	if(val == 0) { \
		printf("[error] %s:%d { %s } can^t be 0\n", __FILE__, __LINE__, #val);	\
		return rt; \
	}

