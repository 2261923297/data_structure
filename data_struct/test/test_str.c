#include "str.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>

void print_stdout(data_t* data) {
	printf("%d, ", *data);
}
void change_to_zero(data_t* data) {
	*data = 0;
}
void test_array_str() {
	struct __str_st ss;
	struct __strbo_mapper *sm = NULL;
	test_func(INIT_STR_BO_MAPPER, &sm);
	struct __str_bo* sb = sm->get(sm, TYPE_NUMBER_ARRAY);

	test_func(sb->create, &ss, sizeof(array_str_s), TYPE_NUMBER_ARRAY);

	for(int i = 0; i < 32; i++) {
		sb->add(&ss, i, &i);
	}
	sb->traverse(&ss, print_stdout, "add");

	data_t data = 0;

	for(int i = 0; i < 32; i++) {
		sb->find(&ss, i, &data);
		print_val(data, d);
	}

	for(int i = 0; i < 32; i++) {
		sb->update(&ss, i, &data);
	}
	sb->traverse(&ss, print_stdout, "update");

	for(int i = 0; i < 32; i++) {
		sb->del(&ss, 0, &data);
	}
	sb->traverse(&ss, print_stdout, "del");
}

void test_str_manager() {
	size_t test_type = TYPE_NUMBER_LINK;
	str_mg* sm = NULL;
	str_mg* sm_copy = NULL;
	str_mg* sm_sub = NULL;

	strbo_mapper_t* smp = NULL;
	init_str_ap(&sm, &smp, test_type);
	init_str_ap(&sm_copy, &smp, test_type);
	init_str_ap(&sm_sub, &smp, test_type);
	
	data_t original_datas[] =  { 1, 2, 3, 4, 5, 6, 7 };

	print_info("sm->assign---------------------");
	sm->assign(sm, original_datas, sizeof(original_datas) / sizeof(data_t));
	sm->bo->traverse(sm->st, print_stdout, "mg->assign");


	print_info("sm->index---------------------");
	size_t index = 0;
	for(data_t i = 1; i <= sm->st->len; i++) {
		sm->index(sm, &i, &index);
		print_val(index, lu);
	}
/*
	print_info("sm_sub->assign---------------------");
	sm_sub->assign(sm_sub, original_datas, sizeof(original_datas) / sizeof(data_t));
	sm->bo->traverse(sm_sub->st, print_stdout, "mg_sub->assign");
*/

	print_info("sm_copy");
	sm_copy->copy(sm_copy, sm);
	sm_copy->bo->traverse(sm_copy->st, print_stdout, "sm_copy->copy");
	
	print_info("sm->sub---------------------");
	sm_sub->sub(sm, 1, 5, sm_sub);
	sm->bo->traverse(sm_sub->st, print_stdout, "mg->sub");

	print_info("sm->concat---------------------");
	sm->concat(sm, sm_sub);
	sm->bo->traverse(sm->st, print_stdout, "mg->sub");
}

int main() {
//	test_array_str();
	test_str_manager();
	return 0;
}


