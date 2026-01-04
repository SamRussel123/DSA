#include <stdio.h>

typedef struct node {
    int elem;
    struct node *LC;
    struct node *RC;
} Node, *BST;

void insert(BST* T, int val){
    BST *trav = T;   

    while(*trav != NULL && (*trav)->elem != val){
        trav = ((*trav)->elem > val) ? &(*trav)->LC : &(*trav)->RC;
    }

    if(*trav == NULL){
        *trav = (BST) calloc(1, sizeof(Node));
        (*trav)->elem = val;
    }

    // or

    // Node* temp = malloc(sizeof(Node));
    // temp->elem = val;
    // temp->LC = NULL;
    // temp->RC = NULL;
    // *trav = temp;

}

void inorder(BST b){
   if(b != NULL){
    inorder(b->LC);
   printf("%d ", b->elem);
   inorder(b->RC);
   }
}

void preorder(BST b){
    if(b != NULL){
        printf("%d ", b->elem);
        preorder(b->LC);
        preorder(b->RC);
    }
}

void postorder(BST b){
    if(b != NULL) {
        postorder(b->LC);
        postorder(b->RC);
        printf("%d ", b->elem);
    }
    
}

BST delete(BST T, int val){
    if(T == NULL) return NULL;

    if(val < T->elem){
        T->LC = delete(T->LC, val);
    } else if(val > T->elem){
        T->RC = delete(T->RC, val);
    } else {
        if(T->LC == NULL && T->RC == NULL){
            free(T);
            return NULL;
        }

        if(T->LC == NULL){
            BST temp = T->RC;
            free(T);
            return temp;
        }

        if(T->RC == NULL){
            BST temp = T->LC;
            free(T);
            return temp;
        }
    }
}