#include "termnode.h"

Node* newTermNode( int firstLine, int firstColumn, TermNode* termnode, MulNode* mulnode, FactorNode* factornode, int lastLine, int lastColumn ){
    TermNode* temp = (TermNode*) malloc ( sizeof(TermNode) );
    temp->termnode = termnode;
    temp->mulnode = mulnode;
    temp->factornode = factornode;
    temp->node.type = _TermNode;
    temp->node.visit = TermNode_visit;
    temp->node.loc.first_line = firstLine;
    temp->node.loc.first_column = firstColumn;
    temp->node.loc.last_line = lastLine;
    temp->node.loc.last_column = lastColumn;

    return temp;
}

void TermNode_visit(void* node){

}
