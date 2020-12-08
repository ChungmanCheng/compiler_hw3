#include "procedstatementnode.h"

Node* newProcedStatementNode( int firstLine, int firstColumn, char* id, ExpListNode* explistnode, int lastLine, int lastColumn ){
    ProcedStatementNode* temp = (ProcedStatementNode*) malloc ( sizeof(ProcedStatementNode) );
    temp->id = id;
    temp->explistnode = explistnode;
    temp->node.type = _ProcedStatementNode;
    temp->node.visit = ProcedStatementNode_visit;
    temp->node.loc.first_line = firstLine;
    temp->node.loc.first_column = firstColumn;
    temp->node.loc.last_line = lastLine;
    temp->node.loc.last_column = lastColumn;

    return temp;
}

void* ProcedStatementNode_visit(void* node){

    return 0;
}
