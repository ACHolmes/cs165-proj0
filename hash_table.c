#include "hash_table.h"
#include "stdlib.h"
#include <stdio.h>

// Initialize the components of a hashtable.
// The size parameter is the expected number of elements to be inserted.
// This method returns an error code, 0 for success and -1 otherwise (e.g., if the parameter passed to the method is not null, if malloc fails, etc).
int allocate(hashtable** ht, int size) {
    
    // Allocate new hashtable struct
    hashtable* new_table = malloc(sizeof(hashtable));
    
    // Check for malloc errors
    if (!(new_table)){
        return -1;
    }

    // Allocate the actual store
    table_item** store = calloc(size, sizeof(table_item*));
    if (!store) {
        free(new_table);
        return -1;
    }

    // Make the hastable actually point to the store
    new_table->store = store;

    // Set table capacity
    new_table->capacity = size;
    
    // Put a pointer to the new hashtable at the address stored by ht
    *ht = new_table;
    return 0;
}


unsigned int hash(keyType key, unsigned int size)
{
    return key % size;

    // unsigned long hash = 5381;
    // int c;

    // while ( (c = *str++) )
    // {
    //     hash = ((hash << 5) + hash) + c; 
    // }
    // return hash;
}

// This method inserts a key-value pair into the hash table.
// It returns an error code, 0 for success and -1 otherwise (e.g., if malloc is called and fails).
int put(hashtable* ht, keyType key, valType value) {

    unsigned int index = hash(key, ht->capacity);
    table_item* new_item = malloc(sizeof(table_item));
    if (!new_item) {
        return -1;
    }

    new_item->key = key;
    new_item->val = value;

    new_item->next = ht->store[index];
    ht->store[index] = new_item;
    
    return 0;
}

// This method retrieves entries with a matching key and stores the corresponding values in the
// values array. The size of the values array is given by the parameter
// num_values. If there are more matching entries than num_values, they are not
// stored in the values array to avoid a buffer overflow. The function returns
// the number of matching entries using the num_results pointer. If the value of num_results is greater than
// num_values, the caller can invoke this function again (with a larger buffer)
// to get values that it missed during the first call. 
// This method returns an error code, 0 for success and -1 otherwise (e.g., if the hashtable is not allocated).
int get(hashtable* ht, keyType key, valType *values, int num_values, int* num_results) {
    unsigned int pos = hash(key, ht->capacity);
    *num_results = 0;
    
    for (table_item* cur = ht->store[pos]; cur != NULL; cur = cur->next) {
        if (*num_results < num_values) {
            values[*num_results] = cur->val;
        }
        *num_results = *num_results + 1;
    }
    return 0;
}

// This method erases all key-value pairs with a given key from the hash table.
// It returns an error code, 0 for success and -1 otherwise (e.g., if the hashtable is not allocated).
int erase(hashtable* ht, keyType key) {
    (void) ht;
    (void) key;
    return 0;
}

// This method frees all memory occupied by the hash table.
// It returns an error code, 0 for success and -1 otherwise.
int deallocate(hashtable* ht) {
    // This line tells the compiler that we know we haven't used the variable
    // yet so don't issue a warning. You should remove this line once you use
    // the parameter.
    for (unsigned int pos = 0; pos < ht->capacity; pos++) {
        table_item* cur = ht->store[pos];
        table_item* tmp;
        while (cur) {
            tmp=cur;
            cur = cur->next;
            free(tmp);
        }
    }
    free(ht);
    // (void)ht;
    return 0;
}
