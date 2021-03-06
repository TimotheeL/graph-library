/*
	PW2 - Graph Library Representation by Adjacency Lists
	graph.h
	Thibault BERTIN - Timothée LAURENT
	Master 1 CMI Informatique - TP1A
*/
#ifndef GRAPH_H
#define GRAPH_H

#define WHITE 0
#define GRAY 1
#define BLACK 2

#include "list.h"

#ifdef __cplusplus
extern "C" {
#endif

struct Graph {
	bool isDirected;
	int nbMaxNodes;
	struct Neighbour **adjList;
};

/*
 * Create an empty graph"
 * Params:
 * - Graph *self: the graph you wish to create
 * - bool isDirected: true if the graph is directed
 * - int nbMaxNodes: the maximum number of nodes the graph can have
 * Return:
 * - void
 */
void create_graph(struct Graph *self, bool isDirected, int nbMaxNodes);

/*
 * Destroy a graph
 * Params:
 * - Graph *self: the graph you wish to destroy
 * Return:
 * - void
 */
void destroy_graph(struct Graph *self);

/*
 * Load a graph from a file
 * Params:
 * - Graph *self: the graph structure in which to load the saved graph
 * - char * filename: the file from which you wish to load a graph
 * Return:
 * - int 0: success, -1: error
 */
int load_graph(struct Graph *self, const char *filename);

/*
 * Add a node to a graph
 * Params:
 * - Graph *self: the graph in which you wish to add a node 
 *
 * Return:
 * - int 0: success, -1: error
 */
int add_node(struct Graph *self, int node);

/*
 * Remove a node from a graph
 * Params:
 * - Graph *self: the graph from which you wish to remove a node
 * - int node: the node you wish to remove
 * Return:
 * - int 0: success, -1: error
 */
int remove_node(struct Graph *self, int node);

/*
 * Add an edge to a graph
 * Params:
 * - Graph *self: the graph in which you wish to add an edge
 * - int nodeTail: the node from which the edge starts
 * - int nodeHead: the node to which the edge arrives
 * - int weight: the weight of the edge
 * - bool symmetric: symmetric edge is added if true
 * Return:
 * - int 0: success, -1: error
 */
int add_edge(struct Graph *self, int nodeTail, int nodeHead, int weight, bool symmetric);

/*
 * Remove an edge from a graph
 * Params:
 * - Graph *self: the graph from which you wish to remove an edge
 * - int nodeTail: the node from which the edge starts
 * - int nodeHead: the node to which the edge arrives
 * Return:
 * - int 0: success, -1: error
 */
int remove_edge(struct Graph *self, int nodeTail, int nodeHead);

/*
 * Display a graph on the standard output
 * Params:
 * - Graph *self: the graph you wish to view
 * Return:
 * - void
 */
void view_graph(const struct Graph *self);

/*
 * Save a graph in a file
 * Params:
 * - Graph self: the graph you wish to save
 * - char * filename: the filename in which to save the file. ':' for stdout
 * Return:
 * - void
 */
void save_graph(const struct Graph *self, const char *filename);

/*
 * Get the number of nodes in a graph
 * Params:
 * - Graph *self: the graph from which you wish to get the number of nodes
 * Return:
 * - size_t n the number of nodes in the graph
 */
size_t get_node_number(const struct Graph *self);

/*
 * Breadth first search
 * Params:
 * - Graph *self: the graph you wish to apply BFS on
 * - int source: the source node
 * - int sink: the sink node
 * - int *parent: array containing the parents of the path found by BFS
 * - int **flow: current flow values
 * Return:
 * - true if a path exists between source and sink, false otherwise
 */
bool breadth_first_search (const struct Graph *self, int source, int sink, int *parent, int **flow);

/*
 * Depth first search
 * Params:
 * - Graph *self: the graph you wish to apply DFS on
 * - int source: the source node
 * - int sink: the sink node
 * - int *parent: array containing the parents of the path found by DFS
 * - int **flow: current flow values
 * Return:
 * - true if a path exists between source and sink, false otherwise
 */
bool depth_first_search(const struct Graph *self, int source, int sink, int *parent, int **flow);

/*
 * Shortest path Floyd-Warshall
 * Params:
 * - Graph *self: the graph you wish to apply Floyd-Warshall on
 * - int source: the source node
 * - int sink: the sink node
 * - int *parent: array containing the parents of the path found by Floyd-Warshall
 * - int **flow: current flow values
 * Return:
 * - true if a path exists between source and sink, false otherwise
 */
bool floyd_warshall(const struct Graph *self, int source, int sink, int *parent, int **flow);

/*
 * Get the maximum flow of a graph from a source node to a sink node using the Ford Fulkerson algorithm
 * Params:
 * - Graph *self: the graph from which you wish to get the maximum flow
 * - int source: the source node
 * - int sink: the sink node
 * - int function: the function used to find a path
 * Return:
 * - int maxFlow: the maximum flow of the graph
 */
int ford_fulkerson(const struct Graph *self, int source, int sink, int function);

#ifdef __cplusplus
}
#endif

#endif // GRAPH_H
