#ifndef GRAPH_H_
#define GRAPH_H_

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

#endif
