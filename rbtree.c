#include <stdio.h>
#include <stdlib.h>

#define RED 1
#define BLACK 0

typedef struct RBTNode {
    int data;
    int color;
    struct RBTNode* left;
    struct RBTNode* right;
    struct RBTNode* parent;
} RBTNode;

int main() {
    RBTNode* root = NULL;
    RBTNode* SENTINEL = malloc(sizeof(RBTNode));
    SENTINEL->color = BLACK;
    SENTINEL->left = NULL;
    SENTINEL->right = NULL;
    SENTINEL->parent = NULL;
    
    int test_values[] = {7, 3, 18, 10, 22, 8, 11, 26, 2, 6, 13};
    int num_values = sizeof(test_values) / sizeof(test_values[0]);
    
    for (int i = 0; i < num_values; i++) {
        int value = test_values[i];
        RBTNode* node = malloc(sizeof(RBTNode));
        node->data = value;
        node->color = RED;
        node->left = SENTINEL;
        node->right = SENTINEL;
        node->parent = NULL;
        
        if (root == NULL) {
            root = node;
            node->color = BLACK;
            continue;
        }
        
        RBTNode* y = NULL;
        RBTNode* x = root;
        
        while (x != SENTINEL) {
            y = x;
            if (node->data < x->data)
                x = x->left;
            else
                x = x->right;
        }
        
        node->parent = y;
        
        if (y != NULL) {
            if (node->data < y->data)
                y->left = node;
            else
                y->right = node;
        }
            
        RBTNode* current = node;
        
        while (current != root && current->parent && current->parent->color == RED) {
            if (current->parent == current->parent->parent->left) {
                RBTNode* uncle = current->parent->parent->right;
                
                if (uncle && uncle->color == RED) {
                    current->parent->color = BLACK;
                    uncle->color = BLACK;
                    current->parent->parent->color = RED;
                    current = current->parent->parent;
                } else {
                    if (current == current->parent->right) {
                        current = current->parent;
                        
                        if (!current || !current->parent) continue;
                        
                        RBTNode* temp = current;
                        RBTNode* parent = temp->parent;
                        RBTNode* grandparent = parent ? parent->parent : NULL;
                        
                        if (!parent) continue;
                        
                        temp->parent = grandparent;
                        parent->left = temp->right;
                        if (temp->right != SENTINEL)
                            temp->right->parent = parent;
                        temp->right = parent;
                        parent->parent = temp;
                        
                        if (grandparent) {
                            if (grandparent->left == parent)
                                grandparent->left = temp;
                            else
                                grandparent->right = temp;
                        } else {
                            root = temp;
                        }
                    }
                    
                    if (!current || !current->parent || !current->parent->parent) continue;
                    
                    current->parent->color = BLACK;
                    current->parent->parent->color = RED;
                    
                    RBTNode* temp = current->parent->parent;
                    RBTNode* pivot = current->parent;
                    RBTNode* parent = temp ? temp->parent : NULL;
                    
                    if (!temp || !pivot) continue;
                    
                    temp->left = pivot->right;
                    if (pivot->right != SENTINEL)
                        pivot->right->parent = temp;
                    pivot->right = temp;
                    temp->parent = pivot;
                    pivot->parent = parent;
                    
                    if (parent) {
                        if (parent->left == temp)
                            parent->left = pivot;
                        else
                            parent->right = pivot;
                    } else {
                        root = pivot;
                    }
                }
            } else {
                RBTNode* uncle = current->parent->parent->left;
                
                if (uncle && uncle->color == RED) {
                    current->parent->color = BLACK;
                    uncle->color = BLACK;
                    current->parent->parent->color = RED;
                    current = current->parent->parent;
                } else {
                    if (current == current->parent->left) {
                        current = current->parent;
                        
                        if (!current || !current->parent) continue;
                        
                        RBTNode* temp = current;
                        RBTNode* parent = temp->parent;
                        RBTNode* grandparent = parent ? parent->parent : NULL;
                        
                        if (!parent) continue;
                        
                        temp->parent = grandparent;
                        parent->right = temp->left;
                        if (temp->left != SENTINEL)
                            temp->left->parent = parent;
                        temp->left = parent;
                        parent->parent = temp;
                        
                        if (grandparent) {
                            if (grandparent->left == parent)
                                grandparent->left = temp;
                            else
                                grandparent->right = temp;
                        } else {
                            root = temp;
                        }
                    }
                    
                    if (!current || !current->parent || !current->parent->parent) continue;
                    
                    current->parent->color = BLACK;
                    current->parent->parent->color = RED;
                    
                    RBTNode* temp = current->parent->parent;
                    RBTNode* pivot = current->parent;
                    RBTNode* parent = temp ? temp->parent : NULL;
                    
                    if (!temp || !pivot) continue;
                    
                    temp->right = pivot->left;
                    if (pivot->left != SENTINEL)
                        pivot->left->parent = temp;
                    pivot->left = temp;
                    temp->parent = pivot;
                    pivot->parent = parent;
                    
                    if (parent) {
                        if (parent->left == temp)
                            parent->left = pivot;
                        else
                            parent->right = pivot;
                    } else {
                        root = pivot;
                    }
                }
            }
        }
        
        if (root)
            root->color = BLACK;
    }

    printf("digraph RBTree {\n");
    printf("    node [style=filled];\n");
    
    if (root != NULL) {
        RBTNode* queue[1000];
        int front = 0, rear = 0;
        queue[rear++] = root;
        
        while (front < rear) {
            RBTNode* current = queue[front++];
            
            printf("    %d [label=\"%d\", fillcolor=%s, fontcolor=%s];\n", 
                current->data, 
                current->data, 
                current->color == RED ? "red" : "black",
                current->color == RED ? "black" : "white");
            
            if (current->left != SENTINEL) {
                printf("    %d -> %d;\n", current->data, current->left->data);
                queue[rear++] = current->left;
            }
            if (current->right != SENTINEL) {
                printf("    %d -> %d;\n", current->data, current->right->data);
                queue[rear++] = current->right;
            }
        }
    }
    
    printf("}\n");
    return 0;
}
