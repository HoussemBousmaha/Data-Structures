#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 5

int main(void) {
    srand(time(0));

    int data[SIZE] = {0};
    int *front = NULL;
    int *rear = NULL;

    for (int i = 0; i < SIZE; i++) {
        // enqueue
        if (rear == NULL) {
            front = rear = data;
        } else {
            rear++;
        }

        *rear = rand() % 100;
        printf("Enqueued: %d\n", *rear);
    }

    printf("--------------------------------------------------------------------\n");

    while (front != NULL) {
        printf("Dequeued: %d\n", *front);

        if (front == rear) {
            front = rear = NULL;
        } else {
            front++;
        }
    }

    return 0;
}
