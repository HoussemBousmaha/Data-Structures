#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100000

static int arr[N] = {0};

typedef struct {
    int a;
    int b;
} Pair;

typedef struct {
    Pair l;
    Pair r;
} PartitionBounds;

PartitionBounds partition(int *array, int l, int r) {
    int j_turn = 1;
    int i = l, j = r;

    while (i < j) {
        while (array[i] < array[j]) {
            if (j_turn) {
                j--;
            } else {
                i++;
            }
        }

        int tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;

        j_turn = !j_turn;
    }

    PartitionBounds boundaries;

    if (j_turn) {
        boundaries.l.a = l;
        boundaries.l.b = j - 1;
        boundaries.r.a = j + 1;
        boundaries.r.b = r;
    } else {
        boundaries.l.a = l;
        boundaries.l.b = i - 1;
        boundaries.r.a = i + 1;
        boundaries.r.b = r;
    }

    return boundaries;
}

void quicksort() {
    Pair stack[N];
    int top = -1;

    stack[++top] = (Pair){0, N - 1};

    while (top >= 0) {
        int l = stack[top].a;
        int r = stack[top].b;
        top--;

        while (r > l) {
            PartitionBounds boundaries = partition(arr, l, r);

            if (boundaries.l.b - boundaries.l.a > boundaries.r.b - boundaries.r.a) {
                stack[++top] = boundaries.l;
                l = boundaries.r.a;
                r = boundaries.r.b;
            } else {
                stack[++top] = boundaries.r;
                l = boundaries.l.a;
                r = boundaries.l.b;
            }
        }
    }
}

int main(void) {
    for (size_t i = 0; i < N; i++) {
        arr[i] = rand();
    }

    clock_t begin_time = clock();
    quicksort();
    double elapsed = (double)(clock() - begin_time) / CLOCKS_PER_SEC;
    printf("Sorting took: %f seconds\n", elapsed);

    return 0;
}
