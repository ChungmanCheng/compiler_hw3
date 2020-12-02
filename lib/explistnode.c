#include "explistnode.h"

Node* newExpListNode( int firstLine, int firstColumn, ExpListNode* explistnode, ExpNode* expnode, int lastLine, int lastColumn ){
    ExpListNode* temp = (ExpListNode*) malloc ( sizeof(ExpListNode) );
    temp->explistnode = explistnode;
    temp->expnode = expnode;
    temp->node.type = _ExpListNode;
    temp->node.visit = ExpListNode_visit;
    temp->node.loc.first_line = firstLine;
    temp->node.loc.first_column = firstColumn;
    temp->node.loc.last_line = lastLine;
    temp->node.loc.last_column = lastColumn;

    return temp;
}

void ExpListNode_visit(void* node){

    return;
}
