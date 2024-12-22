#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

Node *bst_create_node(int key) {
    Node *node = malloc(sizeof(Node));
    node->key = key;
    node->left = node->right = NULL;

    return node;
}

Node *bst_insert(Node *node, int key) {
    if (node == NULL)
        return bst_create_node(key);

    if (key < node->key) {
        node->left = bst_insert(node->left, key);
    } else if (key > node->key) {
        node->right = bst_insert(node->right, key);
    }
    return node;
}

void bst_dump_dot(Node *node, FILE *stream) {
    if (node == NULL)
        return;

    fprintf(stream, "    %d [label=\"%d\"];\n", node->key, node->key);
    if (node->left != NULL) {
        fprintf(stream, "    %d -> %d;\n", node->key, node->left->key);
        bst_dump_dot(node->left, stream);
    }
    if (node->right != NULL) {
        fprintf(stream, "    %d -> %d;\n", node->key, node->right->key);
        bst_dump_dot(node->right, stream);
    }
}

void bst_export_file(Node *tree, FILE *stream) {
    fprintf(stream, "digraph BST {\n");
    fprintf(stream, "    node [fontname=\"Arial\"];\n");
    bst_dump_dot(tree, stream);
    fprintf(stream, "}\n");
}
