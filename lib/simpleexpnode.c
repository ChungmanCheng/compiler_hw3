#include "simpleexpnode.h"

Node* newSimpleExpNode( int firstLine, int firstColumn, SimpleExpNode* simpleexpnode, AddNode* addnode, TermNode* termnode, int lastLine, int lastColumn ){
    SimpleExpNode* temp = (SimpleExpNode*) malloc ( sizeof(SimpleExpNode) );
    temp->termnode = termnode;
    temp->simpleexpnode = simpleexpnode;
    temp->addnode = addnode;
    temp->node.type = _SimpleExpNode;
    temp->node.visit = SimpleExpNode_visit;
    temp->node.loc.first_line = firstLine;
    temp->node.loc.first_column = firstColumn;
    temp->node.loc.last_line = lastLine;
    temp->node.loc.last_column = lastColumn;

    return temp;
}

void SimpleExpNode_visit(void* node){

    return;
}
