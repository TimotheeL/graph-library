/*
	PW2 - Graph Library Representation by Adjacency Lists
	Thibault BERTIN - Timothée LAURENT
	Master 1 CMI Informatique - TP1A
*/
#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <assert.h>

#include "list.h"
#ifdef __cplusplus
extern "C" {
#endif

struct Graph {
	bool isDirected;
	int nbMaxNodes;
	struct Neighbour *adjList;
};

/*
 * Create an empty graph
 */
void create_graph(struct Graph *self, bool isDirected, int nbMaxNodes);

/*
 * Destroy a graph
 */
void destroy_graph(struct Graph *self);

/*
 * Load graph from file
 */ 
void load_graph(const char *filename);

/*
 * Add a node to a graph
 */
void add_node(struct Graph *self, int nbNode);

/*
 * Remove a node from a graph
 */
void remove_node(struct Graph *self, int node);

/*
 * Add an edge to a graph
 */
void add_edge(struct Graph *self);

/*
 * Remove an edge from the graph
 */
void remove_edge(struct Graph *self, int nodeTail, int nodeHead);

/*
 * Display the graph on the standard output
 */
void view_graph(const struct Graph *self);

/*
 * Save the graph in a file
 */
void save_graph(const struct Graph *self, const char *filename);

/*
 * Exit the program
 */
void quit();

#ifdef __cplusplus
}
#endif

#endif // GRAPH_H
