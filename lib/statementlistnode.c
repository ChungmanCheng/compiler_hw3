#include "statementlistnode.h"

Node* newStatementListNode( int firstLine, int firstColumn, StatementListNode* statementlistnode, StatementNode* statementnode, int lastLine, int lastColumn ){
    StatementListNode* temp = (StatementListNode*) malloc ( sizeof(StatementListNode) );
    temp->nextList = statementlistnode;
    temp->statementnode = statementnode;
    temp->node.type = _StatementListNode;
    temp->node.visit = StatementListNode_visit;
    temp->node.loc.first_line = firstLine;
    temp->node.loc.first_column = firstColumn;
    temp->node.loc.last_line = lastLine;
    temp->node.loc.first_column = lastColumn;

    return temp;
}

void StatementListNode_visit(void* node){

}
