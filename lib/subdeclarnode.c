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
        if ( checkList(listRoot, temp->head->id, scope, Function) ){
            fprintf(stderr, REDEF_VAR, temp->head->node.loc.first_line, temp->head->node.loc.first_column, temp->head->id );
        }else{
            SHOW_NEWSYM(temp->head->id);
            list* tempList;
            if (temp->head->type){
                // PROCEDURE
                
                tempList = newfunclist( temp->head->id, scope, Void, Function );
                list_push_back( listRoot, tempList );

            }else{
                // FUNCTION
                switch (temp->head->standard_type->type)
                {
                case 0:
                    /* code */
                    tempList = newfunclist( temp->head->id, scope, Int, Function );
                    break;

                case 1:
                    tempList = newfunclist( temp->head->id, scope, Real, Function );
                    break;

                case 2:
                    tempList = newfunclist( temp->head->id, scope, String, Function );
                    break;
                
                default:
                    break;
                }
                list_push_back( listRoot, tempList );
            }
            // create a scope
            SHOW_NEWSCP();
            scope++;

            // pass in data type
            ParameterListNode* curr = NULL;
            if (temp->head->arguments != NULL)
                curr = temp->head->arguments->parameterlist;
            while(curr != NULL){
                // parameterList

                // add pass in data type
                returnType typeTemp;
                if (curr->typenode->standtypenode != NULL){
                    // standtype
                    switch(curr->typenode->standtypenode->type){
                    case 0:
                        typeTemp = Int;
                        break;

                    case 1:
                        typeTemp = Real;
                        break;

                    case 2:
                        typeTemp = String;
                        break;

                    default:
                        break;
                    }

                    IdentListNode* idList = curr->identlistnode;
                    ((funcsymbolobj*)tempList->data)->passInType = (passinobj*) malloc ( sizeof(passinobj) );
                    ((passinobj*)((funcsymbolobj*)tempList->data)->passInType)->data = (symbolobj*) malloc ( sizeof(symbolobj) );
                    ((passinobj*)((funcsymbolobj*)tempList->data)->passInType)->data->type = typeTemp;
                    passinobj* passinobjTemp = ((funcsymbolobj*)tempList->data)->passInType;
                    if ( checkList(listRoot, idList->id, scope, Data) ){
                        fprintf(stderr, REDEF_VAR, idList->node.loc.first_line, idList->node.loc.first_column, idList->id );
                    }else{
                        SHOW_NEWSYM(idList->id);
                        list_push_back( listRoot, newdatalist(idList->id, scope, typeTemp, Data) );
                    }
                    passinobjTemp->next = NULL;
                    while( idList->PrevNode != NULL ){
                        passinobjTemp->next = (passinobj*) malloc ( sizeof(passinobj) );
                        ((passinobj*)passinobjTemp->next)->data = (symbolobj*) malloc ( sizeof(symbolobj) );
                        idList = idList->PrevNode;
                        passinobjTemp = (passinobj*)(passinobjTemp->next);
                        passinobjTemp->data->type = typeTemp;
                        if ( checkList(listRoot, idList->id, scope, Data) ){
                            fprintf(stderr, REDEF_VAR, idList->node.loc.first_line, idList->node.loc.first_column, idList->id );
                        }else{
                            SHOW_NEWSYM(idList->id);
                            list_push_back( listRoot, newdatalist(idList->id, scope, typeTemp, Data) );
                        }
                    }

                }else{
                    // array
                    /*
                    IdentListNode* idList = curr->identlistnode;

                    ((funcsymbolobj*)tempList->data)->passInType = (passinobj*) malloc ( sizeof(passinobj) );
                    ((passinobj*)((funcsymbolobj*)tempList->data)->passInType)->data = (symbolobj*) malloc ( sizeof(arraysymbolobj) );
                    ((arraysymbolobj*)((passinobj*)((funcsymbolobj*)tempList->data)->passInType)->data)->type = Array;
                    ((arraysymbolobj*)((passinobj*)((funcsymbolobj*)tempList->data)->passInType)->data)->start = curr->typenode->array_start;
                    ((arraysymbolobj*)((passinobj*)((funcsymbolobj*)tempList->data)->passInType)->data)->end = curr->typenode->array_end;
                    passinobj* passinobjTemp = ((funcsymbolobj*)tempList->data)->passInType;
                    passinobjTemp->next = NULL;

                    while(idList->PrevNode != NULL){
                        
                        
                        if ( checkList(listRoot, idList->id, scope, Data) ){
                            fprintf(stderr, REDEF_VAR, idList->node.loc.first_line, idList->node.loc.first_column, idList->id );
                        }else{
                            SHOW_NEWSYM(idList->id);
                            list_push_back( listRoot, newarraylist(idList->id, scope, Array, Data) );
                        }

                        idList = idList->PrevNode;
                    }
                    */

                }

                curr = curr->NextNode;
            }
        }
    }
    
    if (temp->declarnode != NULL){
        temp->declarnode->node.visit(temp->declarnode);
    }

    if (temp->subdeclarsnode != NULL){
        temp->subdeclarsnode->node.visit(temp->subdeclarsnode);
    }

    if (temp->compoundstatementnode != NULL){
        temp->compoundstatementnode->node.visit(temp->compoundstatementnode);
    }

    SHOW_CLSSCP();
    SHOW_SYMTAB_HEAD();
    // print table
    list_printTable(listRoot);
    SHOW_SYMTAB_TAIL();
    scope--;
    listRemove(listRoot, scope);
    
    return;
}