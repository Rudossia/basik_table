#ifndef TABLE

#define TABLE

#define MAX_READ_SIZE 120

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <readline/readline.h>
#include <readline/history.h>

typedef char* KeyType;
typedef char* InfoType;

typedef struct KeySpace {
    KeyType key;
    InfoType info;
    struct KeySpace* next;
} KeySpace;

typedef struct Table {
    KeySpace* ks;
} Table;

KeyType createKey(KeyType k);
InfoType createInfo(InfoType k);
KeySpace* createKeySpace(KeyType k, InfoType i);


void freeKeySpace(KeySpace* ks);
Table* createTable();

void freeTable(Table* t);
KeySpace* insert(Table* t, KeyType k, InfoType i);

void printTable(Table* t);
void delete(Table* t, KeyType k);

void search_info(Table* t, KeyType k);
Table* my_task(Table* t, KeyType start, KeyType end);



#endif
