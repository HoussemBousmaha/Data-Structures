#include <stdbool.h>
#include <stdio.h>

#include "graph.h"

int main(void) {

    int edges_nb, vertices_nb;
    printf("number of vertices: ");
    scanf("%d", &vertices_nb);

    printf("\nnumber of edges: ");
    scanf("%d", &edges_nb);

    graph *g1 = create_graph(vertices_nb);

    init_graph(g1, edges_nb);

    // FILE* f=fopen("..\\output\\out.txt", "w");
    // print_mtx(g1,f);

    print_graph(g1);

    destroy_graph(g1);

    return 0;
}

void print_mtx(graph *g, FILE *f) {
    for (int i = 0; i < g->num_nodes; i++) {
        for (int j = 0; j < g->num_nodes; j++) {
            fprintf(f, "|%2d ", g->edges[i][j]);
        }
        fprintf(f, "\n");
    }
}
