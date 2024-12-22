#include <iostream>
#include <vector>

using namespace std;

#include "heap_draw.hpp"

void Draw_Heap(vector<int> tree, int *sortie) {

    int nbNil;
    char file_path[20];
    FILE *f;

    if (tree.size() == 0)
        cout << "> ERREUR : Arbre vide !";
    else {
        snprintf(file_path, sizeof(file_path), "out%d.dot", *sortie);
        f = fopen(file_path, "w");
        fprintf(f, "graph arbre {\n");
        fprintf(f, "\tordering = out;\n");
        fprintf(f, "\tsplines = false;\n");

        nbNil = 0;

        dessinArbre(tree, 0, f, &nbNil, tree.size());
        fprintf(f, "}\n");
        fclose(f);

        (*sortie)++;

        // printf("\n\n>> L'arbre est dessine correctement !\n\n");
    }
}

void dessinArbre(vector<int> tree, int index, FILE *f, int *nbNil, int treesize) {
    int info, info_fg, info_fd;
    if (index < treesize) {
        info = tree[index];
        // Dessiner un arc vers le fils gauche
        if (2 * index + 1 < treesize) {

            info_fg = tree[2 * index + 1];
            fprintf(f, "  \"{%d, %d}\" -- \"{%d, %d}\" \n", info, index, info_fg, 2 * index + 1);
        } else {
            fprintf(f, "  \"NIL%d\" [style=invis];\n", *nbNil);
            fprintf(f, "  \"{%d, %d}\" -- \"NIL%d\" ", info, index, (*nbNil)++);
            fprintf(f, " [style=invis];\n");
        }

        // Dessiner un fils NIL virtuel et invisible au milieu (pour une meilleure s�paration des fils gauches et
        // droits)
        fprintf(f, "  \"NIL%d\" [style=invis];\n", *nbNil);
        fprintf(f, "  \"{%d, %d}\" -- \"NIL%d\" ", info, index, (*nbNil)++);
        fprintf(f, " [style=invis];\n");

        // Dessiner un arc vers le fils droit
        if (2 * index + 2 < treesize) {
            info_fd = tree[2 * index + 2];
            fprintf(f, "  \"{%d, %d}\" -- \"{%d, %d}\" \n", info, index, info_fd, 2 * index + 2);
        } else {
            fprintf(f, "  \"NIL%d\" [style=invis];\n", *nbNil);
            fprintf(f, "  \"{%d, %d}\" -- \"NIL%d\" ", info, index, (*nbNil)++);
            fprintf(f, " [style=invis];\n");
        }

        // Dessiner les sous-arbres gauche et droit
        dessinArbre(tree, 2 * index + 1, f, nbNil, treesize);
        dessinArbre(tree, 2 * index + 2, f, nbNil, treesize);
    }
}
