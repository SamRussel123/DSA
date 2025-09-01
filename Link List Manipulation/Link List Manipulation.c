
/* List* initialize();
void empty(List *list);
void insertFirst(List *list, int data);
void insertLast(List *list, int data);
void insertPos(List *list, int data, int index);
void deleteStart(List *list);
void deleteLast(List *list);
void deletePos(List *list, int index);
int retrieve(List *list, int index);
int locate(List *list, int data);
void display(List *list);
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    int count;
} List;

List* initialize() {
    List *list = (List*) malloc(sizeof(List));
    if (list == NULL) {
        return NULL;
    }
    list->head = NULL;
    list->count = 0;
    return list;
}

void empty(List *list) {
    Node *current = list->head;
    Node *temp;
    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }
    list->head = NULL;
    list->count = 0;
}

void insertFirst(List *list, int data) {
    Node *newNode = (Node*) malloc(sizeof(Node));
    if (newNode == NULL) return;
    newNode->data = data;
    newNode->next = list->head;
    list->head = newNode;
    list->count++;
}

void insertLast(List *list, int data) {
    Node *newNode = (Node*) malloc(sizeof(Node));
    if (newNode == NULL) return;
    newNode->data = data;
    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    list->count++;
}

void insertPos(List *list, int data, int index) {
    if (index < 0 || index > list->count) {
        printf("Invalid index!\n");
        return;
    }

    if (index == 0) {
        insertFirst(list, data);
        return;
    }

    if (index == list->count) {
        insertLast(list, data);
        return;
    }

    Node *newNode = (Node*) malloc(sizeof(Node));
    if (newNode == NULL) return;
    newNode->data = data;

    Node *current = list->head;
    for (int i = 0; i < index - 1; i++) {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
    list->count++;
}

void deleteStart(List *list) {
    if (list->head == NULL) return;
    Node *current = list->head;
    list->head = current->next;
    free(current);
    list->count--;
}

void deleteLast(List *list) {
    if (list->head == NULL) return;

    if (list->head->next == NULL) {
        free(list->head);
        list->head = NULL;
    } else {
        Node *current = list->head;
        while (current->next->next != NULL) {
            current = current->next;
        }
        free(current->next);
        current->next = NULL;
    }
    list->count--;
}

void deletePos(List *list, int index) {
    if (index < 0 || index >= list->count) {
        printf("Invalid index!\n");
        return;
    }

    if (index == 0) {
        deleteStart(list);
        return;
    }

    Node *current = list->head;
    for (int i = 0; i < index - 1; i++) {
        current = current->next;
    }

    Node *temp = current->next;
    current->next = temp->next;
    free(temp);
    list->count--;
}

int retrieve(List *list, int index) {
    if (index < 0 || index >= list->count) {
        printf("Invalid index!");
        return -1;
    }
    Node *current = list->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}

int locate(List *list, int data) {
    Node *current = list->head;
    int index = 0;
    while (current != NULL) {
        if (current->data == data) {
            return index;
        }
        current = current->next;
        index++;
    }
    return -1;
}

void display(List *list) {
    Node *current = list->head;
    printf("List: ");
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\nCount: %d\n", list->count);
}

int main() {
    List *list = initialize();

    insertFirst(list, 5);
    insertFirst(list, 6);
    insertFirst(list, 2);
    display(list);

    insertLast(list, 7);
    display(list);

    insertPos(list, 8, 2);
    display(list);

    deleteStart(list);
    display(list);

    deleteLast(list);
    display(list);

    deletePos(list, 1);
    display(list);

    printf("Retrieve index 1: %d\n", retrieve(list, 1));
    printf("Locate value 5: %d\n", locate(list, 5));

    empty(list);
    display(list);

    free(list);
    return 0;
}












