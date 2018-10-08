#ifndef GRAPH_H
#define GRAPH_H

#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Create an empty graph
 */
void create_graph(struct graph *self);

/*
 * Destroy a graph
 */
void destroy_graph(struct graph *self);

/*
 * Load graph from file
 */ 
void load_graph();

/*
 * Add a node to a graph
 */
void add_node();

/*
 * Remove a node from a graph
 */
void remove_node();

/*
 * Add an edge to a graph
 */
void add_edge();

/*
 * Remove an edge from the graph
 */
void remove_edge();

/*
 * Exit the program
 */
void quit();

#ifdef __cplusplus
}
#endif

#endif // GRAPH_H
