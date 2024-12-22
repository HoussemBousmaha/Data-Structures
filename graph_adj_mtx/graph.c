#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "graph.h"
#include "hash.h"

graph *create_graph(int num_nodes) {

    srand(time(NULL));
    graph *g = malloc(sizeof(*g));
    if (g == NULL)
        return NULL;

    // allocate our matrix
    g->num_nodes = num_nodes;

    // allocating "num_nodes" pointer to bool
    g->edges = calloc(sizeof(int *), num_nodes);
    // allocating "num_nodes" int ( 4bits ) records
    g->vertices = calloc(sizeof(int), num_nodes);

    if (g->edges == NULL || g->vertices == NULL) {
        free(g);
        return NULL;
    }

    // allocating "num_nodes" arrays of bools such that each array contains "num_nodes" boolean
    for (int row = 0; row < num_nodes; row++) {
        // allocating "num_nodes" bool (which is just 1 bit) records
        g->edges[row] = calloc(sizeof(int), num_nodes);
        if (g->edges[row] == NULL) {
            // cleanup again
            destroy_graph(g);
            return NULL;
        }
    }

    return g;
}

void init_graph(graph *g, int nb_edges) {
    // generates exacly "num_nodes" distinct values and arrange them
    // in a hash table (g->vertices)
    // this hash table is a special one because it has exacly "num_nodes" elements
    // and there is no (0 <= j,i < num_nodes) such that T[i] == T[j]

    // this is necessary beacause our graph is undirected and contains exactly "num_nodes" vertices
    // init_hash_table(g->vertices, g->num_nodes);
    init_hash_table(g->vertices, g->num_nodes);

    // add edges between random vertices in the graph
    add_edges(nb_edges, g);
}

void destroy_graph(graph *g) {
    if (g->edges == NULL || g->vertices == NULL) {
        free(g);
        return;
    }

    for (int i = 0; i < g->num_nodes; i++) {
        if (g->edges[i] != NULL)
            free(g->edges[i]);
    }

    free(g->vertices);
    free(g->edges);
    free(g);
}
void print_graph(graph *g) {
    FILE *out = fopen("..\\output\\out.dot", "w");

    fprintf(out, "graph {\n");
    fprintf(out, "\tordering = out;\n");
    // fprintf(out, "\tsplines = false;\n");
    for (int from = 0; from < g->num_nodes; from++) {
        fprintf(out,
                "\t%d [style=filled, fillcolor=\"white\", fontcolor=\"black\", fontsize=12, shape=doublecircle, "
                "fontname=\"Comic Sans MS\"];\n",
                g->vertices[from]);
        for (int to = from; to < g->num_nodes; to++)
            if (g->edges[from][to] && g->edges[to][from]) {
                fprintf(out,
                        "\t%d [style=filled, fillcolor=\"white\", fontcolor=\"black\", fontsize=12, "
                        "shape=doublecircle, fontname=\"Comic Sans MS\"];\n",
                        g->vertices[to]);
                fprintf(out, "\t%d -- %d [label=\"%d\"];\n", g->vertices[from], g->vertices[to], g->edges[from][to]);
            }
    }
    fprintf(out, "}\n");
    // system("..\\output\\out.png");
}
bool add_edge(graph *g, int from_node, int to_node, int weight) {
    assert(g != NULL);
    assert(from_node < g->num_nodes);
    assert(to_node < g->num_nodes);

    if (has_edge(g, from_node, to_node) || from_node == to_node)
        return false;

    g->edges[from_node][to_node] = weight;
    g->edges[to_node][from_node] = weight;

    return true;
}
bool has_edge(graph *g, int from_node, int to_node) {
    assert(g != NULL);
    assert(from_node < g->num_nodes);
    assert(to_node < g->num_nodes);

    return g->edges[from_node][to_node] != 0 || g->edges[to_node][from_node] != 0;
}

void add_edges(int number_of_edges, graph *graph) {
    srand(time(NULL));
    for (int i = 0; i < number_of_edges; i++) {
        int from, to, weight;
        // printf("from, to, weight: ");
        // scanf("%d %d %d", &from, &to, &weight);
        from = rand() % graph->num_nodes;
        to = rand() % graph->num_nodes;
        weight = rand() % 100;
        // printf("\n");
        // scanf("%d %d", &from, &to);

        add_edge(graph, from, to, weight);
    }
}
