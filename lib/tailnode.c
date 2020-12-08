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

void* TailNode_visit(void* node){
    TailNode* temp = (TailNode*) node;

    // debug
    // fprintf(stderr, "%d: %d has an Node\n", temp->node.loc.first_line, temp->node.loc.first_column);

    if (temp->expnode != 0)
        temp->expnode->node.visit(temp->expnode);

    if (temp->tailnode != 0)
        temp->tailnode->node.visit(temp->tailnode);

    return 0;
}
