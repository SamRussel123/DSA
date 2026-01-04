#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "types.h"
#include "arrayQueue.h"

int main() {
    Queue *regular = initialize();
    Queue *priority = initialize();
    if (!regular || !priority) return 1;

    int choice = 0;
    int ticket = 1;

    while (1) {
        printf("--- Pharmacy Queueing System ---\n");
        printf("1. Enter Regular Queue\n");
        printf("2. Enter Priority Queue\n");
        printf("3. Call Next Customer\n");
        printf("4. Display Queues\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("Invalid input.\n\n");
            continue;
        }

        if (choice == 1) {
            if (!isFull(regular)) {
                enqueue(regular, ticket);
                printf("You have entered the Regular queue. Your number is %d.\n\n", ticket);
                ticket++;
            } else {
                printf("Regular queue is full. Please try again later.\n\n");
            }
        } else if (choice == 2) {
            if (!isFull(priority)) {
                enqueue(priority, ticket);
                printf("You have entered the Priority queue. Your number is %d.\n\n", ticket);
                ticket++;
            } else {
                printf("Priority queue is full.\n\n");
            }
        } else if (choice == 3) {
            if (!isEmpty(priority)) {
                int num = dequeue(priority);
                printf("Calling next customer from Priority Queue. Customer number: %d\n\n", num);
            } else if (!isEmpty(regular)) {
                int num = dequeue(regular);
                printf("Calling next customer from Regular Queue. Customer number: %d\n\n", num);
            } else {
                printf("Both queues are empty. No customers to call.\n\n");
            }
        } else if (choice == 4) {
            printf("\n-- Current Queue Status --\n");
            printf("Regular Queue: ");
            display(regular);
            printf("Priority Queue: ");
            display(priority);
            printf("\n");
        } else if (choice == 5) {
            printf("Exiting program. Goodbye!\n");
            break;
        } else {
            printf("Invalid choice.\n\n");
        }
    }

    free(regular);
    free(priority);
    return 0;
}