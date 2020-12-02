#include <stdlib.h>

#include "subdeclarnode.h"
#include "list.h"

extern list* listRoot;
extern int scope;

Node* newSubDeclarNode( int firstLine, int firstColumn, SubHeadNode* subheadnode, DeclarNode* declarnode, SubDeclarSNode* subdeclarsnode, CompoundStatementNode* compoundstatementnode, int lastLine, int lastColumn ){
    SubDeclarNode* temp = (SubDeclarNode*) malloc ( sizeof(SubDeclarNode) );
    temp->head = subheadnode;
    temp->declarnode = declarnode;
    temp->subdeclarsnode = subdeclarsnode;
    temp->compoundstatementnode = compoundstatementnode;
    temp->node.type = _SubDeclarNode;
    temp->node.visit = SubDeclarNode_visit;
    temp->node.loc.first_line = firstLine;
    temp->node.loc.first_column = firstColumn;
    temp->node.loc.last_line = lastLine;
    temp->node.loc.last_column = lastColumn;

    return temp;
};

void SubDeclarNode_visit(void* node){
    SubDeclarNode* temp = (SubDeclarNode*) node;

    if (temp->head != NULL){
        if (temp->head->type){
            // PROCEDURE

        }else{
            // FUNCTION

        }
    }
    
    if (temp->declarnode != NULL){
        // create a scope
        SHOW_NEWSCP();
        scope++;

        temp->declarnode->node.visit(temp->declarnode);

        SHOW_CLSSCP();
        SHOW_SYMTAB_HEAD();
        // print table
        list_printTable(listRoot);
        SHOW_SYMTAB_TAIL();
        scope--;
        listRemove(listRoot, scope);
    }

    if (temp->subdeclarsnode != NULL){
        temp->subdeclarsnode->node.visit(temp->subdeclarsnode);
    }

    if (temp->compoundstatementnode != NULL){
        temp->compoundstatementnode->node.visit(temp->compoundstatementnode);
    }
    
    return;
}