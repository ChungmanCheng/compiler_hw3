#include "expnode.h"

Node* newExpNode( int firstLine, int firstColumn, ExpNode* first, int op, ExpNode* least, int lastLine, int lastColumn ){
    ExpNode* temp = (ExpNode*) malloc ( sizeof(ExpNode) );
    temp->first = first;
    temp->least = least;
    temp->type = op;
    temp->node.type = _ExpNode;
    temp->node.visit = ExpNode_visit;
    temp->node.loc.first_line = firstLine;
    temp->node.loc.first_column = firstColumn;
    temp->node.loc.last_line = lastLine;
    temp->node.loc.last_column = lastColumn;

    return temp;
}

void ExpNode_visit(void* node){

}
