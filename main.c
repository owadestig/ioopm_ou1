#include <stdio.h>
#include <stdlib.h>
#include "hash_table.h"

int main(int argc, char const *argv[])
{
    printf("TEST\n");

    char *test1 = calloc(1, 3*sizeof(char));
    test1 = "abc";
    char *test2 = &test1;
    test1 = "123";

    printf("test1 = %s , test2 = %s",test1, test2); 


    ioopm_hash_table_t *ht = ioopm_hash_table_create();
    ioopm_hash_table_insert(ht, 5, "e");
    ioopm_hash_table_insert(ht, 3, "c");
    ioopm_hash_table_insert(ht, 1, "a");
    ioopm_hash_table_insert(ht, 4, "d");
    ioopm_hash_table_insert(ht, 2, "b");
    ioopm_hash_table_keys(ht);
    ioopm_hash_table_values(ht);
    ioopm_hash_table_remove(ht, 6);
    ioopm_hash_table_remove(ht, 5);
    ioopm_hash_table_values(ht);
    ioopm_hash_table_destroy(ht);

    return 0;
}
