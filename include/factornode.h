#ifndef _FACTORNODE_H
#define _FACTORNODE_H

#include "ast.h"

typedef struct factornode FactorNode;

// Node* newFactorNode( int, int, int, char*, ExpListNode*, NumNode*, ExpNode*, FactorNode*, int, int );

void FactorNode_visit(void*);

#endif