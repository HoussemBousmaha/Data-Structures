#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M 3
#define MAX_KEYS (2 * M - 1)
#define MAX_CHILDREN (2 * M)

struct BTreeNode {
    int keys[MAX_KEYS];
    struct BTreeNode* children[MAX_CHILDREN];
    int num_keys;
    int is_leaf;
};

int main() {
    srand(time(NULL));
    
    struct BTreeNode* root = malloc(sizeof(struct BTreeNode));
    root->num_keys = 0;
    root->is_leaf = 1;
    
    for (int n = 0; n < 100; n++) {
        int key = rand() % 1000;
        struct BTreeNode* current = root;
        
        if (current->num_keys == MAX_KEYS) {
            struct BTreeNode* new_root = malloc(sizeof(struct BTreeNode));
            struct BTreeNode* new_node = malloc(sizeof(struct BTreeNode));
            
            new_root->children[0] = root;
            new_root->is_leaf = 0;
            new_root->num_keys = 0;
            
            new_node->is_leaf = root->is_leaf;
            new_node->num_keys = M - 1;
            
            for (int i = 0; i < M - 1; i++) {
                new_node->keys[i] = root->keys[i + M];
            }
            
            if (!root->is_leaf) {
                for (int i = 0; i < M; i++) {
                    new_node->children[i] = root->children[i + M];
                }
            }
            
            root->num_keys = M - 1;
            new_root->keys[0] = root->keys[M - 1];
            new_root->children[1] = new_node;
            new_root->num_keys = 1;
            
            root = new_root;
            current = new_root;
        }
        
        while (!current->is_leaf) {
            int i = current->num_keys - 1;
            while (i >= 0 && key < current->keys[i]) {
                i--;
            }
            i++;
            
            if (current->children[i]->num_keys == MAX_KEYS) {
                struct BTreeNode* child = current->children[i];
                struct BTreeNode* new_node = malloc(sizeof(struct BTreeNode));
                
                new_node->is_leaf = child->is_leaf;
                new_node->num_keys = M - 1;
                
                for (int j = 0; j < M - 1; j++) {
                    new_node->keys[j] = child->keys[j + M];
                }
                
                if (!child->is_leaf) {
                    for (int j = 0; j < M; j++) {
                        new_node->children[j] = child->children[j + M];
                    }
                }
                
                child->num_keys = M - 1;
                
                for (int j = current->num_keys; j > i; j--) {
                    current->children[j + 1] = current->children[j];
                }
                for (int j = current->num_keys - 1; j >= i; j--) {
                    current->keys[j + 1] = current->keys[j];
                }
                
                current->keys[i] = child->keys[M - 1];
                current->children[i + 1] = new_node;
                current->num_keys++;
                
                if (key > current->keys[i]) {
                    i++;
                }
            }
            
            current = current->children[i];
        }
        
        int pos = current->num_keys - 1;
        while (pos >= 0 && current->keys[pos] > key) {
            current->keys[pos + 1] = current->keys[pos];
            pos--;
        }
        current->keys[pos + 1] = key;
        current->num_keys++;
    }
    
    printf("digraph btree {\n    node [shape=record];\n\n");
    
    struct BTreeNode* queue[1000];
    int front = 0, rear = 0;
    queue[rear++] = root;
    
    while (front < rear) {
        struct BTreeNode* node = queue[front++];
        printf("    node%p [label=\"", (void*)node);
        
        for (int i = 0; i < node->num_keys; i++) {
            if (i > 0) printf("|");
            printf("%d", node->keys[i]);
        }
        printf("\"];\n");
        
        if (!node->is_leaf) {
            for (int i = 0; i <= node->num_keys; i++) {
                printf("    node%p -> node%p;\n", (void*)node, (void*)node->children[i]);
                queue[rear++] = node->children[i];
            }
        }
    }
    printf("}\n");
    
    return 0;
}
