#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

#define NODE_MAX 1000
#define NB_NODES 20

int main(void) {
    Node *root = bst_insert(NULL, rand() % NODE_MAX);
    for (size_t i = 0; i < NB_NODES; i++) {
        bst_insert(root, rand() % NODE_MAX);
    }

    bst_export_file(root, stdout);

    return 0;
}
