#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "arrayStack.h"

#define numOfStack 3

bool pushToAvailableStack(Stack stacks[], int value) {
    for (int i = 0; i < numOfStack; i++) {
        if (!isFull(&stacks[i])) {
            push(&stacks[i], value);
            return true;
        }
    }
    return false;
}

int popFromLatestStack(Stack stacks[]) {
    for (int i = numOfStack - 1; i >= 0; i--) {
        if (!isEmpty(&stacks[i])) {
            return pop(&stacks[i]);
        }
    }
    return -1;
}

bool containerExists(Stack stacks[], int target) {
    for (int i = 0; i < numOfStack; i++) {
        Stack tmp = stacks[i];
        while (!isEmpty(&tmp)) {
            if (peek(&tmp) == target) return true;
            pop(&tmp);
        }
    }
    return false;
}

void displayStacks(Stack stacks[]) {
    for (int i = 0; i < numOfStack; i++) {
        printf("\n--- Stack %d ---\n", i + 1);
        if (isEmpty(&stacks[i])) {
            printf("Stack is empty.\n");
        } else {
            for (int j = stacks[i].top; j >= 0; j--) {
                printf("%d\n", stacks[i].items[j]);
            }
        }
    }
    
}

int main() {
    
    Stack stacks[numOfStack];
    for(int i = 0; i < numOfStack; ++i){
        initializeStack(&stacks[i]);
    }
    int choice = 0;
    int value;
    
    
        while(1){
        printf("--- Warehouse Inventory Management System ---\n");
        printf("1. Push a container\n");
        printf("2. Pop a container\n");
        printf("3. Check if a container exists\n");
        printf("4. Display all stacks\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice){
            case 1: 
            printf("Enter container ID to push: ");
            scanf("%d", &value);
            if(pushToAvailableStack(stacks, value)){
                printf("Container %d pushed successfully.\n", value);
            } else {
                printf("All stacks are full");
            }
            break;
            
        case 2: 
            value = popFromLatestStack(stacks);
            if(value == -1){
                printf("Error: All stacks are empty. Cannot pop container.\n");
            } else {
                printf("Container %d popped successfully.\n", value);
            }
            break;
            
        case 3: 
            printf("Enter container ID to check: ");
            scanf("%d", &value);
            if(containerExists(stacks, value)){
                printf("Container %d exists in a stack.\n", value);
            } else {
                printf("Container %d does not exist in any stack.\n", value);
            }
            break;
        
        case 4: 
            displayStacks(stacks);
            break;
            
        case 5: 
            printf("Exiting program.");
            return 0;
            
            
        default: 
            printf("Invalid choice.\n");
    }
    printf("\n");
    }
        
        
    
    return 0;
}