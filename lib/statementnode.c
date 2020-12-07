#include "statementnode.h"


Node* newStatementNode( int firstLine, int firstColumn, int type, VarNode* varnode, ExpNode* expnode, ProcedStatementNode* procedstatementnode, CompoundStatementNode* compoundstatementnode, StatementNode* statementnode1, StatementNode* statementnode2, int lastLine, int lastColumn ){
    StatementNode* temp = (StatementNode*) malloc ( sizeof(StatementNode) );
    temp->type = type;
    temp->varnode = varnode;
    temp->expnode = expnode;
    temp->procedstatementnode = procedstatementnode;
    temp->compoundstatementnode = compoundstatementnode;
    temp->statementnode1 = statementnode1;
    temp->statementnode2 = statementnode2;
    temp->node.type = _StatementNode;
    temp->node.visit = StatementNode_visit;
    temp->node.loc.first_line = firstLine;
    temp->node.loc.first_column = firstColumn;
    temp->node.loc.last_line = lastLine;
    temp->node.loc.last_column = lastColumn;

    return temp;
}

void StatementNode_visit(void* node){
    StatementNode* temp = (StatementNode*) node;
    

    return;
}
