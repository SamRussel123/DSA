#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct {
    char *elem;
    int count;
    int size;
} List, *Lptr;

void initialize(Lptr L);
void insertPos(Lptr L, char data, int pos);
void deletePos(Lptr L, int pos);
int locate(Lptr L, char data);
char retrieve(Lptr L, int pos);
void insertSorted(Lptr L, char data);
void makeNULL(Lptr L);
void display(Lptr L);

int main(){
    List list;
    Lptr L = &list;

    initialize(L);

    L->elem[0] = 'J';
    L->elem[1] = 'U';
    L->elem[2] = 'S';
    L->elem[3] = 'T';
    L->elem[4] = 'I';
    L->elem[5] = 'N';
    L->count = 6;

    printf("Original: ");
    display(L);

    insertPos(L, 'C', 2);
    printf("After inserting C at pos 2: ");
    display(L);

    deletePos(L, 3);
    printf("After deleting pos 3: ");
    display(L);

    printf("Locate 'I': %d\n", locate(L, 'I'));
    printf("Retrieve at 2: %c\n", retrieve(L, 2));

    insertSorted(L, 'B');
    printf("After insertSorted B: ");
    display(L);

    makeNULL(L);
    printf("After makeNULL: ");
    display(L);

    free(L->elem);
    return 0;
}

void initialize(Lptr L){
    L->elem = malloc(sizeof(char) * MAX);
    L->count = 0;
    L->size = MAX;
}

void insertPos(Lptr L, char data, int pos){
    if(pos < 0 || pos > L->count || L->count == L->size) return;
    for(int i = L->count; i > pos; --i){
        L->elem[i] = L->elem[i - 1];
    }
    L->elem[pos] = data;
    L->count++;
}

void deletePos(Lptr L, int pos){
    if(pos < 0 || pos >= L->count) return;
    for(int i = pos; i < L->count - 1; ++i){
        L->elem[i] = L->elem[i + 1];
    }
    L->count--;
}

int locate(Lptr L, char data){
    for(int i = 0; i < L->count; ++i){
        if(L->elem[i] == data) return i;
    }
    return -1;
}

char retrieve(Lptr L, int pos){
    if(pos < 0 || pos >= L->count) return '\0';
    return L->elem[pos];
}

void insertSorted(Lptr L, char data){
    int i;
    for(i = 0; i < L->count; ++i){
        if(data < L->elem[i]) break;
    }
    insertPos(L, data, i);
}

void makeNULL(Lptr L){
    L->count = 0;
}

void display(Lptr L){
    for(int i = 0; i < L->count; ++i){
        printf("%c ", L->elem[i]);
    }
    printf("\n");
}