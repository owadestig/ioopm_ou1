#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"
#include <stdbool.h>

#define No_Buckets 17

struct entry
{
    int key;       // holds the key
    char *value;   // holds the value
    entry_t *next; // points to the next entry (possibly NULL)
};

struct hash_table
{
    entry_t *buckets[17];
    int size;
};

static entry_t *find_previous_entry_for_key(entry_t *prev_entry, entry_t *entry, int key);
static entry_t *entry_create(int key, char *value, entry_t *next);
static void remove_bucket(ioopm_hash_table_t *ht, entry_t *entry);
static bool key_equiv(int key, char *value_ignored, void *x);
static bool value_equiv(int key_ignored, char *value, void *x);

/// @brief Create a new hash table
/// @return A new empty hash table
ioopm_hash_table_t *ioopm_hash_table_create()
{
    ioopm_hash_table_t *ht = calloc(1, sizeof(ioopm_hash_table_t));

    if (ht == NULL)
    {
        perror("ioopm_hash_table_create: Couldnt calloc\n");
    }

    ht->size = 0;

    return ht;
}

/// @brief Delete a hash table and free its memory
/// param ht a hash table to be deleted
void ioopm_hash_table_destroy(ioopm_hash_table_t *ht)
{
    ioopm_hash_table_clear(ht);
    free(ht);
}

/// @brief add key => value entry in hash table ht
/// @param ht hash table operated upon
/// @param key key to insert
/// @param value value to insert
void ioopm_hash_table_insert(ioopm_hash_table_t *ht, int key, char *value)
{
    int bucket = key % No_Buckets;

    entry_t *entry = find_previous_entry_for_key(NULL, ht->buckets[bucket], key);

    // Om listan är tom eller entry är längst fram
    if (entry == NULL)
    {
        // Om listan är tom
        if (ht->buckets[bucket] == NULL)
        {
            ht->buckets[bucket] = entry_create(key, value, NULL);
            ht->size++;
            return;
        }

        // Om entry längst fram har samma key
        if (ht->buckets[bucket]->key == key)
        {
            ht->buckets[bucket]->value = value;
            return;
        }

        // Om entry längst fram har en större key än variabel key
        ht->buckets[bucket] = entry_create(key, value, ht->buckets[bucket]);
        ht->size++;
        return;
    }

    // Om vi hittade en entry med rätt key
    if (entry->next != NULL && entry->next->key == key)
    {
        entry->next->value = value;
        return;
    }

    entry->next = entry_create(key, value, entry->next);
    ht->size++;
}

/// @brief checks if current entry has a matching or larger key then the input key,
///        iteratively searches the list until this criteria is met or reaches end of list
/// @param prev_entry previous entry to the one currently being investigated
/// @param key input key to insert
/// @param entry current entry thats investigated, checking if it matches or is larger than
///              param key
static entry_t *find_previous_entry_for_key(entry_t *prev_entry, entry_t *entry, int key)
{
    if (entry == NULL || entry->key >= key)
    {
        return prev_entry;
    }

    return find_previous_entry_for_key(entry, entry->next, key);
}

/// @brief create a new entry
/// @param key key to create entry with
/// @param value value to create entry with
/// @param next next entry after the newly created one
/// @return a pointer to a allocated new entry
static entry_t *entry_create(int key, char *value, entry_t *next)
{
    entry_t *new_entry = calloc(1, sizeof(entry_t));

    if (new_entry == NULL)
    {
        perror("entry_create: Couldn't calloc\n");
    }

    new_entry->key = key;
    new_entry->value = value;

    if (next != NULL)
    {
        new_entry->next = next;
    }

    return new_entry;
}

