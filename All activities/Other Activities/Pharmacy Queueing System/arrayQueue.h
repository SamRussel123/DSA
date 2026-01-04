#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "types.h"

Queue* initialize() {
    Queue* q = (Queue*) malloc(sizeof(Queue));
    if (q == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    q->front = 0;
    q->rear = -1;
    q->list.count = 0;
    return q;
}

bool isFull(Queue* q) {
    return q->list.count == MAX;
}

bool isEmpty(Queue* q) {
    return q->list.count == 0;
}

void enqueue(Queue* q, int value) {
    if (isFull(q)) {
        printf("Queue is full\n");
        return;
    }
    q->rear = (q->rear + 1) % MAX;
    q->list.items[q->rear] = value;
    q->list.count++;
}

int dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return -1;
    }
    int value = q->list.items[q->front];
    q->front = (q->front + 1) % MAX;
    q->list.count--;
    return value;
}

void display(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }
    int i = q->front;
    for (int c = 0; c < q->list.count; c++) {
        printf("%d ", q->list.items[i]);
        i = (i + 1) % MAX;
    }
    printf("\n");
}