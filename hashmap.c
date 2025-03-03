#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define HASH_MAP_CAPACITY 1024
#define STRINGS_COUNT 500
#define STRING_LENGTH 5

typedef struct {
    char K[STRING_LENGTH];
    int V;
    bool occupied;
} HashEntry;

static HashEntry map[HASH_MAP_CAPACITY] = {0};
static const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

size_t hash(const char *input) {
    size_t hash = 5381;
    int c;

    while ((c = *input++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash % HASH_MAP_CAPACITY;
}

void hash_insert(const char *K, int V) {
    size_t index = hash(K);

    int collisions = 0;

    while (map[index].occupied) {
        index = (index + 1) % HASH_MAP_CAPACITY;
        collisions++;
    }

    strcpy(map[index].K, K);
    map[index].V = V;
    map[index].occupied = true;
}

int hash_search(const char *K) {
    size_t index = hash(K);

    while (map[index].occupied) {
        if (strcmp(map[index].K, K) == 0) {
            return map[index].V;
        }
        index = (index + 1) % HASH_MAP_CAPACITY;
    }

    return -1;
}

int main(void) {
    srand(time(NULL));

    for (int i = 0; i < STRINGS_COUNT; i++) {
        char K[STRING_LENGTH];
        for (size_t j = 0; j < STRING_LENGTH - 1; j++) {
            int c_idx = rand() % (sizeof(charset) - 1);
            char c = charset[c_idx];
            K[j] = c;
        }
        K[STRING_LENGTH - 1] = '\0';

        int V = rand() % 1000;
        hash_insert(K, V);
    }

    return 0;
}
