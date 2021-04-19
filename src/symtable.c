#include "symtable.h"

tableEntry* symtable [BUCKETS];
unsigned int symtable_size = 0;

unsigned long long polynomialRollingHash(char* str) {
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
        symtable[i] = NULL;
}


void insert_symtable(tableEntry value) {
    unsigned int idx = polynomialRollingHash(value.id) % BUCKETS;
    // Find head of chain for given key
    tableEntry* head = symtable[idx];
    tableEntry* next;

    // Check if key is already present
    while (head != NULL)
    {
        if (!strcmp(head->id, value.id))
        {
            next = (tableEntry*) malloc(sizeof(tableEntry));
            next->id = value.id;
            next->type = value.type;
            return;
        }
        head = head->next;
    }

    // Insert key in chain
    symtable_size++;
    next = (tableEntry*) malloc(sizeof(tableEntry));
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
    while (head != NULL) {
        if (!strcmp(head->id, id)) {
            return head->type;
        }
        head = head->next;
    }

    return NULL;
}

/**
 * TABLE OF TYPES
 */
typeEntry* typetable [BUCKETS];
unsigned int typetable_size = 0;

void init_typetable() {
    for (size_t i = 0; i < BUCKETS; i++)
        typetable[i] = NULL;
}

void insert_typetable(typeEntry value) {
    unsigned int idx = polynomialRollingHash(value.id) % BUCKETS;
    // Find head of chain for given key
    typeEntry* head = symtable[idx];
    typeEntry* next;

    // Check if key is already present
    while (head != NULL)
    {
        if (!strcmp(head->id, value.id))
        {
            next = (typeEntry*) malloc(sizeof(typeEntry));
            next->id = value.id;
            next->parent = value.parent;
            return;
        }
        head = head->next;
    }

    // Insert key in chain
    typetable_size++;
    next = (typeEntry*) malloc(sizeof(typeEntry));
    next->id = value.id;
    next->parent = value.parent;
    next->next = symtable[idx];
    symtable[idx] = next;
}

/**
 * @brief Check if rhs is subtype of lsh
 */
int check_types(char* rsh, char* lsh){
    unsigned int idx1 = polynomialRollingHash(rsh) % BUCKETS;
    unsigned int idx2 = polynomialRollingHash(rsh) % BUCKETS;

    typeEntry* type1 = typetable[idx1];
    typeEntry* type2 = typetable[idx1];

    // Find rsh struct
    while (type1 != NULL){
        if (!strcmp(type1->id, rsh)){
            // Find lsh struct
            while (type2 != NULL){
                if (!strcmp(type2->id, rsh))
                    if (!strcmp(type1->id, type2->id))
                        return 1;
                    else 
                        return check_types(type1->parent, type2->id);
            }
        }
        type1 = type1->next;
    }
    return 0;
}
/**
 * @brief Returns 1 if type is found, 0 otherwise.
 */
int check_type(char* type){
    unsigned int idx = polynomialRollingHash(type) % BUCKETS;

    typeEntry* head = typetable[idx];

    // Check if key is already present
    while (head != NULL) {
        if (!strcmp(head->id, type)) {
            1;
        }
        head = head->next;
    }

    return 0;
}
