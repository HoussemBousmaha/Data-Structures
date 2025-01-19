#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_table(int *table, int table_size);
int hash_function(int value, int table_size);
void init_hash_table(int *table, int table_size);
bool insert(int *table, int data, int table_size);
bool search(int *table, int data, int table_size);

typedef struct mygraph {
    int num_nodes;
    int *vertices;
    int **edges;
} graph;

graph *create_graph(int num_nodes);
void destroy_graph(graph *g);
void print_graph(graph *g);
bool add_edge(graph *g, int from_node, int to_node, int weight);
bool has_edge(graph *g, int from_node, int to_node);
void add_edges(int, graph *);
void init_graph(graph *g, int nb_edges);

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
int hash_function(int value, int table_size) {
    return (value) % table_size;
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
    init_hash_table(g->vertices, g->num_nodes);
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

void print_mtx(graph *g, FILE *f) {
    for (int i = 0; i < g->num_nodes; i++) {
        for (int j = 0; j < g->num_nodes; j++) {
            fprintf(f, "|%2d ", g->edges[i][j]);
        }
        fprintf(f, "\n");
    }
}

int main(void) {
    int edges_nb, vertices_nb;
    printf("number of vertices: ");
    scanf("%d", &vertices_nb);

    printf("\nnumber of edges: ");
    scanf("%d", &edges_nb);

    graph *g1 = create_graph(vertices_nb);

    init_graph(g1, edges_nb);

    print_graph(g1);

    destroy_graph(g1);

    return 0;
}