/// @brief lookup value for key in hash table ht
/// @param ht hash table operated upon
/// @param key key to lookup
/// @return the value mapped to by key (FIXME: incomplete)
void *ioopm_hash_table_lookup(ioopm_hash_table_t *ht, int key)
{
    int bucket = key % No_Buckets;
    entry_t *entry_front = ht->buckets[bucket];
    entry_t *prev_entry = find_previous_entry_for_key(NULL, entry_front, key);

    if (prev_entry == NULL)
    {
        if (entry_front->key == key)
        {
            return prev_entry->value;
        }

        fprintf(stdout, "Entry with key %d to lookup doesn't exist (empty bucket)\n", key);
        return NULL;
    }

    if (prev_entry->next != NULL && prev_entry->next->key == key)
    {
        return prev_entry->next->value;
    }

    return NULL;
}

/// @brief remove any mapping from key to a value
/// @param ht hash table operated upon
/// @param key key to remove
/// @return the value mapped to by key (FIXME: incomplete)
char *ioopm_hash_table_remove(ioopm_hash_table_t *ht, int key)
{
    int bucket = key % No_Buckets;
    entry_t *prev_entry = find_previous_entry_for_key(NULL, ht->buckets[bucket], key);
    char *val = NULL;

    // If prev_entry is NULL then bucket is empty or front of bucket has the right key
    if (prev_entry == NULL)
    {
        // Om bucket inte är tom och front bucket har rätt key
        // If bucket is NOT empty and front of bucket has the right key
        if (ht->buckets[bucket] != NULL && ht->buckets[bucket]->key == key)
        {
            val = ht->buckets[bucket]->value;
            entry_t *temp = ht->buckets[bucket]->next;
            free(ht->buckets[bucket]);
            ht->buckets[bucket] = temp;
        }
        else
        {
            fprintf(stdout, "Entry with key %d to remove doesn't exist\n", key);
            return NULL;
        }
    } // Om rätt key hittades som inte var front bucket
    else if (prev_entry->next != NULL && prev_entry->next->key == key)
    {
        entry_t *entry = prev_entry->next;
        prev_entry->next = entry->next;
        val = entry->value;
        free(entry);
    }
    else
    {
        fprintf(stdout, "Entry with key %d to remove doesn't exist\n", key);
        return NULL;
    }

    ht->size--;
    return val;
}

/// @brief returns the number of key => value entries in the hash table
/// @param h hash table operated upon
/// @return the number of key => value entries in the hash table
int ioopm_hash_table_size(ioopm_hash_table_t *h)
{
    return h->size;
}

/// @brief checks if the hash table is empty
/// @param h hash table operated upon
/// @return true is size == 0, else false
bool ioopm_hash_table_is_empty(ioopm_hash_table_t *h)
{
    if (ioopm_hash_table_size(h) == 0)
    {
        return true;
    }

    return false;
}

/// @brief clear all the entries in a hash table
/// @param ht hash table operated upon
void ioopm_hash_table_clear(ioopm_hash_table_t *ht)
{
    for (int i = 0; i < No_Buckets; i++)
    {
        while (ht->buckets[i] != NULL)
        {
            ioopm_hash_table_remove(ht, ht->buckets[i]->key);
        }
    }
}

static void remove_bucket(ioopm_hash_table_t *ht, entry_t *entry)
{
    if (entry->next == NULL)
    {
        ioopm_hash_table_remove(ht, entry->key);
        return;
    }
    remove_bucket(ht, entry->next);
    remove_bucket(ht, entry);
}

/// @brief return the keys for all entries in a hash map (in no particular order, but same as ioopm_hash_table_values)
/// @param h hash table operated upon
/// @return an array of keys for hash table h
int *ioopm_hash_table_keys(ioopm_hash_table_t *ht)
{
    int amount = ioopm_hash_table_size(ht);
    int i = 0;
    int *keys = calloc(1, amount * sizeof(int));

    for (int j = 0; j < No_Buckets; j++)
    {
        entry_t *entry = ht->buckets[j];

        while (entry != NULL)
        {
            keys[i] = entry->key;
            entry = entry->next;
            i++;
        }
    }
    return keys;
}

