#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

struct entry
{
    int key;       // holds the key
    char *value;   // holds the value
    entry_t *next; // points to the next entry (possibly NULL)
};

struct hash_table
{
    entry_t *buckets[17];
};

void remove_bucket(ioopm_hash_table_t *ht, entry_t *entry);
entry_t *find_previous_entry_for_key(entry_t *prev_entry, entry_t *entry, int key);
entry_t *entry_create(int key, char *value, entry_t *next);

/// @brief Create a new hash table
/// @return A new empty hash table
ioopm_hash_table_t *ioopm_hash_table_create()
{
    ioopm_hash_table_t *ht = calloc(1, sizeof(ioopm_hash_table_t));

    if (ht == NULL)
    {
        perror("ioopm_hash_table_create: Couldnt calloc\n");
    }

    return ht;
}

/// @brief Delete a hash table and free its memory
/// param ht a hash table to be deleted
void ioopm_hash_table_destroy(ioopm_hash_table_t *ht)
{
    free(ht->buckets);
    free(ht);
}

/// @brief add key => value entry in hash table ht
/// @param ht hash table operated upon
/// @param key key to insert
/// @param value value to insert
void ioopm_hash_table_insert(ioopm_hash_table_t *ht, int key, char *value)
{
    int bucket = key % 17;

    entry_t *entry = find_previous_entry_for_key(NULL, ht->buckets[bucket], key);

    // Om listan är tom eller entry är längst fram
    if (entry == NULL)
    {
        // Om listan är tom
        if (ht->buckets[bucket] == NULL)
        {
            ht->buckets[bucket] = entry_create(key, value, NULL);
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
    }

    entry_t *next = entry->next;

    // Om vi hittade en entry med rätt key
    if (entry->next != NULL && entry->next->key == key)
    {
        entry->next->value = value;
        return;
    }

    entry->next = entry_create(key, value, entry->next);
}

/// @brief checks if current entry has matching or a larger key then the input key,
///        iteratively searches the list for until criteria is met or end of list
/// @param prev_entry previous entry to the one currently being investigated
/// @param key input key to insert
/// @param entry current entry thats investigated, checking if it matches or is larger than
///              param key
entry_t *find_previous_entry_for_key(entry_t *prev_entry, entry_t *entry, int key)
{
    if (entry == NULL || entry->key >= key)
    {
        return prev_entry;
    }

    return find_previous_entry_for_key(entry, entry->next, key);
}

entry_t *entry_create(int key, char *value, entry_t *next)
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
    int bucket = key % 17;
    entry_t *entry_front = ht->buckets[bucket];
    entry_t *prev_entry = find_previous_entry_for_key(entry_front, entry_front, key);

    if (prev_entry->next == NULL)
    {
        return NULL;
    }

    if (prev_entry == entry_front && prev_entry->key == key)
    {
        return prev_entry->value;
    }

    if (prev_entry->next->key == key)
    {
        return prev_entry->next->value;
    }
}

/// @brief remove any mapping from key to a value
/// @param ht hash table operated upon
/// @param key key to remove
/// @return the value mapped to by key (FIXME: incomplete)
char *ioopm_hash_table_remove(ioopm_hash_table_t *ht, int key)
{
    entry_t *entry = ioopm_hash_table_lookup(ht, key);
    entry_t *prev_entry = find_previous_entry_for_key(entry, entry, key);

    if (entry != prev_entry)
    {
        prev_entry->next = entry->next;
    }

    char *val = calloc(1, sizeof(entry->value));
    val = strcpy(val, entry->value);

    free(entry->value); // KANSKE ONÖDIGT
    free(entry);
}

/// @brief returns the number of key => value entries in the hash table
/// @param h hash table operated upon
/// @return the number of key => value entries in the hash table
int ioopm_hash_table_size(ioopm_hash_table_t *h)
{
    int amount = 0;

    for (int i = 0; i < 17; i++)
    {
        entry_t *current_entry = h->buckets[i];

        while (current_entry != NULL)
        {
            amount++;
            current_entry = current_entry->next;
        }
    }

    return amount;
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
/// @param h hash table operated upon
void ioopm_hash_table_clear(ioopm_hash_table_t *h)
{
    for (int i = 0; i < 17; i++)
    {
        remove_bucket(h, h->buckets[i]);
    }
}

void remove_bucket(ioopm_hash_table_t *ht, entry_t *entry)
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
int *ioopm_hash_table_keys(ioopm_hash_table_t *h)
{
    for (int i = 0; i < 17; i++)
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
    return NULL;
}

/// @brief return the values for all entries in a hash map (in no particular order, but same as ioopm_hash_table_keys)
/// @param h hash table operated upon
/// @return an array of values for hash table h
char **ioopm_hash_table_values(ioopm_hash_table_t *h)
{
    for (int i = 0; i < 17; i++)
    {
        fprintf(stdout, "bucket %d: ", i);

        entry_t *entry = h->buckets[i];
        while (entry != NULL)
        {
            fprintf(stdout, "%s ", entry->value);
            entry = entry->next;
        }
    }
    return NULL;
}

/// @brief check if a hash table has an entry with a given key
/// @param h hash table operated upon
/// @param key the key sought
bool ioopm_hash_table_has_key(ioopm_hash_table_t *h, int key)
{
    if (ioopm_hash_table_lookup(h, key) != NULL)
    {
        return true;
    }

    return false;
}

/// @brief check if a hash table has an entry with a given value
/// @param h hash table operated upon
/// @param value the value sought
bool ioopm_hash_table_has_value(ioopm_hash_table_t *h, char *value)
{
    for (int i = 0; i < 17; i++)
    {
        entry_t *entry = h->buckets[i];

        while (entry != NULL)
        {
            if (entry->value == value)
            {
                return true;
            }
            entry = entry->next;
        }
    }
    return false;
}

/// @brief check if a predicate is satisfied by all entries in a hash table
/// @param h hash table operated upon
/// @param pred the predicate
/// @param arg extra argument to pred
bool ioopm_hash_table_all(ioopm_hash_table_t *h, ioopm_apply_function pred, void *arg);

/// @brief check if a predicate is satisfied by any entry in a hash table
/// @param h hash table operated upon
/// @param pred the predicate
/// @param arg extra argument to pred
bool ioopm_hash_table_any(ioopm_hash_table_t *h, ioopm_apply_function pred, void *arg);

/// @brief apply a function to all entries in a hash table
/// @param h hash table operated upon
/// @param apply_fun the function to be applied to all elements
/// @param arg extra argument to apply_fun
void ioopm_hash_table_apply_to_all(ioopm_hash_table_t *h, ioopm_apply_function apply_fun, void *arg);