#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct {
    char *elem;
    int count;
    int size;
} List;

List initialize();
List insertPos(List L, char data, int pos);
List deletePos(List L, int pos);
int locate(List L, char data);
char retrieve(List L, int pos);
List insertSorted(List L, char data);
List makeNULL(List L);
void display(List L);

int main(){
    List L = initialize();

    L.elem[0] = 'J';
    L.elem[1] = 'U';
    L.elem[2] = 'S';
    L.elem[3] = 'T';
    L.elem[4] = 'I';
    L.elem[5] = 'N';
    L.count = 6;

    printf("Original: ");
    display(L);

    L = insertPos(L, 'C', 2);
    printf("After inserting C at pos 2: ");
    display(L);

    L = deletePos(L, 3);
    printf("After deleting pos 3: ");
    display(L);

    printf("Locate 'I': %d\n", locate(L, 'I'));
    printf("Retrieve at 2: %c\n", retrieve(L, 2));

    L = insertSorted(L, 'B');
    printf("After insertSorted B: ");
    display(L);

    L = makeNULL(L);
    printf("After makeNULL: ");
    display(L);

    free(L.elem);
    return 0;
}

List initialize(){
    List L;
    L.elem = malloc(sizeof(char) * MAX);
    L.count = 0;
    L.size = MAX;
    return L;
}

List insertPos(List L, char data, int pos){
    if(pos < 0 || pos > L.count || L.count == L.size) return L;
    for(int i = L.count; i > pos; --i){
        L.elem[i] = L.elem[i - 1];
    }
    L.elem[pos] = data;
    L.count++;
    return L;
}

List deletePos(List L, int pos){
    if(pos < 0 || pos >= L.count) return L;
    for(int i = pos; i < L.count - 1; ++i){
        L.elem[i] = L.elem[i + 1];
    }
    L.count--;
    return L;
}

int locate(List L, char data){
    for(int i = 0; i < L.count; ++i){
        if(L.elem[i] == data) return i;
    }
    return -1;
}

char retrieve(List L, int pos){
    if(pos < 0 || pos >= L.count) return '\0';
    return L.elem[pos];
}

List insertSorted(List L, char data){
    int i;
    for(i = 0; i < L.count; ++i){
        if(data < L.elem[i]) break;
    }
    return insertPos(L, data, i);
}

List makeNULL(List L){
    L.count = 0;
    return L;
}

void display(List L){
    for(int i = 0; i < L.count; ++i){
        printf("%c ", L.elem[i]);
    }
    printf("\n");
}