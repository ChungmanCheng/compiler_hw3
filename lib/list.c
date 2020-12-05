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
    temp->data->next = NULL;
    temp->next = NULL;
    temp->prev = NULL;
    temp->push_back = list_push_back;

    return temp;
}

list* newarraylist(char* id, int scope, returnType type, dataType nodetype){
    list* temp = (list*) malloc ( sizeof(list) );
    temp->data = (symbolobj*) malloc ( sizeof(arraysymbolobj) );
    temp->id = id;
    temp->scope = scope;
    temp->nodeType = nodetype;
    temp->data->type = type;
    temp->data->next = NULL;
    temp->next = NULL;
    temp->prev = NULL;
    temp->push_back = list_push_back;

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
            if ( (curr->nodeType == Data) || (curr->nodeType == Array_Data) ){
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
                
            }
            curr = curr->prev;
        }
    }
}

int checkList( list* root, char* id, int scope, dataType type ){
    list* curr = root;
    while (curr != NULL){
        if ( (!strcmp(curr->id, id)) && (curr->scope == scope) && (curr->nodeType == type ) ){
            return 1;
        }
        curr = curr->next;
    }

    return 0;
}

void listRemove( list* listRoot, int scope){
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
