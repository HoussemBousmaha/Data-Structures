#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 1024
#define NUM_STRINGS 100
#define STRING_LENGTH 32

typedef struct {
    char key[STRING_LENGTH];
    int value;
    int occupied; // 0 = empty, 1 = occupied
} HashEntry;

static HashEntry map[MAX_SIZE] = {0};
static const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

size_t hash(const char *input) {
    size_t hash = 5381;
    int c;

    while ((c = *input++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash % MAX_SIZE;
}

void insert(const char *key, int value) {
    size_t index = hash(key);

    while (map[index].occupied) {
        index = (index + 1) % MAX_SIZE;
    }

    strcpy(map[index].key, key);
    map[index].value = value;
    map[index].occupied = 1;
}

int search(const char *key) {
    size_t index = hash(key);

    while (map[index].occupied) {
        if (strcmp(map[index].key, key) == 0) {
            return map[index].value;
        }
        index = (index + 1) % MAX_SIZE;
    }

    return -1; // Key not found
}

int main(void) {
    srand(time(NULL));

    for (int i = 0; i < NUM_STRINGS; i++) {
        int value = rand() % 1000;

        char key[STRING_LENGTH];
        for (size_t j = 0; j < STRING_LENGTH - 1; j++) {
            key[j] = charset[rand() % (sizeof(charset) - 1)];
        }
        key[STRING_LENGTH - 1] = '\0';

        insert(key, value);
    }

    // Print stored keys and values
    printf("Stored key-value pairs:\n");
    for (size_t i = 0; i < MAX_SIZE; i++) {
        if (map[i].occupied) {
            printf("Index %zu: Key = %s, Value = %d\n", i, map[i].key, map[i].value);
        }
    }

    return 0;
}
