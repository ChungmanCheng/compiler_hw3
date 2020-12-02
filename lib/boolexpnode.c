#include "boolexpnode.h"

Node* newBoolExpNode( int firstLine, int firstColumn, SimpleExpNode* first, RelopNode* relop, SimpleExpNode* least, int lastLine, int lastColumn ){
    BoolExpNode* temp = (BoolExpNode*) malloc ( sizeof(BoolExpNode) );
    temp->first = first;
    temp->relop = relop;
    temp->least = least;
    temp->node.type = _BoolExpNode;
    temp->node.visit = BoolExpNode_visit;
    temp->node.loc.first_line = firstLine;
    temp->node.loc.first_column = firstColumn;
    temp->node.loc.last_line = lastLine;
    temp->node.loc.last_column = lastColumn;

    return temp;
}

void BoolExpNode_visit(void* node){

}
