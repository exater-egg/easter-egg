#ifndef _SYMTABLE_H_
#define _SYMTABLE_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BUCKETS 1024

typedef struct TableEntryStruct
{
    char* id;
    char* type;
    struct TableEntryStruct* next;
    /* data */
} tableEntry;

void init_symtable();

// based on: https://www.geeksforgeeks.org/string-hashing-using-polynomial-rolling-hash-function/
unsigned long long polynomialRollingHash(
    char* str);

void insert_symtable(tableEntry value);

char* lookup_type(char* id);

#endif//
