#ifndef _OPTIONALSTATEMENTSNODE_H
#define _OPTIONALSTATEMENTSNODE_H

#include "ast.h"
#include "statementlistnode.h"

typedef struct optionalstatementsnode{
    Node node;
    StatementListNode* statementlistnode;

} OptionalStatementSNode;

Node* newOptionalStatementSNode( int, int, StatementListNode*, int, int );

void OptionalStatementSNode_visit(void*);

#endif