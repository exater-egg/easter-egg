#include <stdio.h>
#include <string.h>
#define BUCKETS 1024

typedef struct 
{
    char* id;
    char* type;
    tableEntry* next;
    /* data */
} tableEntry;

tableEntry* symtable [BUCKETS];
unsigned int symtable_size = 0;

void init_symtable() {
    for (size_t i = 0; i < BUCKETS; i++)
    {
        symtable[i] = NULL;
    }
}

// based on: https://www.geeksforgeeks.org/string-hashing-using-polynomial-rolling-hash-function/
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

void insert_symtable(tableEntry value)
{
    unsigned int idx = polynomialRollingHash(value.id) % BUCKETS;
    // Find head of chain for given key
    tableEntry* head = symtable[idx];

    // Check if key is already present
    while (head != NULL)
    {
        if (strcmp(head->id, value.id))
        {
            head = &value;
            return;
        }
        head = head->next;
    }

    // Insert key in chain
    symtable_size++;
    head = symtable[idx];
    value.next = head;
    symtable[idx] = &value;

    // @TODO: If load factor goes beyond threshold, then
    // double hash table size
}
/// Driver Code
/*int main()
{
    // Given strings
    char* str1 = "josivan";
    char* str2 = "Josivan";

    printf("Hash of \'%s\' = %lld\n", str1, 
      polynomialRollingHash(str1)%512);
    printf("Hash of \'%s\' = %lld\n", str2, 
      polynomialRollingHash(str2)%512);

 
}*/
