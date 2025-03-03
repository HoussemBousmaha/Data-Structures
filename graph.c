#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int num_nodes;
    int *vertices;
    int **edges;
} Graph;

int hash_function(int value, int table_size) {
    return (value) % table_size;
}

bool has_edge(Graph *g, int from_node, int to_node) {
    assert(g != NULL);
    assert(from_node < g->num_nodes);
    assert(to_node < g->num_nodes);

    return g->edges[from_node][to_node] != 0 || g->edges[to_node][from_node] != 0;
}

bool add_edge(Graph *g, int from_node, int to_node, int weight) {
    assert(g != NULL);
    assert(from_node < g->num_nodes);
    assert(to_node < g->num_nodes);

    if (has_edge(g, from_node, to_node) || from_node == to_node)
        return false;

    g->edges[from_node][to_node] = weight;
    g->edges[to_node][from_node] = weight;

    return true;
}

void add_edges(int number_of_edges, Graph *graph) {
    srand(time(NULL));
    for (int i = 0; i < number_of_edges; i++) {
        int from, to, weight;
        from = rand() % graph->num_nodes;
        to = rand() % graph->num_nodes;
        weight = rand() % 100;
        add_edge(graph, from, to, weight);
    }
}

bool search(int *table, int data, int table_size) {
    int index = hash_function(data, table_size);
    bool run = true;
    if (table[index] == -1)
        return false;

    else {
        while (run) {
            if (table[index] == data)
                return true;
            else {
                index = (index + 1) % table_size;
                if (table[index] == -1)
                    return false;
            }
        }
    }

    return true;
}

void free_graph(Graph *g) {
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

bool insert(int *table, int data, int table_size) {
    bool exist = search(table, data, table_size);
    int index = hash_function(data, table_size);

    if (exist == true)
        return false;

    bool empty = false;
    while (empty == false)
        if (table[index] == -1)
            empty = true;
        else
            index = (index + 1) % table_size;

    table[index] = data;
    return true;
}

void print_table(int *table, int table_size) {
    for (int i = 0; i < table_size; i++) {
        if (table[i] == -1)
            printf("index>> %d\t|empty|\n", i);
        else
            printf("index>> %d\t|%5d|\n", i, table[i]);
    }
}

void init_hash_table(int *table, int table_size) {
    for (int i = 0; i < table_size; i++)
        table[i] = -1;

    for (int i = 0; i < table_size; i++) {
        int data;
        data = rand() % 300;
        bool inserted = insert(table, data, table_size);

        while (inserted == false) {
            data = rand() % 300;
            inserted = insert(table, data, table_size);
        }
    }
}

Graph *make_graph(int edges, int vertices) {
    srand(time(NULL));
    Graph *g = malloc(sizeof(*g));
    if (g == NULL)
        return NULL;

    g->num_nodes = vertices;
    g->edges = calloc(sizeof(int *), vertices);
    g->vertices = calloc(sizeof(int), vertices);

    if (g->edges == NULL || g->vertices == NULL) {
        free(g);
        return NULL;
    }

    for (int row = 0; row < vertices; row++) {
        g->edges[row] = calloc(sizeof(int), vertices);
        if (g->edges[row] == NULL) {
            free_graph(g);
            return NULL;
        }
    }

    init_hash_table(g->vertices, g->num_nodes);
    add_edges(edges, g);

    return g;
}

void dump_graph(Graph *g) {
    printf("graph {\n");
    printf("\tordering = out;\n");
    for (int from = 0; from < g->num_nodes; from++) {
        printf("\t%d [style=filled, fillcolor=\"white\", fontcolor=\"black\", fontsize=12, shape=doublecircle, "
               "fontname=\"Comic Sans MS\"];\n",
               g->vertices[from]);
        for (int to = from; to < g->num_nodes; to++)
            if (g->edges[from][to] && g->edges[to][from]) {
                printf("\t%d [style=filled, fillcolor=\"white\", fontcolor=\"black\", fontsize=12, "
                       "shape=doublecircle, fontname=\"Comic Sans MS\"];\n",
                       g->vertices[to]);
                printf("\t%d -- %d [label=\"%d\"];\n", g->vertices[from], g->vertices[to], g->edges[from][to]);
            }
    }
    printf("}\n");
}

void print_mtx(Graph *g, FILE *f) {
    for (int i = 0; i < g->num_nodes; i++) {
        for (int j = 0; j < g->num_nodes; j++) {
            fprintf(f, "|%2d ", g->edges[i][j]);
        }
        fprintf(f, "\n");
    }
}

int main(void) {
    int edges = 10, vertices = 5;

    Graph *graph = make_graph(edges, vertices);
    dump_graph(graph);
    free_graph(graph);
    return 0;
}
