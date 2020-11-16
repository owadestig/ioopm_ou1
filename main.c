#include <stdio.h>
#include <stdlib.h>
#include "hash_table.h"

int main(int argc, char const *argv[])
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create();
    ioopm_hash_table_insert(ht, 5, "e");
    ioopm_hash_table_insert(ht, 3, "c");
    ioopm_hash_table_insert(ht, 1, "a");
    ioopm_hash_table_insert(ht, 4, "d");
    ioopm_hash_table_insert(ht, 2, "b");
    //  int *keys = ioopm_hash_table_keys(ht);
    char **values = ioopm_hash_table_values(ht);
    int size = ioopm_hash_table_size(ht);
    ioopm_hash_table_remove(ht, 6);
    ioopm_hash_table_remove(ht, 5);
    ioopm_hash_table_values(ht);
    ioopm_hash_table_destroy(ht);
    /*
    fprintf(stdout, "Keys = ");
    for (int i = 0; i < size; i++)
    {
        fprintf(stdout, "%d ", keys[i]);
    }
    free(keys);
*/
    fprintf(stdout, "Values = \n");
    for (int i = 0; i < size; i++)
    {
        fprintf(stdout, "%s \n", values[i]);
    }

    int frees = 0;
    for (int i = 0; i < size; i++)
    {
        free(values[i]);
        frees++;
    }

    free(values);
    frees++;

    printf("frees = %d\n", frees);

    return 0;
}
