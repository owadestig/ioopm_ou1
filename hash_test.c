#include <stdio.h>
#include <stdlib.h>
#include "hash_table.h"
#include <string.h>
#include <stdbool.h>
//#include <CUnit/Basic.h>

//Klar
void test_create()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  CU_ASSERT_PTR_NOT_NULL(ht);
  ioopm_hash_table_destroy(ht);
}

//klar
void test_destroy()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  ioopm_hash_table_destroy(ht);
  CU_ASSERT_PTR_NULL(ht);
}

void test_insert()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  ioopm_hash_table_destroy(ht);
}

//klar
void test_lookup1()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  for (int i = 0; i < 18; ++i) /// 18 is a bit magical
  {
    CU_ASSERT_PTR_NULL(ioopm_hash_table_lookup(ht, i));
  }
  CU_ASSERT_PTR_NULL(ioopm_hash_table_lookup(ht, -1));
  ioopm_hash_table_destroy(ht);
}

//klar
void test_lookup2()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  int key = 5;
  char *value = "test";
  CU_ASSERT_PTR_NULL(ioopm_hash_table_lookup(ht, key));
  ioopm_hash_table_insert(ht, key, value);
  CU_ASSERT(value == ioopm_hash_table_lookup(ht, key));
  ioopm_hash_table_destroy(ht);
}

//klar
void test_remove1()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  CU_ASSERT_PTR_NULL(ioopm_hash_table_remove(ht, 1));
  ioopm_hash_table_insert(ht, 1, "hej");
  char *test = ioopm_hash_table_remove(ht, 1);
  CU_ASSERT(strcmp(test, "hej"));
  //free(test);
  test = ioopm_hash_table_remove(ht, 1);
  CU_ASSERT_PTR_NULL(test);
  ioopm_hash_table_destroy(ht);
}

//klar
void test_remove2()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  for (int i = 0; i < 18; ++i) /// 18 is a bit magical
  {
    ioopm_hash_table_insert(ht, i, "vadsomhelst");
  }

  for (int i = 17; i >= 0; --i) /// 18 is a bit magical
  {
    char *temp = ioopm_hash_table_remove(ht, i);
    CU_ASSERT_PTR_NOT_NULL(temp);
    //free(temp);
  }
  CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht));
  ioopm_hash_table_destroy(ht);
}

//KLAR
void test_size()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  CU_ASSERT(0 == ioopm_hash_table_size(ht));
  for (int i = 0; i < 18; ++i) /// 18 is a bit magical
  {
    ioopm_hash_table_insert(ht, i, "vadsomhelst");
    CU_ASSERT(i + 1 == ioopm_hash_table_size(ht));
  }

  for (int i = 17; i >= 0; --i) /// 18 is a bit magical
  {
    char *temp = ioopm_hash_table_remove(ht, i);
    //free(temp);
    CU_ASSERT(i - 1 == ioopm_hash_table_size(ht));
  }

  CU_ASSERT(0 == ioopm_hash_table_size(ht));
  ioopm_hash_table_destroy(ht);
}

//KLAR
void test_empty()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht));
  ioopm_hash_table_insert(ht, 5, "hej");
  CU_ASSERT_FALSE(ioopm_hash_table_is_empty(ht));
  ioopm_hash_table_destroy(ht);
}

//KLAR
void test_clear()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  ioopm_hash_table_insert(ht, 5, "hej");
  ioopm_hash_table_clear(ht);
  CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht));
  ioopm_hash_table_destroy(ht);
}

void keys_test()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  ioopm_hash_table_destroy(ht);
}

void values_test()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  ioopm_hash_table_destroy(ht);
}

void test_has_key()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  ioopm_hash_table_destroy(ht);
}

void test_has_value()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  ioopm_hash_table_destroy(ht);
}

void test_all()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  ioopm_hash_table_destroy(ht);
}

void test_any()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  ioopm_hash_table_destroy(ht);
}

void test_apply_all()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  ioopm_hash_table_destroy(ht);
}

int init_suite(void)
{
  return 0;
}

int clean_suite(void)
{
  return 0;
}

void test1(void)
{
  CU_ASSERT(true);
}

void test2(void)
{
  CU_ASSERT(true);
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
