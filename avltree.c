#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define max(a,b) ((a) > (b) ? (a) : (b))
#define height(n) ((n) == NULL ? -1 : (n)->height)

typedef struct AVLTreeNode {
    int key;
    struct AVLTreeNode* left;
    struct AVLTreeNode* right;
    int height;
} AVLTreeNode;

int main(void) {
    AVLTreeNode* root = NULL;
    AVLTreeNode** stack = malloc(sizeof(AVLTreeNode*) * 100);
    AVLTreeNode** print_stack = malloc(sizeof(AVLTreeNode*) * 100);
    int* visited = malloc(sizeof(int) * 100);
    int stack_top = 0;
    int print_top = 0;
    AVLTreeNode* current;

    srand(time(NULL));
    int values[] = {42, 15, 88, 33, 91, 7, 65, 29, 76, 51, 23, 94, 11, 82, 37, 59, 18, 46, 70, 85};

    for (int i = 0; i < 20; i++) {
        int key = values[i];
        AVLTreeNode* new_node = malloc(sizeof(AVLTreeNode));
        new_node->key = key;
        new_node->left = new_node->right = NULL;
        new_node->height = 0;

        if (!root) {
            root = new_node;
            continue;
        }

        stack_top = 0;
        current = root;
        while (current) {
            stack[stack_top++] = current;
            if (key < current->key)
                current = current->left;
            else if (key > current->key)
                current = current->right;
            else {
                free(new_node);
                goto next_insert;
            }
        }

        current = stack[stack_top - 1];
        if (key < current->key)
            current->left = new_node;
        else
            current->right = new_node;

        while (stack_top > 0) {
            current = stack[--stack_top];
            current->height = 1 + max(height(current->left), height(current->right));
            int balance = height(current->left) - height(current->right);

            if (balance > 1) {
                if (key < current->left->key) {
                    AVLTreeNode* y = current->left;
                    current->left = y->right;
                    y->right = current;
                    current->height = 1 + max(height(current->left), height(current->right));
                    y->height = 1 + max(height(y->left), height(y->right));
                    if (stack_top > 0)
                        stack[stack_top - 1]->left = y;
                    else
                        root = y;
                } else {
                    AVLTreeNode* y = current->left;
                    AVLTreeNode* x = y->right;
                    y->right = x->left;
                    current->left = x->right;
                    x->left = y;
                    x->right = current;
                    current->height = 1 + max(height(current->left), height(current->right));
                    y->height = 1 + max(height(y->left), height(y->right));
                    x->height = 1 + max(height(x->left), height(x->right));
                    if (stack_top > 0)
                        stack[stack_top - 1]->left = x;
                    else
                        root = x;
                }
            } else if (balance < -1) {
                if (key > current->right->key) {
                    AVLTreeNode* y = current->right;
                    current->right = y->left;
                    y->left = current;
                    current->height = 1 + max(height(current->left), height(current->right));
                    y->height = 1 + max(height(y->left), height(y->right));
                    if (stack_top > 0)
                        stack[stack_top - 1]->right = y;
                    else
                        root = y;
                } else {
                    AVLTreeNode* y = current->right;
                    AVLTreeNode* x = y->left;
                    y->left = x->right;
                    current->right = x->left;
                    x->right = y;
                    x->left = current;
                    current->height = 1 + max(height(current->left), height(current->right));
                    y->height = 1 + max(height(y->left), height(y->right));
                    x->height = 1 + max(height(x->left), height(x->right));
                    if (stack_top > 0)
                        stack[stack_top - 1]->right = x;
                    else
                        root = x;
                }
            }
        }
        next_insert:;
    }

    printf("digraph AVLTree {\n");
    printf("    node [shape=circle];\n");
    
    if (root) {
        print_stack[print_top] = root;
        visited[print_top] = 0;
        print_top++;
        
        while (print_top > 0) {
            current = print_stack[print_top - 1];
            if (visited[print_top - 1] == 0) {
                visited[print_top - 1] = 1;
                if (current->left) {
                    printf("    %d -> %d;\n", current->key, current->left->key);
                    print_stack[print_top] = current->left;
                    visited[print_top] = 0;
                    print_top++;
                }
            } else if (visited[print_top - 1] == 1) {
                visited[print_top - 1] = 2;
                if (current->right) {
                    printf("    %d -> %d;\n", current->key, current->right->key);
                    print_stack[print_top] = current->right;
                    visited[print_top] = 0;
                    print_top++;
                }
            } else {
                print_top--;
            }
        }
    }
    
    printf("}\n");

    free(stack);
    free(print_stack);
    free(visited);
    return 0;
}
