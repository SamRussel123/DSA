#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "set.h"

// write your functions here...

Node* make_node(char* spell_text){
    // TODO: allocate memory, copy string, set next to NULL
    Node* n = malloc(sizeof(Node));
    if(!n) return NULL;

    strncpy(n->spell, spell_text, sizeof(n->spell) - 1);
    n->spell[sizeof(n->spell) - 1] = '\0'; 
    n->next = NULL;

    return n;
}

Set* createSet(){
    // TODO: allocate memory for Set, initialize head and size
    Set *S = malloc(sizeof(Set));
    if(!S) return NULL;

    S->head = NULL;
    S->size = 0;
    return S;

}
bool containsSpell(Set* set, String spell){
    // TODO: traverse list and check if spell already exists
    if(!set) return false;
    for(Node* curr = set->head; curr != NULL; curr = curr->next){
        if(strcmp(curr->spell, spell) == 0){
            return true;
        }
    }
    return false;
}

bool addSpell(Set* set, String spell){
    // TODO: validate, check duplicates, create node, insert at head
    if(!set) return false;

    if(spell[0] == '\0'){
        return false;
    }

    if(containsSpell(set, spell)){
        return false;
    }

    Node* n = make_node(spell);
    if(!n) return NULL;

    n->next = set->head;
    set->head = n;
    set->size++;

    return true;
}

bool removeSpell(Set** set, String spell) {
    // TODO: traverse list, find and remove node, adjust head or prev->next
    if(!set || !(*set) || !(*set)->head) {
        return false;
    }

    Set* s = *set;
    Node* cur = s->head;
    Node* prev = NULL;

    while(cur){
        if(strcmp(cur->spell, spell) == 0){
            if(prev){
                prev->next = cur->next;
            } else {
                s->head = cur->next;
            }
        }
        free(cur);
        s->size--;
        return true;
    }
    return false;
}

void printSet(Set* set){
    // TODO: print all spells, handle empty case
    if(!set | !set->head){
        printf("Empty");
        return;
    }

    Node* cur = set->head;
    int index = 1;
    while(cur != NULL){
        printf("Element %i: %d", index, cur->spell);
        cur = cur->next;
        index++;
    }
}

void destroySet(Set* set){
    // TODO: free all nodes and then the set itself
    if(!set) return NULL;

    Node* cur = set->head;
    while(cur){
        Node* next = cur->next;
        free(cur);
        cur = next;
    }
    free(set);
}

Set* unionSets(Set* set1, Set* set2){
    // TODO: create new set, copy elements from both sets without duplicates
    Set* out = createSet();
    if(!out) return NULL;

    if(set1 != NULL){
        Node* curr = set1->head;
        while(curr != NULL){
            addSpell(out, curr->spell);
            curr = curr->next;
        }
    }

    if(set2 != NULL){
        Node* curr = set2->head;
        while(curr != NULL){
            addSpell(out, curr->spell);
            curr = curr->next;
        }
    }
    return out;
}

Set* intersectSets(Set* set1, Set* set2){
    // TODO: create new set, add only elements that exist in both sets
    Set* out = createSet();
    if(!out) return NULL;

    if(!set1 || !set2) return out;

    for(Node* cur = set1->head; cur; cur = cur->next){
        if(containsSpell(set2, cur->spell)){
            addSpell(out,cur->spell);
        }
    }

    return out;
}