#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000000

typedef struct {
    int first;
    int second;
} Pair;

typedef struct {
    Pair left;
    Pair right;
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
        boundaries.left.first = l;
        boundaries.left.second = j - 1;
        boundaries.right.first = j + 1;
        boundaries.right.second = r;
    } else {
        boundaries.left.first = l;
        boundaries.left.second = i - 1;
        boundaries.right.first = i + 1;
        boundaries.right.second = r;
    }

    return boundaries;
}

void quicksort(int *arr, int n) {
    Pair stack[n];
    int top = -1;

    stack[++top] = (Pair){0, n - 1};

    while (top >= 0) {
        int l = stack[top].first;
        int r = stack[top].second;
        top--;

        while (r > l) {
            PartitionBounds boundaries = partition(arr, l, r);

            if (boundaries.left.second - boundaries.left.first > boundaries.right.second - boundaries.right.first) {
                stack[++top] = boundaries.left;
                l = boundaries.right.first;
                r = boundaries.right.second;
            } else {
                stack[++top] = boundaries.right;
                l = boundaries.left.first;
                r = boundaries.left.second;
            }
        }
    }
}

int main() {
    int *array = (int *)malloc(N * sizeof(int));
    if (!array) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < N; i++) {
        array[i] = rand();
    }

    clock_t begin_time = clock();
    quicksort(array, N);
    printf("Sorting took: %f seconds\n", (float)(clock() - begin_time) / CLOCKS_PER_SEC);

    free(array);
    return 0;
}
