#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "linked_list.h"
//#include <CUnit/CUnit.h>

//#include <CUnit/Basic.h>

void CU_ASSERT(bool as);
void CU_ASSERT_TRUE(bool as);
void CU_ASSERT_FALSE(bool as);
void CU_ASSERT_PTR_NULL(bool as);
void CU_ASSERT_PTR_NOT_NULL(bool as);
void ghettostyle();

void test_create()
{
    ioopm_list_t *list = ioopm_linked_list_create();
    CU_ASSERT_PTR_NOT_NULL(list);
    ioopm_linked_list_destroy(list);
}

void test_destroy()
{
    ioopm_list_t *list = ioopm_linked_list_create();
    ioopm_linked_list_insert(list, 0, 5);
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
    ioopm_linked_list_insert(list, 0, 2);
    CU_ASSERT(1 == ioopm_linked_list_get(list, 1));
    ioopm_linked_list_insert(list, 0, 3);
    CU_ASSERT(2 == ioopm_linked_list_get(list, 1));
    ioopm_linked_list_insert(list, 4, 4);
    CU_ASSERT(4 == ioopm_linked_list_get(list, 4));

    ioopm_linked_list_destroy(list);
}

int test_remove()
{
}

int test_get()
{
    ioopm_list_t *list = ioopm_linked_list_create();
    for (int i = 0; i < 10; i++)
    {
        ioopm_linked_list_insert(list, 0, i);
    }
    CU_ASSERT(4 == ioopm_linked_list_get(list, 5));
    CU_ASSERT(0 == ioopm_linked_list_get(list, 9));
    CU_ASSERT_PTR_NULL(ioopm_linked_list_get(list, 12));
    CU_ASSERT_PTR_NULL(ioopm_linked_list_get(list, -5));
    ioopm_linked_list_destroy(list);
}

void test_contains()
{
    ioopm_list_t *list = ioopm_linked_list_create();
    for (int i = 0; i < 10; i++)
    {
        ioopm_linked_list_insert(list, 0, i);
    }
    CU_ASSERT_TRUE(ioopm_linked_list_contains(list, 5));
    CU_ASSERT_FALSE(ioopm_linked_list_contains(list, 11));
    ioopm_linked_list_destroy(list);
}

void test_size()
{
    ioopm_list_t *list = ioopm_linked_list_create();
    for (int i = 0; i < 10; i++)
    {
        ioopm_linked_list_insert(list, 0, i);
    }
    CU_ASSERT(10 == ioopm_linked_list_size(list));
    ioopm_linked_list_remove(list, 5);
    CU_ASSERT(9 == ioopm_linked_list_size(list));
    ioopm_linked_list_clear(list);
    CU_ASSERT(0 == ioopm_linked_list_size(list));
    ioopm_linked_list_destroy(list);
}

void test_is_empty()
{
    ioopm_list_t *list = ioopm_linked_list_create();
    for (int i = 0; i < 10; i++)
    {
        ioopm_linked_list_insert(list, 0, i);
    }
    CU_ASSERT_FALSE(ioopm_linked_list_is_empty(list));
    ioopm_linked_list_clear(list);
    CU_ASSERT_TRUE(ioopm_linked_list_is_empty(list));
    ioopm_linked_list_destroy(list);
}

void test_clear()
{
    ioopm_list_t *list = ioopm_linked_list_create();
    for (int i = 0; i < 10; i++)
    {
        ioopm_linked_list_insert(list, 0, i);
    }
    CU_ASSERT_FALSE(ioopm_linked_list_is_empty(list));
    ioopm_linked_list_clear(list);
    CU_ASSERT_TRUE(ioopm_linked_list_is_empty(list));
    CU_ASSERT_PTR_NOT_NULL(list);
    ioopm_linked_list_destroy(list);
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
    ghettostyle();

    /*
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
    */
}

void ghettostyle()
{
    test_create();
    test_destroy();
    test_append();
    test_prepend();
    test_insert();
    test_remove();
    test_get();
    test_contains();
    test_size();
    test_is_empty();
    test_clear();
}

void CU_ASSERT(bool as)
{
    if (as)
    {
        fprintf(stdout, "CU_ASSERT_TRUE: Success\n");
        return;
    }

    fprintf(stdout, "CU_ASSERT_TRUE: FAIL\n");
}

void CU_ASSERT_FALSE(bool as)
{
    if (!as)
    {
        fprintf(stdout, "CU_ASSERT_FALSE: Success\n");
        return;
    }

    fprintf(stdout, "CU_ASSERT_FALSE: FAIL\n");
}

void CU_ASSERT_TRUE(bool as)
{
    if (as)
    {
        fprintf(stdout, "CU_ASSERT_TRUE: Success\n");
        return;
    }

    fprintf(stdout, "CU_ASSERT_TRUE: FAIL\n");
}

void CU_ASSERT_PTR_NOT_NULL(bool as)
{
    if (as != NULL)
    {
        fprintf(stdout, "CU_ASSERT_PTR_NOT_NULL: Success\n");
        return;
    }

    fprintf(stdout, "CU_ASSERT_PTR_NOT_NULL: FAIL\n");
}

void CU_ASSERT_PTR_NULL(bool as)
{
    if (as == NULL)
    {
        fprintf(stdout, "CU_ASSERT_PTR_NULL: Success\n");
        return;
    }

    fprintf(stdout, "CU_ASSERT_PTR_NULL: FAIL\n");
}