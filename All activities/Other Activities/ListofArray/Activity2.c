#include <stdio.h>
#include <stdlib.h>


typedef struct node {
    int data;
    struct node* next;
}Node;

typedef struct {
    Node *head;
    int count;
} List;

List* initialize();
void empty(List *list);
void insertFirst(List *list, int data);
void insertLast(List *list, int data);
void insertPos(List *list, int data, int index);
void deleteStart(List *list);
void deletePos(List *list, int index);
int retrieve(List *list, int index);
int locate(List *list, int data);
void display(List *list);

int main(){
    List* myList = initialize();

    insertFirst(myList, 10);
    insertLast(myList, 20);
    insertFirst(myList, 5);
    insertPos(myList, 15, 2);
    insertPos(myList, 25, 4);

    display(myList);

    deleteStart(myList);
    deletePos(myList, 2);

    display(myList);

    int val = retrieve(myList, 1);
    printf("Value at index 1: %d\n", val);

    int index = locate(myList, 25);
    printf("Index of 25: %d\n", index);

    empty(myList);
    display(myList);

    free(myList);
    return 0;
}

List* initialize(){
    List* L = malloc(sizeof(List));
    if(L == NULL){
        printf("Memory allocation failed.");
        return NULL;
    }
    L->count = 0;
    L->head = NULL;

    return L;
}

void empty(List *list){
    Node *curr = list->head;
    Node *temp;

    while(curr != NULL){
        temp = curr;
        curr = curr->next;
        free(temp);
    }
    list->head = NULL;
    list->count = 0;
}

void insertFirst(List *list, int data){

    Node* nn = malloc(sizeof(Node));
    if(nn == NULL){
        printf("New node failed.");
        return;
    }

    nn->data = data;
    nn->next = list->head;
    list->head = nn;
    list->count++;
}

void insertLast(List *list, int data) {
    Node* nn = malloc(sizeof(Node));
    if(nn == NULL){
        printf("New node failed.\n");
        return;
    }

    nn->data = data;
    nn->next = NULL;

    if(list->head == NULL){
        list->head = nn;
    } else {
        Node* curr = list->head;
        while(curr->next != NULL){
            curr = curr->next;
        }
        curr->next = nn;
    }

    list->count++;
}

void insertPos(List *list, int data, int index){
    if(index < 0 || index > list->count){
        printf("Invalid index.");
        return; 
    }

    if(index == 0){
        insertFirst(list, data);
    } else if(index == list->count){
        insertLast(list, data);
    } else {
        Node* nn = malloc(sizeof(Node));
        if(nn == NULL){
        printf("New node failed.");
        return;
        }

        nn->data = data;

        Node* curr = list->head;
        for(int i = 0; i < index - 1; ++i){
            curr = curr->next;
        }

        nn->next = curr->next;
        curr->next = nn;
        list->count++;

    }
}

void deleteStart(List *list){
    if(list->head == NULL) return;
    Node* temp = list->head;
    list->head = list->head->next;
    free(temp);
    list->count--;
}

void deletePos(List *list, int index){
    if(index < 0 || index >= list->count) return;
    if(index == 0){
        deleteStart(list);
    } else {
        Node* curr = list->head;
        for(int i = 0; i < index - 1; ++i){
            curr = curr->next;
        }
        Node* temp = curr->next;
        curr->next = temp->next;
        free(temp);
        list->count--;
    }
}

int retrieve(List *list, int index){
    if(index < 0 || index >= list->count) return -1;
    Node* curr = list->head;
    for(int i = 0; i < index; ++i){
        curr = curr->next;
    }
    return curr->data;
}

int locate(List *list, int data){
    Node* curr = list->head;
    int index = 0;
    while(curr != NULL){
        if(curr->data == data) return index;
        curr = curr->next;
        index++;
    }
    return -1;
}

void display(List *list){
    Node* curr = list->head;
    while(curr != NULL){
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("\n");
}