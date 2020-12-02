#include "tailnode.h"

Node* newTailNode( int firstLine, int firstColumn, ExpNode* expnode, TailNode* tailnode, int lastLine, int lastColumn ){
    TailNode* temp = (TailNode*) malloc ( sizeof(TailNode) );
    temp->expnode = expnode;
    temp->tailnode = tailnode;
    temp->node.type = _TailNode;
    temp->node.visit = TailNode_visit;
    temp->node.loc.first_line = firstLine;
    temp->node.loc.first_column = firstColumn;
    temp->node.loc.last_line = lastLine;
    temp->node.loc.last_column = lastColumn;

    return temp;
}

void TailNode_visit(void* node){

    return;
}
