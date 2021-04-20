#ifndef _SYMTABLE_H_
#define _SYMTABLE_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BUCKETS 1024

typedef struct TableEntryStruct
{
    char* id;
    char* parent;
    char* type;
    struct TableEntryStruct* next;
    /* data */
} tableEntry;

typedef struct TypeEntryStruct
{
    char* id;
    char* parent;
    struct TypeEntryStruct* next;
} typeEntry;

void init_symtable();
void init_typetable();

// based on: https://www.geeksforgeeks.org/string-hashing-using-polynomial-rolling-hash-function/
unsigned long long polynomialRollingHash(char* str);

void insert_symtable(tableEntry value);
void insert_typetable(typeEntry value);

char* lookup_type(char* id);
int check_types(char* rsh, char* lsh);
int check_type(char* type);

#endif//
