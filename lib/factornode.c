#include "factornode.h"
#include "tailnode.h"
#include "explistnode.h"
#include "expnode.h"
#include "numnode.h"

struct factornode{
    Node node;
    int type;
    char* id;
    TailNode* tailnode;
    ExpListNode* explistnode;
    NumNode* num;
    ExpNode* expnode;
    struct factornode* factornode;
    
};

Node* newFactorNode( int firstLine, int firstColumn, int type, char* id, ExpListNode* explistnode, NumNode* numnode, ExpNode* expnode, FactorNode* factornode, int lastLine, int lastColumn ){
    FactorNode* temp = (FactorNode*) malloc ( sizeof(FactorNode) );
    temp->type = type;
    temp->id = id;
    temp->explistnode = explistnode;
    temp->num = numnode;
    temp->expnode = expnode;
    temp->factornode = factornode;
    temp->node.type = _FactorNode;
    temp->node.visit = FactorNode_visit;
    temp->node.loc.first_line = firstLine;
    temp->node.loc.first_column = firstColumn;
    temp->node.loc.last_line = lastLine;
    temp->node.loc.last_column = lastColumn;

    return temp;
}

void FactorNode_visit(void* node){

    return;
}
