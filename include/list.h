#ifndef _LIST_H
#define _LIST_H

#include <stdio.h>
#include <stdlib.h>

#include "info.h"

typedef struct SymbolObj{
    char* id;
    int scope;
    char* type;
} symbolobj;

typedef struct List{
    symbolobj data;
    struct List* next;
    struct List* prev;
    void (*push_back)(struct List*, struct List*);
} list;

void list_push_back(list*, list*);

list* newlist(char*, int, char*);

void list_printTable(list*);

#endif