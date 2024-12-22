#include "string.h"
#include <stdlib.h>

#include "Linked_List.h"
#include "types.h"

LinkedList *allocate_list() {
    // Allocates memory for a Linkedlist pointer
    LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
    list->next = NULL;
    return list;
}

LinkedList *linkedlist_insert(LinkedList *list, hash_table_item *item) {
    // Inserts the item onto the Linked List
    if (!list) // list == NULL
    {
        LinkedList *head = allocate_list();
        head->item = item;
        head->next = NULL;
        list = head;
        return list;
    }

    else if (!list->next) {
        LinkedList *node = allocate_list();
        node->item = item;
        node->next = NULL;
        list->next = node;
        return list;
    }

    LinkedList *temp = list->next;
    while (temp->next)
        temp = temp->next;

    LinkedList *node = allocate_list();
    node->item = item;
    node->next = NULL;
    temp->next = node;

    return list;
}

hash_table_item *linkedlist_remove(LinkedList *list) {
    // Removes the head from the linked list
    // and returns the item of the popped element

    if (!list) // list == NULL (empty list)
        return NULL;
    if (!list->next) // list->next == NULL (one item)
        return NULL;

    LinkedList *node = list->next;
    LinkedList *temp = list;
    temp->next = NULL;
    list = node;

    hash_table_item *it = NULL;
    memcpy(temp->item, it, sizeof(hash_table_item));
    free(temp->item->key);
    free(temp->item->value);
    free(temp->item);
    free(temp);

    return it;
}

void free_linkedlist(LinkedList *list) {
    LinkedList *temp = list;
    while (list) {
        temp = list;
        list = list->next;
        free(temp->item->key);
        free(temp->item->value);
        free(temp->item);
        free(temp);
    }
}
