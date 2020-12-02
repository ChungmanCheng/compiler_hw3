#include "varnode.h"

Node* newVarNode( int firstLine, int firstColumn, char* id, TailNode* tailnode, int lastLine, int lastColumn ){
    VarNode* temp = (VarNode*) malloc ( sizeof(VarNode) );
    temp->id = id;
    temp->tailnode = tailnode;
    temp->node.type = _VarNode;
    temp->node.visit = VarNode_visit;
    temp->node.loc.first_line = firstLine;
    temp->node.loc.first_column = firstColumn;
    temp->node.loc.last_line = lastLine;
    temp->node.loc.last_column = lastColumn;

    return temp;
}

void VarNode_visit(void* node){

    return;
}
