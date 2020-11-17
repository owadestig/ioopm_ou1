#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "linked_list.h"
#include <CUnit/CUnit.h>

//#include <CUnit/Basic.h>

int init_suite(void)
{
    return 0;
}

int clean_suite(void)
{
    return 0;
}

void test_create()
{
    ioopm_list_t *list = ioopm_linked_list_create();
    CU_ASSERT_PTR_NOT_NULL(list);
    ioopm_linked_list_destroy(list);
}

void test_destroy()
{
}

void test_append()
{
}

void test_prepend()
{
}

void test_insert()
{
}

int test_remove()
{
}

int test_get()
{
}

void test_contains()
{
}

void test_size()
{
}

void test_is_empty()
{
}

void test_clear()
{
}

void test_all()
{
}

void test_any()
{
}

void test_apply_to_all()
{
}

int main()
{
    CU_pSuite test_suite1 = NULL;

    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    test_suite1 = CU_add_suite("Test Suite 1", init_suite, clean_suite);
    if (NULL == test_suite1)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (
        (NULL == CU_add_test(test_suite1, "test 1", test1)) ||
        (NULL == CU_add_test(test_suite1, "test 2", test2)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}