#ifndef _LIST_H
#define _LIST_H

#include <stdio.h>
#include <stdlib.h>

#include "info.h"

typedef enum{ Int, Void, Real, String, Array } returnType;

typedef enum{ Function, Procedure, Data, Array_Data } dataType;

typedef struct SymbolObj{
    returnType type;
    struct symbolobj* next;
} symbolobj;

typedef struct ArraySymbolObj{
    returnType type;
    symbolobj* data;
    int start;
    int end;
}arraysymbolobj;

typedef struct List{
    dataType nodeType;
    char* id;
    int scope;
    symbolobj* data;
    struct List* next;
    struct List* prev;
    void (*push_back)(struct List*, struct List*);
} list;

void list_push_back(list*, list*);

list* newdatalist(char*, int, returnType, dataType);

list* newarraylist(char*, int, returnType, dataType);

void list_printTable(list*);

#endif