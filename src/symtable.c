#include "symtable.h"

tableEntry* symtable [BUCKETS];
unsigned int symtable_size = 0;

unsigned long long polynomialRollingHash(
    char* str)
{
    // P and M
    int p = 31;
    int m = 1e9 + 9;
    long long power_of_p = 1;
    long long hash_val = 0;
 
    // Loop to calculate the hash value
    // by iterating over the elements of string
    for (int i = 0; i < strlen(str); i++) {
        hash_val
            = (hash_val
               + (str[i] - 'a' + 1) * power_of_p)
              % m;
        power_of_p
            = (power_of_p * p) % m;
    }
    return hash_val;
}
void init_symtable() {
    for (size_t i = 0; i < BUCKETS; i++)
    {
        symtable[i] = NULL;
    }
}

void insert_symtable(tableEntry value)
{
    unsigned int idx = polynomialRollingHash(value.id) % BUCKETS;
    // Find head of chain for given key
    tableEntry* head = symtable[idx];
    tableEntry* next;

    // Check if key is already present
    while (head != NULL)
    {
        if (!strcmp(head->id, value.id))
        {
            next = malloc(sizeof(tableEntry*));
            next->id = value.id;
            next->type = value.type;
            return;
        }
        head = head->next;
    }

    // Insert key in chain
    symtable_size++;
    next = malloc(sizeof(tableEntry*));
    next->id = value.id;
    next->type = value.type;
    next->next = symtable[idx];
    symtable[idx] = next;

    // @TODO: If load factor goes beyond threshold, then
    // double hash table size
}

char* lookup_type(char* id){
    unsigned int idx = polynomialRollingHash(id) % BUCKETS;

    tableEntry* head = symtable[idx];

    // Check if key is already present
    while (head != NULL)
    {
        if (!strcmp(head->id, id))
        {
            return head->type;
        }
        head = head->next;
    }

    return NULL;
}
