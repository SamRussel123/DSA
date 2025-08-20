#include <stdio.h>



#define MAX 10

typedef struct {
    
    int elem[MAX];
    int count;
    
} List;

List initialize(List L);

List insertPos(List L, int data, int position);
List deletePos(List L, int position);
int locate(List L, int data);
List insertSorted(List L, int data);
void display(List L);

List initialize(List L) {
    L.count = 0;
    return L;
}

List insertPos(List L, int data, int position) {
    if (L.count == MAX || position < 0 || position > L.count)
        return L;
    for (int i = L.count; i > position; i--) {
        L.elem[i] = L.elem[i - 1];
    }
    L.elem[position] = data;
    L.count++;
    return L;
}

List deletePos(List L, int position) {
    if (position < 0 || position >= L.count)
        return L;
    for (int i = position; i < L.count - 1; i++) {
        L.elem[i] = L.elem[i + 1];
    }
    L.count--;
    return L;
}

int locate(List L, int data) {
    
    for (int i = 0; i < L.count; i++) {
        
        if (L.elem[i] == data)
            return i;
    }
    return 0;
}

List insertSorted(List L, int data) {
    
    if (L.count == MAX)
        return L;
    int i = 0;
    
    while (i < L.count && L.elem[i] < data) {
        i++;
    }
    return insertPos(L, data, i);
}

void display(List L) {
    
    for (int i = 0; i < L.count; i++) {
        
        printf("%d ", L.elem[i]);
    }
    printf("\n");
}

int main() {
    List L = initialize(L);

    L = insertPos(L, 10, 0);
    L = insertPos(L, 15, 1);
    L = insertPos(L, 20, 2);

    display(L);
    printf("Del Pos of 0 and 1, and you are left with: ");
    L = deletePos(L, 1);
    L = deletePos(L, 0);
    display(L);

    int pos = locate(L, 20);
    printf("Pos of 20: %d\n", pos);
    printf("Inserted Vals: ");
    L = insertSorted(L, 69);
    L = insertSorted(L, 720);
    L = insertSorted(L, 369);
    display(L);

    return 0;
}
