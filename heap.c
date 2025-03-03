#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 50

static int heap[N] = {0};

void dump_heap(int index) {
    if (index < N) {
        int info = heap[index];

        if (2 * index + 1 < N) {
            printf("  \"V=%d I=%d\" -> \"V=%d I=%d\";\n", info, index, heap[2 * index + 1], 2 * index + 1);
        }

        if (2 * index + 2 < N) {
            printf("  \"V=%d I=%d\" -> \"V=%d I=%d\";\n", info, index, heap[2 * index + 2], 2 * index + 2);
        }

        dump_heap(2 * index + 1);
        dump_heap(2 * index + 2);
    }
}

void heapify(int i) {
    int smallest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < N && heap[l] < heap[smallest])
        smallest = l;
    if (r < N && heap[r] < heap[smallest])
        smallest = r;

    if (smallest != i) {
        int temp = heap[i];
        heap[i] = heap[smallest];
        heap[smallest] = temp;
        heapify(smallest);
    }
}

int main(void) {
    srand(time(NULL));

    for (int i = 0; i < N; i++) {
        heap[i] = rand() % 20;
    }

    for (int i = N / 2 - 1; i >= 0; i--) {
        heapify(i);
    }

    printf("digraph G {\n");
    dump_heap(0);
    printf("}\n");

    return 0;
}
