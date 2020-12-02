#ifndef _ADDNODE_H
#define _ADDNODE_H

#include "ast.h"

typedef struct addnode{
    Node node;
    int positive;   // 1: positive, 0: negative
    
} AddNode;

Node* newAddNode( int, int, int, int, int );

void AddNode_visit(void*);

#endif