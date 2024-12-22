#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "hash.h"

void print_table(int *table, int table_size) {
    for (int i = 0; i < table_size; i++) {
        if (table[i] == -1)
            printf("index>> %d\t|empty|\n", i);
        else
            printf("index>> %d\t|%5d|\n", i, table[i]);
    }
}
int hash_function(int value, int table_size) {
    return (value) % table_size;
}

void init_hash_table(int *table, int table_size) {
    // initialize all values with -1 (indicates empty cell)
    for (int i = 0; i < table_size; i++)
        table[i] = -1;

    for (int i = 0; i < table_size; i++) {
        int data;
        data = rand() % 300;
        // scanf("%d", &data);

        bool inserted = insert(table, data, table_size);

        while (inserted == false) {
            data = rand() % 300;
            // printf("\ndata exists please enter another data: ");
            // scanf("%d", &data);
            inserted = insert(table, data, table_size);
        }
    }
}

bool insert(int *table, int data, int table_size) {
    bool exist = search(table, data, table_size);
    int index = hash_function(data, table_size);

    if (exist == true)
        return false;

    bool empty = false;
    while (empty == false)
        if (table[index] == -1)
            empty = true;
        else
            index = (index + 1) % table_size;

    table[index] = data;
    return true;
}

bool search(int *table, int data, int table_size) {
    int index = hash_function(data, table_size);
    bool run = true;
    if (table[index] == -1)
        return false;

    else {
        while (run) {
            if (table[index] == data)
                return true;
            else {
                index = (index + 1) % table_size;
                if (table[index] == -1)
                    return false;
            }
        }
    }

    return true;
}
