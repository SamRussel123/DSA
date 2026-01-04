#include <stdio.h>

#define MAX 10

typedef struct {
    int elem[MAX];
    int count;
} List;

List initialize(List L);
List insertPos(List L, int data, int pos);
List deletePos(List L, int pos);
int locate(List L, int data);
List insertSorted(List L, int data);
void display(List L);

int main(){
    List L = initialize(L);

    L.elem[0] = 10;
    L.elem[1] = 20;
    L.elem[2] = 30;
    L.elem[3] = 40;
    L.elem[4] = 50;
    L.count = 5;

    printf("Original List: "); display(L);

    L = insertPos(L, 25, 2);
    printf("Inserting 25: "); display(L);

    L = deletePos(L, 3);
    printf("Deleting position 3: ");
    display(L);

    int indx =  locate(L, 40);
    printf("What the index of 40 is: %d\n", indx);

    L = insertSorted(L, 35);
    printf("Insert sorted 35: "); 
    display(L);
    

    return 0;
}


List initialize(List L){
    L.count = 0;
    return L;
}

List insertPos(List L, int data, int pos){
    if(pos < 0 || pos > L.count || L.count == MAX){
        return L;
    }

    for(int i = L.count; i > pos; --i){
        L.elem[i] = L.elem[i - 1];
    }
    L.elem[pos] = data;
    L.count++;
    return L;
}

List deletePos(List L, int pos){
    if(pos < 0 || pos >= L.count){
        return L;
    }

    for(int i = pos; i < L.count - 1; ++i){
        L.elem[i] = L.elem[i +  1];
    }
    L.count--;
    return L;
}

int locate(List L, int data){
    for(int i = 0; i < L.count; ++i){
        if(L.elem[i] == data){
            return i;
        }
    }

    return -1;
}

List insertSorted(List L, int data){
    int i;

    for(i = 0; i < L.count; ++i){
        if(data < L.elem[i]){
            break;
        }
    }
    return insertPos(L, data, i);
}

void display(List L){
    for(int i = 0; i < L.count; ++i){
        printf("%d ", L.elem[i]);
    }
    printf("\n");
}