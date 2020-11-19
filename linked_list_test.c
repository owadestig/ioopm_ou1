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
    ioopm_list_t *list = ioopm_linked_list_create();
    ioopm_linked_list_insert(list, 5);
    ioopm_linked_list_destroy(list);
    CU_ASSERT_PTR_NULL(list);
}

void test_append()
{
    ioopm_list_t *list = ioopm_linked_list_create();
    ioopm_linked_list_append(list, 5);
    ioopm_linked_list_append(list, 6);
    ioopm_linked_list_append(list, 7);
    CU_ASSERT(7 == ioopm_linked_list_get(list, 0));
    ioopm_linked_list_destroy(list);
}

void test_prepend()
{
    ioopm_list_t *list = ioopm_linked_list_create();
    ioopm_linked_list_prepend(list, 5);
    ioopm_linked_list_prepend(list, 6);
    ioopm_linked_list_prepend(list, 7);
    CU_ASSERT(7 == ioopm_linked_list_get(list, 0));
    ioopm_linked_list_destroy(list);
}

void test_insert()
{
    ioopm_list_t *list = ioopm_linked_list_create();

    ioopm_linked_list_insert(list, 0, 1);
    CU_ASSERT(1 == ioopm_linked_list_get(list, 0));
    ioopm_linked_list_insert(list, 0 2);
    CU_ASSERT(1 == ioopm_linked_list_get(list, 1))
    ioopm_linked_list_insert(list, 0, 3);
    CU_ASSERT(2 == ioopm_linked_list_get(list, 1))
    ioopm_linked_list_insert(list, 4, 4);
    CU_ASSERT(4 == ioopm_linked_list_get(list, 4))

    ioopm_linked_list_destroy(list);
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