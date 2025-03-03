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

PartitionBounds partition(int l, int r) {
    int j_turn = 1;
    int i = l, j = r;

    while (i < j) {
        while (arr[i] < arr[j]) {
            if (j_turn) {
                j--;
            } else {
                i++;
            }
        }

        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;

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
            PartitionBounds bounds = partition(l, r);

            if (bounds.l.b - bounds.l.a > bounds.r.b - bounds.r.a) {
                stack[++top] = bounds.l;
                l = bounds.r.a;
                r = bounds.r.b;
            } else {
                stack[++top] = bounds.r;
                l = bounds.l.a;
                r = bounds.l.b;
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
