#include <stdio.h>
#include <stdlib.h>
#include "hash_table.h"
#include <string.h>
#include <stdbool.h>
//#include <CUnit/Basic.h>

ioopm_hash_table_t *ioopm_hash_table_create_test()
{
    ioopm_hash_table_t *ht  = ioopm_hash_table_create();
    if (/* condition */)
    {
        /* code */
    }
    
}

void ioopm_hash_table_destroy_test(ioopm_hash_table_t *ht)
{

}

void ioopm_hash_table_insert_test(ioopm_hash_table_t *ht, int key, char *value)
{

}

void *ioopm_hash_table_lookup_test(ioopm_hash_table_t *ht, int key)
{

}

char *ioopm_hash_table_remove_test(ioopm_hash_table_t *ht, int key)
{
    
}

int ioopm_hash_table_size_test(ioopm_hash_table_t *h)
{

}

bool ioopm_hash_table_is_empty_test(ioopm_hash_table_t *h)
{

}

void ioopm_hash_table_clear_test(ioopm_hash_table_t *h)
{

}

void *ioopm_hash_table_keys_test(ioopm_hash_table_t *h)
{

}

char **ioopm_hash_table_values_test(ioopm_hash_table_t *h)
{

}

bool ioopm_hash_table_has_key_test(ioopm_hash_table_t *h, int key)
{

}

bool ioopm_hash_table_has_value_test(ioopm_hash_table_t *h, char *value)
{
    
}

bool ioopm_hash_table_all_test(ioopm_hash_table_t *h, ioopm_apply_function pred, void *arg)
{

}

bool ioopm_hash_table_any_test(ioopm_hash_table_t *h, ioopm_apply_function pred, void *arg)
{

}

void ioopm_hash_table_apply_to_all_test(ioopm_hash_table_t *h, ioopm_apply_function apply_fun, void *arg)
{

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
    (NULL == CU_add_test(test_suite1, "test 2", test2))
  )
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}
