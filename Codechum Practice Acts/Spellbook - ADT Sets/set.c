#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "set.h"

// write your functions here...

Node* make_node(char* spell_text){
    Node* n = malloc(sizeof(Node));
    if(!n) return NULL;
    
    strncpy(n->spell, spell_text, sizeof(n->spell) - 1);
    n->spell[sizeof(n->spell) - 1] = '\0';
    n->next = NULL;
    return n;
}

Set* createSet(){
    Set* s = malloc(sizeof(Set));
    if(!s) return NULL;
    s->head = NULL;
    s->size = 0;
    return s;
}

bool containsSpell(Set* set, String spell){
    if(!set) return false;
    for(Node* cur = set->head; cur != NULL; cur = cur->next){
        if(strcmp(cur->spell, spell) == 0){
            return true;
        }
    }
    return false;
}

bool addSpell(Set* set, String spell){
    if(!set) return false;
    
    if(spell[0] == '\0') return false;
    
    if(containsSpell(set, spell)) {
        return false;
    }
    
    Node* n = make_node(spell);
    if(!n) return false;
    
    n->next = set->head;
    set->head = n;
    set->size += 1;
    return true;
}

bool removeSpell(Set** set, String spell) {
    if(!set || !(*set) || !(*set)->head) return false;
    
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
            free(cur);
            s->size -= 1;
            return true;
        }
        prev = cur;
        cur = cur->next;
    }
    return false;
}

void printSet(Set* set){
    if(!set || !set->head){
        printf("empty\n");
        return;
    }
    
    Node* cur = set->head;
    int indx = 1;
    while(cur){
        printf("  %d. %s\n", indx, cur->spell);
        cur = cur->next;
        indx++;
    }
}

void destroySet(Set* set){
    if(!set) return;
    Node* cur = set->head;
    while(cur){
        Node* nxt = cur->next;
        free(cur);
        cur = nxt;
    }
    free(set);
}

Set* unionSets(Set* set1, Set* set2){
    Set* out = createSet();
    if(!out) return NULL;
    
    for(Node* cur = set1 ? set1->head : NULL; cur; cur = cur->next){
        addSpell(out, cur->spell);
    }
    
    for(Node* cur = set2 ? set2->head : NULL; cur; cur = cur->next){
        addSpell(out, cur->spell);
    }
    return out;
}

Set* intersectSets(Set* set1, Set* set2){
    Set* out = createSet();
    if(!out) return NULL;
    
    if(!set1 || !set2) return out;
    
    for(Node* cur = set1->head; cur; cur = cur->next){
        if(containsSpell(set2, cur->spell)){
            addSpell(out, cur->spell);
        }
    }
    return out;
}