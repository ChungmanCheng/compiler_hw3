#include "declarnode.h"
#include "list.h"
#include "info.h"

extern list* listRoot;
extern int scope;

Node* newDeclarNode( int firstLine, int firstColumn, DeclarNode* declarnode, IdentListNode* identlist, TypeNode* type, int lastLine, int lastColumn ){
    DeclarNode* temp = (DeclarNode*) malloc ( sizeof(DeclarNode) );
    temp->NextNode = declarnode;
    temp->identlistnode = identlist;
    temp->typenode = type;
    temp->node.type = _DeclarNode;
    temp->node.visit = DeclarNode_visit;
    temp->node.loc.first_line = firstLine;
    temp->node.loc.first_column = firstColumn;
    temp->node.loc.last_line = lastLine;
    temp->node.loc.last_column = lastColumn;

    return temp;
}

void DeclarNode_visit(void* node){
    DeclarNode* temp = (DeclarNode*)node;

    // go to leftmost declarations
    if (temp->NextNode != NULL)
        temp->NextNode->node.visit(temp->NextNode);

    char* dataType = (char*) malloc ( sizeof(char) * 40 );
    // check type
    if (temp->typenode->standtypenode != NULL){
        if (temp->typenode->standtypenode->type == 0){
            sprintf(dataType, "int");
        }else if (temp->typenode->standtypenode->type == 1){
            sprintf(dataType, "real");
        }else{
            sprintf(dataType, "string");
        }
    }else{
        TypeNode* curr = temp->typenode;
        while(curr->type != NULL){
            char str[40];
            strcpy(str, dataType);
            sprintf(dataType, "%s[%d~%d]", str, curr->array_start, curr->array_end);
            curr = curr->type;
        }
        char str[40];
        strcpy(str, dataType);
        if (curr->standtypenode->type == 0){
            sprintf(dataType, "int%s", str);
        }else if (curr->standtypenode->type == 1){
            sprintf(dataType, "real%s", str);
        }else{
            sprintf(dataType, "string%s", str);
        }

    }
    // add sym into symbol table
    IdentListNode* curr = temp->identlistnode;
    while(curr != NULL){
        if ( checkList(listRoot, curr->id, scope) ){
            fprintf(stderr, REDEF_VAR, curr->node.loc.first_line, curr->node.loc.first_column, curr->id );
        }else{
            SHOW_NEWSYM(curr->id);
            list_push_back( listRoot, newlist(curr->id, scope, dataType) );
        }
        curr = curr->PrevNode;
    }

    return;
}
