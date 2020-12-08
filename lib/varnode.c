#include "varnode.h"
#include "list.h"

extern list* listRoot;
extern int scope;

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

void* VarNode_visit(void* node){
    VarNode* temp = (VarNode*) node;
    
    list* listTemp = NULL;
    int datatype = -1;
    symbolobj* currTemp = NULL;

    if ( GetList( listRoot, &listTemp, temp->id ) ){
        if ( (listTemp->nodeType == Function) && ( ((funcsymbolobj*)listTemp->data)->check == 1 ) )
            fprintf(stderr, ASSIG_TYPE, temp->node.loc.first_line, temp->node.loc.first_column);

        currTemp = listTemp->data;
        while (currTemp->type == Array){
            currTemp = ((arraysymbolobj*)currTemp)->data;
        }
        datatype = currTemp->type;
    }else{
        // undeclared variables
        fprintf(stderr, UNDEC_VAR, temp->node.loc.first_line, temp->node.loc.first_column, temp->id );
    }
    // check id tail
    if (temp->tailnode != 0){
        temp->tailnode->node.visit(temp->tailnode);
    }


    return datatype;
}
