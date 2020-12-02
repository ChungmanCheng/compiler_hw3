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

list* newlist(char* id, int scope, char* type){
    list* temp = (list*) malloc ( sizeof(list) );
    temp->data.id = id;
    temp->data.scope = scope;
    temp->data.type = type;
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
        fprintf(stdout, SYMTAB_ENTRY_FMT, curr->data.id, curr->data.scope, curr->data.type);
        while(curr->prev != NULL){
            curr = curr->prev;
            fprintf(stdout, SYMTAB_ENTRY_FMT, curr->data.id, curr->data.scope, curr->data.type);
        }
    }
}

int checkList( list* root, char* id, int scope ){
    list* curr = root;
    while (curr != NULL){
        if ( (!strcmp(curr->data.id, id)) && (curr->data.scope == scope) ){
            return 1;
        }
        curr = curr->next;
    }

    return 0;
}

void listRemove( list* listRoot, int scope){
    list* curr = listRoot;
    while(curr != NULL){
        if ( curr->data.scope > scope ){
            if (curr->next != NULL)
                curr->next->prev = curr->prev;
            if (curr->prev != NULL)
                curr->prev->next = curr->next;
            free(curr);
        }
        curr = curr->next;
    }
    
    return;
}
