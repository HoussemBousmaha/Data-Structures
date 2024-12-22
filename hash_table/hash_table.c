#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Linked_List.h"
#include "hash_table.h"
#include "types.h"

unsigned int hash_function(char *key) {
    unsigned int index = 0;
    int p = 31;
    for (int i = 0; key[i]; i++)
        index = (key[i] * p) % TABLE_SIZE;
    p *= p;

    return index;
}

hash_table_item *create_hash_table_item(char *key, char *value) {
    // Creates a pointer to a new hash table hash_table_item
    hash_table_item *item = (hash_table_item *)malloc(sizeof(hash_table_item));
    item->key = (char *)malloc(strlen(key) + 1);
    item->value = (char *)malloc(strlen(value) + 1);

    strcpy(item->key, key);
    strcpy(item->value, value);

    return item;
}

hash_table *init_hash_table(int size) {
    printf("\n\t--->>  This is a hash table\n\n\t--->>  keys : strings || values : strings\n\n");
    // Creates a new hash_table
    hash_table *table = (hash_table *)malloc(sizeof(hash_table));
    table->size = size;
    table->count = 0;
    table->hash_table_items = (hash_table_item **)calloc(table->size, sizeof(hash_table_item *));

    for (int i = 0; i < table->size; i++)
        table->hash_table_items[i] = NULL;

    table->overflow_buckets = create_overflow_buckets(table);
    return table;
}

void handle_collision(hash_table *table, unsigned int index, hash_table_item *item) {
    LinkedList *head = table->overflow_buckets[index];

    if (head == NULL) {
        // We need to create the list
        head = allocate_list();
        head->item = item;
        table->overflow_buckets[index] = head;
    } else
        // Insert to the list
        table->overflow_buckets[index] = linkedlist_insert(head, item);
}

void free_hash_table_item(hash_table_item *item) {
    // Frees an hash_table_item
    free(item->key);
    free(item->value);
    free(item);
}

void free_table(hash_table *table) {
    // Frees the table
    for (int i = 0; i < table->size; i++) {
        hash_table_item *item = table->hash_table_items[i];
        if (item != NULL)
            free_hash_table_item(item);
    }

    // free the overflow buckets linekd list ans it's items
    free_overflow_buckets(table);
    free(table->hash_table_items);
    free(table);
}

bool print_hash_table(hash_table *ht) {
    FILE *f = fopen("out.txt", "w");
    fprintf(f, "\n\tBEGIN\n\n");
    for (int i = 0; i < ht->size; i++) {
        if (ht->hash_table_items[i] == NULL)
            fprintf(f, "\t--->  %-3d  ||  -----\n", i);
        else {
            if (ht->overflow_buckets[i] != NULL)
                fprintf(f, "\t--->  %-3d  ||  {key : %s, value : %s}\n\n\t\t\tLinked List :", i,
                        ht->hash_table_items[i]->key, ht->hash_table_items[i]->value);
            else
                fprintf(f, "\t--->  %-3d  ||  {key : %s, value : %s}", i, ht->hash_table_items[i]->key,
                        ht->hash_table_items[i]->value);
            while (ht->overflow_buckets[i] != NULL) {
                fprintf(f, " -> {%-4s : %s}", ht->overflow_buckets[i]->item->key, ht->overflow_buckets[i]->item->value);
                ht->overflow_buckets[i] = ht->overflow_buckets[i]->next;
            }
            fprintf(f, "\n\n");
        }
    }
    fprintf(f, "\n\n\ttable_size     ----> %d", ht->size);
    fprintf(f, "\n\ttable_elements ----> %d\n", ht->count);
    fprintf(f, "\n\tEND\n\n");
    return true;
}

void hash_table_insert(hash_table *table, char *key, char *value) {
    // Create the hash_table_item
    hash_table_item *item = create_hash_table_item(key, value);

    // Compute the index
    int index = hash_function(key);

    hash_table_item *current_hash_table_item = table->hash_table_items[index];
    if (current_hash_table_item == NULL) {
        // Key does not exist.
        if (table->count == table->size) {
            // Hash Table Full
            printf("Insert Error: Hash Table is full\n");
            free_hash_table_item(item);
            return;
        }

        // Insert directly
        table->hash_table_items[index] = item;
        table->count++;
    } else {
        // Scenario 1: We only need to update value
        if (strcmp(current_hash_table_item->key, key) == 0)
            strcpy(table->hash_table_items[index]->value, value);
        // Scenario 2: Collision
        else
            handle_collision(table, index, item);
        return;
    }
}

void hash_table_insert_multiple_items(hash_table *ht) {
    int number_poeple;
    printf("\n\tInserting a group of items to the hash_table\n\n");
    printf("\n\t-->>  Enter number of items : ");
    scanf("%d", &number_poeple);

    while (number_poeple--) {
        char key[MAX_NAME], value[MAX_NAME];
        random_string(key);
        random_string(value);
        // printf("\n\t---->>  {key, value} = ");
        // scanf("%s %s", key, value);
        hash_table_insert(ht, key, value);
    }
}

void random_string(char *st) {
    int len = rand() % 10 + 1;
    st[len] = 0;
    while (len)
        st[--len] = 'a' + rand() % 26;
}

char *hash_table_search(hash_table *ht, char *key) {
    // Searches the key in the hashtable
    // and returns NULL if item doesn't exist
    int index = hash_function(key);
    hash_table_item *item = ht->hash_table_items[index];
    LinkedList *head = ht->overflow_buckets[index];

    // Ensure that we move to a non NULL hash_table_item
    while (item != NULL) {
        if (strcmp(item->key, key) == 0)
            return item->value;

        if (head == NULL)
            return NULL;

        item = head->item;
        head = head->next;
    }
    return NULL;
}

void hash_table_print_search(hash_table *table, char *key) {
    char *val;
    if ((val = hash_table_search(table, key)) == NULL)
        printf("\n\t%s does not exist\n", key);
    else
        printf("\n\tfound !\n\tkey : %s\t|    value : %s\n", key, val);
}

LinkedList **create_overflow_buckets(hash_table *table) {
    // Create the overflow buckets; an array of linkedlists
    LinkedList **buckets = (LinkedList **)calloc(table->size, sizeof(LinkedList *));
    for (int i = 0; i < table->size; i++)
        buckets[i] = NULL;
    return buckets;
}

void free_overflow_buckets(hash_table *table) {
    // Free all the overflow bucket lists
    LinkedList **buckets = table->overflow_buckets;
    for (int i = 0; i < table->size; i++)
        free_linkedlist(buckets[i]);
    free(buckets);
}
