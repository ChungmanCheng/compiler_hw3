#include "factornode.h"
#include "list.h"

extern list* listRoot;
extern int scope;

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

        if ( checkList(listRoot, temp->id, scope, Data) ){

        }else{
            fprintf(stderr, UNDEC_VAR, temp->node.loc.first_line, temp->node.loc.first_column, temp->id );
        }

        if (temp->tailnode != 0)
            temp->tailnode->node.visit(temp->tailnode);
        break;

    case 1:
        // IDENTIFIER LPAREN expression_list RPAREN

        if ( checkList(listRoot, temp->id, scope, Data) ){

        }else{
            fprintf(stderr, UNDEC_VAR, temp->node.loc.first_line, temp->node.loc.first_column, temp->id );
        }
        
        if (temp->explistnode != 0)
            temp->explistnode->node.visit(temp->explistnode);

        break;

    case 2:
        // num

        temp->num->node.visit(temp->num);
        break;
    
    case 3:
        // LITERALSTR

        
        break;

    case 4:
        // LPAREN expression RPAREN

        if (temp->expnode != 0)
            temp->expnode->node.visit(temp->expnode);
        break;

    case 5:
        // NOT factor

        if (temp->factornode != 0)
            temp->factornode->node.visit(temp->factornode);
        break;

    case 6:
        // SUBOP factor

        if (temp->factornode != 0)
            temp->factornode->node.visit(temp->factornode);
        break;
    
    default:
        break;
    }

    return 0;
}