/// @brief return the values for all entries in a hash map (in no particular order, but same as ioopm_hash_table_keys)
/// @param h hash table operated upon
/// @return an array of values for hash table h
char **ioopm_hash_table_values(ioopm_hash_table_t *ht)
{
    int amount = ioopm_hash_table_size(ht);
    int i = 0;
    char **values = calloc(1, amount * sizeof(char *));

    for (int j = 0; j < No_Buckets; j++)
    {
        entry_t *entry = ht->buckets[j];

        while (entry != NULL)
        {
            char *temp = calloc(1, sizeof(entry->value));
            strcpy(temp, entry->value);
            values[i] = temp;
            entry = entry->next;
            i++;
        }
    }
    return values;
}

/// @brief prints all keys in hash table
/// @param h hash table operated upon
void ioopm_hash_table_print_keys(ioopm_hash_table_t *h)
{
    for (int i = 0; i < No_Buckets; i++)
    {
        fprintf(stdout, "bucket %d: ", i);

        entry_t *entry = h->buckets[i];
        while (entry != NULL)
        {
            fprintf(stdout, "%d ", entry->key);
            entry = entry->next;
        }
        fprintf(stdout, "\n");
    }
}

/// @brief prints all keys in hash table
/// @param h hash table operated upon
void ioopm_hash_table_print_values(ioopm_hash_table_t *h)
{
    for (int i = 0; i < No_Buckets; i++)
    {
        fprintf(stdout, "bucket %d: ", i);

        entry_t *entry = h->buckets[i];
        while (entry != NULL)
        {
            fprintf(stdout, "%s ", entry->value);
            entry = entry->next;
        }
        fprintf(stdout, "\n");
    }
}

/// @brief check if a hash table has an entry with a given key
/// @param h hash table operated upon
/// @param key the key sought
bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, int key)
{
    return ioopm_hash_table_any(ht, key_equiv, &key);
}

/// @brief check if a hash table has an entry with a given value
/// @param h hash table operated upon
/// @param value the value sought
bool ioopm_hash_table_has_value(ioopm_hash_table_t *ht, char *value)
{
    return ioopm_hash_table_any(ht, value_equiv, &value);
}

static bool key_equiv(int key, char *value_ignored, void *x)
{
    return key == *((int *)x);
}

static bool value_equiv(int key_ignored, char *value, void *x)
{
    /*
    char *other_value_ptr = x;
    char *other_value = calloc(1, strlen(other_value_ptr) * sizeof(char));
    strcpy(other_value, other_value_ptr);
    bool ret = strcmp(value, other_value);
    free(other_value);
    return ret;
    */
    bool temp = strcmp(value, ((char *)x));
    return temp;
}

/// @brief check if a predicate is satisfied by all entries in a hash table
/// @param h hash table operated upon
/// @param pred the predicate
/// @param arg extra argument to pred
bool ioopm_hash_table_all(ioopm_hash_table_t *h, ioopm_predicate pred, void *arg)
{
    for (int i = 0; i < 17; i++)
    {
        entry_t *entry = h->buckets[i];

        while (entry != NULL)
        {
            if (!pred(entry->key, entry->value, arg))
            {
                return false;
            }
            entry = entry->next;
        }
    }
    return true;
}

/// @brief check if a predicate is satisfied by any entry in a hash table
/// @param h hash table operated upon
/// @param pred the predicate
/// @param arg extra argument to pred
bool ioopm_hash_table_any(ioopm_hash_table_t *h, ioopm_predicate pred, void *arg)
{
    for (int i = 0; i < 17; i++)
    {
        entry_t *entry = h->buckets[i];

        while (entry != NULL)
        {
            if (pred(entry->key, entry->value, arg))
            {
                return true;
            }
            entry = entry->next;
        }
    }
    return false;
}

/// @brief apply a function to all entries in a hash table
/// @param h hash table operated upon
/// @param apply_fun the function to be applied to all elements
/// @param arg extra argument to apply_fun
void ioopm_hash_table_apply_to_all(ioopm_hash_table_t *h, ioopm_apply_function apply_fun, void *arg)
{
    apply_fun(0, ioopm_hash_table_values(h), arg);
}