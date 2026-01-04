#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10

typedef struct {
    int items[MAX];
    int count;
} List;

typedef struct {
    List list;
    int front;
    int rear;
} Queue;

Queue* initialize() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->list.count = 0;
    q->front = -1;
    q->rear = -1;
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

    if (isEmpty(q)) {
        q->front = 0;
        q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % MAX;
    }

    q->list.items[q->rear] = value;
    q->list.count++;
}

int dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return -1;
    }

    int value = q->list.items[q->front];

    if (q->list.count == 1) {
        q->front = -1;
        q->rear = -1;
    } else {
        q->front = (q->front + 1) % MAX;
    }

    q->list.count--;
    return value;
}

int front(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return -1;
    }

    int value = q->list.items[q->front];
    return value;
}

void display(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return;
    }

    int i = q->front;
    for (int c = 0; c < q->list.count; c++) {
        printf("%d ", q->list.items[i]);
        i = (i + 1) % MAX;
    }

    printf("\n");
}

int main() {
    Queue* q = initialize();

    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);

    display(q);

    int f = front(q);
    printf("Front value: %d\n", f);

    int removed = dequeue(q);
    printf("Removed: %d\n", removed);

    display(q);

    return 0;
}