#include <stdio.h>
#include <stdbool.h>
#include "types.h"

// write your functions here
void initializeStack(Stack *s) {
    s->top = -1;
}

bool isFull(Stack *s) {
    return s->top == MAX - 1;
}

bool isEmpty(Stack *s) {
    return s->top == -1;
}

void push(Stack *s, int value) {
    if (isFull(s)) {
        printf("Stack is full\n");
        return;
    }
    s->top++;
    s->items[s->top] = value;
}

int pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty\n");
        return -1;
    }

    int value = s->items[s->top];
    s->top--;
    return value;
}

int peek(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty\n");
        return -1;
    }

    int value = s->items[s->top];
    return value;
}

void display(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty\n");
        return;
    }
    for (int i = s->top; i >= 0; i--) {
        printf("%d ", s->items[i]);
    }
    printf("\n");
}