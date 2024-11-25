#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

typedef struct node {
    int frequency;
    char data;
    int pos;
    node *left, *right;
} node;

typedef struct heap {
    int capacity;
    node **elements;
} heap;

node *new_node(char val, int freq) {
    node *n = new node;
    n->data = val;
    n->frequency = freq;
    n->left = n->right = nullptr;
    return n;
}

void heapify(heap *heap, int i) {
    int N = heap->capacity;
    int smallest = i;  // Initialize smallest as root
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2

    // If left child is larger than root
    if (l < N && heap->elements[l]->frequency < heap->elements[smallest]->frequency) smallest = l;

    // If right child is larger than smallest so far
    if (r < N && heap->elements[r]->frequency < heap->elements[smallest]->frequency) smallest = r;

    // If smallest is not root
    if (smallest != i) {
        std::swap(heap->elements[i], heap->elements[smallest]);

        // Recursively heapify the affected sub-tree
        heapify(heap, smallest);
    }
}

heap *build_heap(node **a, int size) {
    heap *h = (heap *)malloc(sizeof(heap));
    h->elements = (node **)calloc(sizeof(node *), size);
    h->capacity = size;
    h->elements = a;
    for (int i = size / 2 - 1; i >= 0; i--) {
        heapify(h, i);
    }
    return h;
}

void insert_heap(heap *h, node *n) {

    h->capacity++;

    int data_index = h->capacity - 1;
    h->elements[data_index] = n;

    int parent_index = (data_index - 1) / 2;

    while (h->elements[data_index]->frequency < h->elements[parent_index]->frequency) {
        node *tmp = h->elements[data_index];
        h->elements[data_index] = h->elements[parent_index];
        h->elements[parent_index] = tmp;

        data_index = parent_index;
        parent_index = (data_index - 1) / 2;
    }
}

node *delete_heap(heap *h) {
    node *ans = h->elements[0];

    h->elements[0] = h->elements[h->capacity - 1];
    h->capacity--;

    heapify(h, 0);

    return ans;
}

node *build_huffman_tree(char *s) {
    std::vector<std::pair<int, char>> a(256);

    long int size = strlen(s);

    for (int i = 0; i < size; i++) {
        a[s[i]].second = s[i];
        a[s[i]].first++;
    }

    sort(a.begin(), a.end());

    heap *h = (heap *)malloc(sizeof(heap));
    h->elements = (node **)calloc(sizeof(node *), 256);
    h->capacity = 0;

    for (int i = 0; i < 256; i++) {
        if (a[i].first != 0) {
            node *n = new_node(a[i].second, a[i].first);
            n->pos = i;
            insert_heap(h, n);
        }
    }

    while (h->capacity != 1) {
        node *first = delete_heap(h);
        node *second = delete_heap(h);

        node *top = new_node('\0', first->frequency + second->frequency);

        top->left = first;
        top->right = second;
        top->pos = fmax(first->pos, second->pos);

        insert_heap(h, top);
    }

    return h->elements[0];
}

char *read_file(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long int size = ftell(file);
    rewind(file);

    char *content = (char *)calloc(size + 1, 1);

    fread(content, 1, size, file);

    return content;
}

void draw_tree(node *R, FILE *f, int *nbNil) {
    int info, info_fg, info_fd;
    if (R != nullptr) {
        info = R->frequency;
        // Dessiner un arc vers le fils gauche
        if (R->left != nullptr && R->right != nullptr) {

            info_fg = R->left->frequency;
            if (R->left->data == '\0') {
                fprintf(f, "  \"{%d %c %d}\" -> \"{%d %c %d}\"[label=0, color=red] \n", info, R->data != '\0' ? R->data : ' ', R->pos, info_fg, ' ',
                        R->left->pos);
            } else {
                fprintf(f, "  \"{%d %c %d}\" -> \"{%d - %c}\"[label=0, color=red] \n", info, R->data != '\0' ? R->data : ' ', R->pos, info_fg,
                        R->left->data);
            }

            // Dessiner un fils NIL virtuel et invisible au milieu (pour une meilleure s�paration des fils gauches et droits)
            fprintf(f, "  \"NIL%d\" [style=invis];\n", *nbNil);
            fprintf(f, "  \"{%d %c %d}\" -> \"NIL%d\" ", info, R->data != '\0' ? R->data : ' ', R->pos, (*nbNil)++);
            fprintf(f, " [style=invis];\n");

            info_fd = R->right->frequency;

            if (R->right->data == '\0') {
                fprintf(f, "  \"{%d %c %d}\" -> \"{%d %c %d}\"[label=1, color=blue] \n", info, R->data != '\0' ? R->data : ' ', R->pos, info_fd, ' ',
                        R->right->pos);
            } else {
                fprintf(f, "  \"{%d %c %d}\" -> \"{%d - %c}\"[label=1, color=blue] \n", info, R->data != '\0' ? R->data : ' ', R->pos, info_fd,
                        R->right->data);
            }
        }

        // Dessiner les sous-arbres gauche et droit
        draw_tree(R->left, f, nbNil);
        draw_tree(R->right, f, nbNil);
    }
}

void draw_huffman_tree(node *root) {
    int nil_cnt;
    FILE *f;

    if (root == nullptr)
        printf("> ERREUR : Arbre vide !");
    else {
        f = fopen("../out/out.dot", "w");

        fprintf(f, "digraph arbre {\n");

        nil_cnt = 0;
        draw_tree(root, f, &nil_cnt);

        fprintf(f, "}\n");

        fclose(f);

        system("dot -Tjpg ../out/out.dot -o ../out/out.jpg");
        system("open ../out/out.jpg");
    }
}

int main(void) {
    char file_name[] = "in.txt";
    char *s = read_file(file_name);
    node *root = build_huffman_tree(s);

    draw_huffman_tree(root);

    return 0;
}
