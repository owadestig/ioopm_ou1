#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "linked_list.h"

struct list
{
    cell_t *first;
    cell_t *last;
    int length;
};

struct cell
{
    int key;
    void *value;
    cell_t *prev;
    cell_t *next;
};

union elem
{ 
  int i;
  unsigned int u;
  bool b;
  float f;
  void *p;
  /// BYT UT VOID VALUE I CELL TILL EN ELEM
};


/// @brief Creates a new empty list
/// @return an empty linked list
ioopm_list_t *ioopm_linked_list_create()
{
    // Allocate memory for the list head.
    ioopm_list_t *l = calloc(1, sizeof(ioopm_list_t));

    l->last = calloc(1, sizeof(cell_t));
    l->first = calloc(1, sizeof(cell_t));

    l->first->next = l->last;
    l->last->prev = l->first->next;
    l->length = 0;

    return l;
}

/// @brief Tear down the linked list and return all its memory (but not the memory of the elements)
/// @param list the list to be destroyed
void ioopm_linked_list_destroy(ioopm_list_t *list);

/// @brief Insert at the end of a linked list in O(1) time
/// @param list the linked list that will be appended
/// @param value the value to be appended
void ioopm_linked_list_append(ioopm_list_t *list, int value)
{
    cell_t *new = calloc(1, sizeof(cell_t));
    new->value = value;
    list->first->next->prev = new;
    new->next = list->first->next;
    list->first->next = new;
    new->prev = list->first;
    list->length++;
}

/// @brief Insert at the front of a linked list in O(1) time
/// @param list the linked list that will be prepended
/// @param value the value to be appended
void ioopm_linked_list_prepend(ioopm_list_t *list, int value)
{
    cell_t *new = calloc(1, sizeof(cell_t));
    new->value = value;
    list->last->prev->next = new;
    new->prev = list->last->prev;
    list->last->prev = new;
    new->next = list->last;
    list->length++;
}

/// @brief Insert an element into a linked list in O(n) time.
/// The valid values of index are [0,n] for a list of n elements,
/// where 0 means before the first element and n means after
/// the last element.
/// @param list the linked list that will be extended
/// @param index the position in the list
/// @param value the value to be appended
void ioopm_linked_list_insert(ioopm_list_t *list, int index, int value)
{
    cell_t *next = ioopm_linked_list_get(list, index);

    cell_t *prev = next->prev;

    cell_t *new = calloc(1, sizeof(cell_t));
    prev->next = new;
    new->prev = prev;
    new->next = next;
    next->prev = new;
    list->length++;
}

/// @brief Remove an element from a linked list in O(n) time.
/// The valid values of index are [0,n-1] for a list of n elements,
/// where 0 means the first element and n-1 means the last element.
/// @param list the linked list that will be extended
/// @param index the position in the list
/// @param value the value to be appended
/// @return the value returned (*)
int ioopm_linked_list_remove(ioopm_list_t *list, int index)
{
    cell_t *entry = ioopm_linked_list_get(list, index + 1);

    entry->prev->next = entry->next;
    entry->next->prev = entry->prev;
    free(entry);
    list->length--;
}

/// @brief Retrieve an element from a linked list in O(n) time.
/// The valid values of index are [0,n-1] for a list of n elements,
/// where 0 means the first element and n-1 means the last element.
/// @param list the linked list that will be extended
/// @param index the position in the list
/// @return the value at the given position
int ioopm_linked_list_get(ioopm_list_t *list, int index)
{
    cell_t *entry = linked_list_lookup(list, index);
    return entry->value;
}

/// @brief Retrieve an element from a linked list in O(n) time.
/// The valid values of index are [0,n-1] for a list of n elements,
/// where 0 means the first element and n-1 means the last element.
/// @param list the linked list that will be extended
/// @param index the position in the list
/// @return the entry at the given position
static void *linked_list_lookup(ioopm_list_t *list, int index)
{
    if (index > list->length)
    {
        fprintf(stderr, "index %d exceeds list length %d", index, list->length);
        return NULL;
    }

    cell_t *entry = list->first;

    int i = 0;

    for (int i = 0; i <= index; i++)
    {
        entry = entry->next;
    }

    return entry;
}

/// @brief Test if an element is in the list
/// @param list the linked list
/// @param element the element sought
/// @return true if element is in the list, else false
bool ioopm_linked_list_contains(ioopm_list_t *list, int element)
{
    cell_t *entry = list->first->next;

    for (int i = 0; i < list->length; i++)
    {
        if (entry->value == element)
        {
            return true;
        }
        entry = entry->next;
    }

    return false;
}

/// @brief Lookup the number of elements in the linked list in O(1) time
/// @param list the linked list
/// @return the number of elements in the list
int ioopm_linked_list_size(ioopm_list_t *list)
{
    return list->length;
}

/// @brief Test whether a list is empty or not
/// @param list the linked list
/// @return true if the number of elements int the list is 0, else false
bool ioopm_linked_list_is_empty(ioopm_list_t *list)
{
    return list->first->next == list->last;
}
/// @brief Remove all elements from a linked list
/// @param list the linked list
void ioopm_linked_list_clear(ioopm_list_t *list)
{
    while (list->first->next != list->last)
    {
        ioopm_linked_list_remove(list, 0);
    }
}

/// @brief Test if a supplied property holds for all elements in a list.
/// The function returns as soon as the return value can be determined.
/// @param list the linked list
/// @param prop the property to be tested (function pointer)
/// @param extra an additional argument (may be NULL) that will be passed to all internal calls of prop
/// @return true if prop holds for all elements in the list, else false
bool ioopm_linked_list_all(ioopm_list_t *list, ioopm_char_predicate prop, void *extra)
{
    cell_t *entry = list->first;

    while (entry != NULL)
    {
        if (!rop(entry->key, entry->value, extra))
        {
            return false;
        }
        entry = entry->next;
    }
    return true;
}

/// @brief Test if a supplied property holds for any element in a list.
/// The function returns as soon as the return value can be determined.
/// @param list the linked list
/// @param prop the property to be tested
/// @param extra an additional argument (may be NULL) that will be passed to all internal calls of prop
/// @return true if prop holds for any elements in the list, else false
bool ioopm_linked_list_any(ioopm_list_t *list, ioopm_char_predicate prop, void *extra)
{
    cell_t *entry = list->first;

    while (entry != NULL)
    {
        if (prop(entry->key, entry->value, extra))
        {
            return true;
        }
        entry = entry->next;
    }
    return false;
}

/// @brief Apply a supplied function to all elements in a list.
/// @param list the linked list
/// @param fun the function to be applied
/// @param extra an additional argument (may be NULL) that will be passed to all internal calls of fun
void ioopm_linked_apply_to_all(ioopm_list_t *list, ioopm_apply_char_function fun, void *extra)
{
    fun(0, list_ (list), extra);
}
