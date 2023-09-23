#ifndef CS165_HASH_TABLE // This is a header guard. It prevents the header from being included more than once.
#define CS165_HASH_TABLE  

typedef unsigned int keyType;
typedef unsigned int valType;

typedef struct table_item {
    keyType key;
    valType val;
    struct table_item* next;
} table_item;

typedef struct hashtable {
// define the components of the hash table here (e.g. the array, bookkeeping for number of elements, etc)
    unsigned int num_elements;
    unsigned int capacity;
    table_item** store;
} hashtable;

int allocate(hashtable** ht, int size);
int put(hashtable* ht, keyType key, valType value);
int get(hashtable* ht, keyType key, valType *values, int num_values, int* num_results);
int erase(hashtable* ht, keyType key);
int deallocate(hashtable* ht);

#endif
