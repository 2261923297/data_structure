#pragma once

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <sys/time.h>
	
static inline uint64_t cur_time_ms();
static inline uint64_t cur_time_us();



#define test_func(func, ...)  do { \
		printf("\n[test] %s:%d %s is begin......\n", __FILE__, __LINE__, #func);				\
		uint64_t start = cur_time_us();						\
		func(__VA_ARGS__);									\
		uint64_t end = cur_time_us();						\
		printf("[test] %s:%d %s is end, using time is %" PRIu64 "us\n", __FILE__, __LINE__, #func, end - start);						\
	} while(0);												\

//


#define print_val(val, format) \
	printf("[info] %s:%d %s = %" #format "\n", __FILE__, __LINE__, #val, val);


#define print_llu(val) \
	printf("[info] %s:%d %s = %" PRIu64 "\n", __FILE__, __LINE__, #val, (val));	


#define error_return(func_name, rt_val) \
	printf("[error] %s:%d func:%s errno = %d\n", __FILE__, __LINE__, #func_name, errno); \
	return rt_val;				\
//

#define mlc(_T) ((#_T)*)malloc(sizeof((#_T)))

static inline uint64_t 
cur_time_us() {
	struct timeval cur;
	gettimeofday(&cur, NULL);

	return cur.tv_sec * 1000000 + cur.tv_usec;
}

static inline uint64_t 
cur_time_ms() {		
	struct timeval cur;
	gettimeofday(&cur, NULL);

	return cur.tv_sec * 1000 + cur.tv_usec / 1000;
}

