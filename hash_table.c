
#include <stdio.h>
#include <stdlib.h>
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
}

/// @brief add key => value entry in hash table ht
/// @param ht hash table operated upon
/// @param key key to insert
/// @param value value to insert
void ioopm_hash_table_insert(ioopm_hash_table_t *ht, int key, char *value)
{
    int bucket = key % 17;

    entry_t *entry = find_previous_entry_for_key(ht->buckets[bucket], ht->buckets[bucket], key);
    entry_t *next = entry->next;

    if (entry != NULL && next->key == key)
    {
        next->value = value;
    }
    else
    {
        // IF FRONT THEN DON'T POINT TO ENTRY THAT DOESN'T EXIST, INSTEAD JUST CREATE ENTRY
        if (entry == ht->buckets[bucket])
        {
            create_entry(key, value, next);
        }
        else
        {
            entry->next = create_entry(key, value, next);
        }
    }
}
// ITERATIVE
entry_t *find_previous_entry_for_key(entry_t *prev_entry, entry_t *entry, int key)
{
    if (entry->key >= key)
    {
        return prev_entry;
    }
    find_previous_entry_for_key(entry, entry->next, key);
}

entry_t *entry_create(int key, char *value, entry_t *next)
{
    entry_t *new_entry = calloc(1, sizeof(entry_t));

    if (new_entry == NULL)
    {
        perror("entry_create: Couldnt calloc\n");
    }

    new_entry->key = key;
    new_entry->value = value;
    new_entry->next = next;

    return new_entry;
}

/// @brief lookup value for key in hash table ht
/// @param ht hash table operated upon
/// @param key key to lookup
/// @return the value mapped to by key (FIXME: incomplete)
void *ioopm_hash_table_lookup(ioopm_hash_table_t *ht, int key);

/// @brief remove any mapping from key to a value
/// @param ht hash table operated upon
/// @param key key to remove
/// @return the value mapped to by key (FIXME: incomplete)
char *ioopm_hash_table_remove(ioopm_hash_table_t *ht, int key);