#include <iostream>
#include <stack>
#include <stdlib.h>

using namespace std;

struct node {
    node *left, *right;
    int val;
    int ht;
};

void dessinArbre(node *R, FILE *f, int *nbNil) {
    int info, info_fg, info_fd;
    if (R != nullptr) {
        info = R->val;
        // Dessiner un arc vers le fils gauche
        if (R->left != nullptr) {

            info_fg = R->left->val;
            fprintf(f, "  \"%d\" -> \"%d\" \n", info, info_fg);
        } else {
            fprintf(f, "  \"NIL%d\" [style=invis];\n", *nbNil);
            fprintf(f, "  \"%d\" -> \"NIL%d\" ", info, (*nbNil)++);
            fprintf(f, " [style=invis];\n");
        }

        // Dessiner un fils NIL virtuel et invisible au milieu (pour une meilleure
        // s�paration des fils gauches et droits)
        fprintf(f, "  \"NIL%d\" [style=invis];\n", *nbNil);
        fprintf(f, "  \"%d\" -> \"NIL%d\" ", info, (*nbNil)++);
        fprintf(f, " [style=invis];\n");

        // Dessiner un arc vers le fils droit
        if (R->right != nullptr) {
            info_fd = R->right->val;
            fprintf(f, "  \"%d\" -> \"%d\" \n", info, info_fd);
        } else {
            fprintf(f, "  \"NIL%d\" [style=invis];\n", *nbNil);
            fprintf(f, "  \"%d\" -> \"NIL%d\" ", info, (*nbNil)++);
            fprintf(f, " [style=invis];\n");
        }

        // Dessiner les sous-arbres gauche et droit
        dessinArbre(R->left, f, nbNil);
        dessinArbre(R->right, f, nbNil);
    }
}
void DrawTree(node *root) {

    int nbNil;
    FILE *f;

    if (root == nullptr)
        printf("> ERREUR : Arbre vide !");
    else {
        char fname[50];
        snprintf(fname, sizeof(fname), "../out/out.dot");
        f = fopen(fname, "w");

        fprintf(f, "digraph arbre {\n");

        nbNil = 0;
        dessinArbre(root, f, &nbNil);

        fprintf(f, "}\n");
        fclose(f);
    }
}

node *new_node(int val) {
    node *n = (node *)malloc(sizeof(node));
    n->val = val;
    n->left = n->right = nullptr;
    n->ht = 0;

    return n;
}

int height(node *root) {
    if (root == nullptr) {
        return -1;
    }

    return 1 + max(height(root->left), height(root->right));
}

node *right_rotation(node *current, node *parent) {

    node *l_child = current->left;
    if (l_child != nullptr) {
        node *tmp = l_child->right;
        l_child->right = current;
        current->left = tmp;

        if (parent == nullptr) {
            return l_child;
        }

        if (parent->val < current->val) {
            parent->right = l_child;
        } else {
            parent->left = l_child;
        }
    }

    return l_child;
}

node *left_rotation(node *current, node *parent) {
    node *r_child = current->right;

    if (r_child != nullptr) {
        node *tmp = r_child->left;
        r_child->left = current;
        current->right = tmp;

        if (parent == nullptr) {
            return r_child;
        }

        if (parent->val > current->val) {
            parent->left = r_child;
        } else {
            parent->right = r_child;
        }
    }

    return r_child;
}

bool insert_bst(node *root, node *n, stack<node *> &st) {

    bool stop = false;

    node *prev = nullptr;

    while (!stop) {
        prev = root;

        if (root->val > n->val) {
            root = root->left;
            st.push(prev);
        } else if (root->val < n->val) {
            root = root->right;
            st.push(prev);
        } else {
            stop = true;
            return false;
        }

        if (root == nullptr) {
            stop = true;
        }
    }

    if ((prev)->val < n->val) {
        (prev)->right = n;
    } else if ((prev)->val > n->val) {
        (prev)->left = n;
    } else {
        return false;
    }

    return true;
}

node *insert_avl(node *root, int val) {
    node *n = new_node(val);

    if (root == nullptr) {
        return n;
    }

    stack<node *> path;
    bool inserted = insert_bst(root, n, path);

    node *current;
    node *parent;
    node *grand_parent;

    if (inserted == true) {
        parent = n;
        while (path.empty() == false) {
            current = parent;
            parent = path.top();
            path.pop();
            if (path.empty() == false)
                grand_parent = path.top();
            else {
                grand_parent = nullptr;
            }

            parent->ht = height(parent);

            if (height(parent->left) - height(parent->right) == -2) {
                if (height(current->left) - height(current->right) == 1) {
                    current = right_rotation(current, parent);

                    current->ht = height(current);

                    current->right->ht = height(current->right);

                    parent = left_rotation(parent, grand_parent);

                    parent->ht = height(parent);

                    parent->left->ht = height(parent->left);
                } else if (height(current->left) - height(current->right) == -1) {
                    parent = left_rotation(parent, grand_parent);

                    parent->left->ht = height(parent->left);
                    parent->ht = height(parent);
                }
            } else if (height(parent->left) - height(parent->right) == 2) {
                if (height(current->left) - height(current->right) == 1) {

                    parent = right_rotation(parent, grand_parent);

                    parent->right->ht = height(parent->right);
                    parent->ht = height(parent);
                } else if (height(current->left) - height(current->right) == -1) {
                    current = left_rotation(current, parent);
                    current->ht = height(current);

                    current->left->ht = height(current->left);

                    parent = right_rotation(parent, grand_parent);

                    parent->ht = height(parent);

                    parent->right->ht = height(parent->right);
                }
            }
        }
    }

    else {
        parent = root;
    }
    return parent;
}

int main(void) {
    srand(time(nullptr));
    node *root = nullptr;
    int n;

    cout << "Number of Nodes: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        int data;
        data = rand() % 1000;
        root = insert_avl(root, data);
    }

    DrawTree(root);

    return 0;
}
