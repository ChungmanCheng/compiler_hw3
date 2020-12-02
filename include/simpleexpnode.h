#ifndef _SIMPLEEXPNODE_H
#define _SIMPLEEXPNODE_H

#include "ast.h"
#include "simpleexpnode.h"
#include "addnode.h"
#include "termnode.h"

typedef struct simpleexpnode{
    Node node;
    TermNode* termnode;
    struct simpleexpnode* simpleexpnode;
    AddNode* addnode;

} SimpleExpNode;

Node* newSimpleExpNode( int, int, SimpleExpNode*, AddNode*, TermNode*, int, int );

void SimpleExpNode_visit(void*);

#endif