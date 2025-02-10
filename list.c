#include <stdio.h>
#include <stdlib.h>

#define COUNT 5
#define MAX 300

struct ListNode {
    struct ListNode *next;
    int data;
};

int main(void) {
    struct ListNode *head, *temp;

    head = (struct ListNode *)malloc(sizeof(struct ListNode));
    head->data = rand() % MAX;
    head->next = NULL;

    temp = head;

    for (int i = 0; i < COUNT; i++) {
        struct ListNode *node = (struct ListNode *)malloc(sizeof(struct ListNode));
        node->data = rand() % MAX;
        node->next = NULL;
        temp->next = node;
        temp = node;
    }

    printf("digraph G {\n");
    printf("    size     =\"6.6\";\n");
    printf("    rankdir  =\"LR\";\n");

    for (struct ListNode *temp = head; temp->next != NULL; temp = temp->next) {
        printf("    %d->%d;\n", temp->data, temp->next->data);
    }

    printf("}\n");

    while (temp != NULL) {
        temp = head->next;
        free(head);
        head = temp;
    }
}
