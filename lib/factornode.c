#include "factornode.h"


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

void* FactorNode_visit(void* node){
    FactorNode* temp = (FactorNode*)node;
    switch (temp->type)
    {
    case 0:
        // IDENTIFIER tail

        break;

    case 1:
        // IDENTIFIER LPAREN expression_list RPAREN

        break;

    case 2:
        // num

        break;
    
    case 3:
        // LITERALSTR

        break;

    case 4:
        // LPAREN expression RPAREN

        break;

    case 5:
        // NOT factor

        break;

    case 6:
        // SUBOP factor

        break;
    
    default:
        break;
    }

    return;
}
