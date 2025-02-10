#include <stdio.h>
#include <stdlib.h>

#define COUNT 5
#define MAX 300

struct node_t {
    struct node_t *next;
    struct node_t *prev;
    int data;
};

int main(void) {
    struct node_t *head, *temp;

    head = (struct node_t *)malloc(sizeof(struct node_t));
    head->data = rand() % MAX;
    head->next = NULL;
    head->prev = NULL;

    temp = head;

    for (int i = 0; i < COUNT; i++) {
        struct node_t *node = (struct node_t *)malloc(sizeof(struct node_t));

        node->data = rand() % MAX;
        node->next = NULL;

        temp->next = node;
        node->prev = temp;
        temp = node;
    }

    FILE *f = fopen("main.dot", "wb");

    fprintf(f, "digraph G {\n");
    fprintf(f, "\tsize     =\t\"6.6\"   ;\n");
    fprintf(f, "\trankdir  =\t\"LR\"    ;\n");

    for (struct node_t *temp = head; temp->next != NULL; temp = temp->next) {
        fprintf(f, "\t%-7d\t->\t%-8d;\n", temp->data, temp->next->data);
    }

    fprintf(f, "}");
    fclose(f);

    while (temp != NULL) {
        temp = head->next;
        free(head);
        head = temp;
    }
}
