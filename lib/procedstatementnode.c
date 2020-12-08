#include "procedstatementnode.h"
#include "list.h"

extern list* listRoot;
extern int scope;

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
    ProcedStatementNode* temp = (ProcedStatementNode*) node;

    // debug
    // fprintf(stderr, "%d: %d has an Node\n", temp->node.loc.first_line, temp->node.loc.first_column);

    list* listTemp;
    if ( GetList( listRoot, &listTemp, temp->id ) ){
        // variable is declared

    }else{
        // undeclared variables
        fprintf(stderr, UNDEC_FUN, temp->node.loc.first_line, temp->node.loc.first_column, temp->id );
    }

    if (temp->explistnode != 0)
        temp->explistnode->node.visit(temp->explistnode);

    return -1;
}
