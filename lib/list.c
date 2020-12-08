#include <string.h>

#include "list.h"

void list_push_back(list* root, list* next){
    list* curr = root;
    while(curr->next != NULL){
        curr = curr->next;
    }
    curr->next = next;
    next->prev = curr;
    return;
}

list* newdatalist(char* id, int scope, returnType type, dataType nodetype){
    list* temp = (list*) malloc ( sizeof(list) );
    temp->data = (symbolobj*) malloc ( sizeof(symbolobj) );
    temp->id = id;
    temp->scope = scope;
    temp->nodeType = nodetype;
    temp->data->type = type;
    temp->next = NULL;
    temp->prev = NULL;

    return temp;
}

list* newarraylist(char* id, int scope, returnType type, dataType nodetype){
    list* temp = (list*) malloc ( sizeof(list) );
    temp->data = (symbolobj*) malloc ( sizeof(arraysymbolobj) );
    temp->id = id;
    temp->scope = scope;
    temp->nodeType = nodetype;
    temp->data->type = type;
    temp->next = NULL;
    temp->prev = NULL;

    return temp;
}

list* newfunclist( char* id, int scope, returnType type, dataType nodetype ){
    list* temp = (list*) malloc ( sizeof(list) );
    temp->data = (symbolobj*) malloc ( sizeof(funcsymbolobj) );
    temp->data->type = type;
    ((funcsymbolobj*)temp->data)->passInType = NULL;
    ((funcsymbolobj*)temp->data)->check = 0;
    temp->id = id;
    temp->scope = scope;
    temp->nodeType = nodetype;
    temp->next = NULL;
    temp->prev = NULL;

    return temp;
}

void list_printTable(list* root){
    list* curr = root;
    if(root != NULL){
        while(curr->next != NULL){
            curr = curr->next;
        }
        while(curr != NULL){
            char dataTemp[40] = { };
            char dataCurr[40] = { };
            if ( curr->nodeType == Data ){
                // data
                symbolobj* temp = curr->data;
                while(temp->type == Array){
                    strcpy( dataCurr, dataTemp );
                    sprintf(dataTemp, "[%d~%d]%s", ((arraysymbolobj*)temp)->start, ((arraysymbolobj*)temp)->end, dataCurr);
                    temp = ((arraysymbolobj*)temp)->data;
                }

                strcpy( dataCurr, dataTemp );
                switch (temp->type)
                {
                case Void:
                    sprintf(dataTemp, "void%s", dataCurr);
                    break;

                case Int:
                    sprintf(dataTemp, "int%s", dataCurr);
                    break;

                case Real:
                    sprintf(dataTemp, "real%s", dataCurr);
                    break;

                case String:
                    sprintf(dataTemp, "string%s", dataCurr);
                    break;
                
                default:
                    break;
                }
                fprintf(stdout, SYMTAB_ENTRY_FMT, curr->id, curr->scope, dataTemp);
            }else{
                // function or procedure
                symbolobj* temp = curr->data;

                int counter = 0;
                // check pass in data type
                passinobj* tempPassInType = ((funcsymbolobj*)curr->data)->passInType;
                while (tempPassInType != NULL){
                    // check type
                    
                    char ArrayTemp[40] = { };
                    char ArrayCurr[40] = { };
                    symbolobj* tempArray = tempPassInType->data;
                    while(tempArray->type == Array){
                        strcpy( ArrayCurr, ArrayTemp );
                        sprintf(ArrayTemp, "[%d~%d]%s", ((arraysymbolobj*)tempArray)->start, ((arraysymbolobj*)tempArray)->end, ArrayCurr);
                        tempArray = ((arraysymbolobj*)tempArray)->data;
                    }

                    strcpy( ArrayCurr, ArrayTemp );
                    switch (tempArray->type)
                    {
                    case Void:
                        sprintf(ArrayTemp, "void%s", ArrayCurr);
                        break;

                    case Int:
                        sprintf(ArrayTemp, "int%s", ArrayCurr);
                        break;

                    case Real:
                        sprintf(ArrayTemp, "real%s", ArrayCurr);
                        break;

                    case String:
                        sprintf(ArrayTemp, "string%s", ArrayCurr);
                        break;
                    
                    default:
                        break;
                    }
                    strcpy( dataCurr, dataTemp );
                    if (counter > 0)
                        sprintf(dataTemp, "%s, %s", dataCurr, ArrayTemp);
                    else
                        sprintf(dataTemp, "%s", ArrayTemp);

                    tempPassInType = tempPassInType->next;
                    counter++;
                }

                // check return data type
                strcpy( dataCurr, dataTemp );
                switch (temp->type)
                {
                case Void:
                    if (!strcmp(dataCurr, ""))
                        sprintf(dataTemp, "void");
                    else
                        sprintf(dataTemp, "void (%s)", dataCurr);
                    break;

                case Int:
                    if (!strcmp(dataCurr, ""))
                        sprintf(dataTemp, "int");
                    else
                    sprintf(dataTemp, "int (%s)", dataCurr);
                    break;

                case Real:
                    if (!strcmp(dataCurr, ""))
                        sprintf(dataTemp, "real");
                    else
                    sprintf(dataTemp, "real (%s)", dataCurr);
                    break;

                case String:
                    if (!strcmp(dataCurr, ""))
                        sprintf(dataTemp, "string");
                    else
                    sprintf(dataTemp, "string (%s)", dataCurr);
                    break;
                
                default:
                    break;
                }
                
                // output
                fprintf(stdout, SYMTAB_ENTRY_FMT, curr->id, curr->scope, dataTemp);
            }
            curr = curr->prev;
        }
    }
}

int checkList( list* root, char* id, int scope, dataType type ){
    list* curr = root;
    while (curr != NULL){
        //  function overload
        // if ( (!strcmp(curr->id, id)) && (curr->scope == scope) && (curr->nodeType == type ) ){
        if ( (!strcmp(curr->id, id)) && (curr->scope == scope) ){
            return 1;
        }
        curr = curr->next;
    }

    return 0;
}

void listRemove( list* listRoot, int scope ){
    list* curr = listRoot;
    while(curr != NULL){
        if ( curr->scope > scope ){
            if (curr->next != NULL)
                curr->next->prev = curr->prev;
            if (curr->prev != NULL)
                curr->prev->next = curr->next;
        }
        curr = curr->next;
    }
    
    return;
}

int GetList( list* root, list** temp, char* id ){
    list* curr = root;
    while (curr != NULL){
        if ( !strcmp(curr->id, id) ){
            *temp = curr;
            return 1;
        }
        curr = curr->next;
    }
    return 0;
}
