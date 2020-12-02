#include "numnode.h"

Node* newNumNode( int firstLine, int firstColumn, int type, double num, char* string, int lastLine, int lastColumn ){
    NumNode* temp = (NumNode*) malloc ( sizeof(NumNode) );
    temp->type = type;
    if (type == 2){
        // sscanf(string, "%llfE%llf", temp->num, temp->exp);
    }else{
        temp->num = num;
        temp->exp = 0.0f;
    }
    temp->node.type = _NumNode;
    temp->node.visit = NumNode_visit;
    temp->node.loc.first_line = firstLine;
    temp->node.loc.first_column = firstColumn;
    temp->node.loc.last_line = lastLine;
    temp->node.loc.last_column = lastColumn;

    return temp;
};

void NumNode_visit(void* node){

    return;
}
