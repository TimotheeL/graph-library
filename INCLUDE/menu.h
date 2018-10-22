/*
	PW2 - Graph Library Representation by Adjacency Lists
	menu.h
	Thibault BERTIN - Timothée LAURENT
	Master 1 CMI Informatique - TP1A
*/
#ifndef MENU_H
#define MENU_H


#include "graph.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Clear a buffer
 * Return:
 * - void
 */
void clear_buffer();

/* Read a string from stdin
 * Params:
 * - char *string: entry string
 * - int length: length of the string
 * Return:
 * - int 0: success, -1: error
 */
int read_string(char *string, int length);

/* Read a long from stdin
 * Return:
 * - long inputted
 */
long read_long();

/* Menu to create a graph
 * Params:
 * - Graph *graph: the graph to create
 * Return:
 * - void
 */
void menu_create_graph(struct Graph *graph);

/* Menu to load a graph
 * Params:
 * - Graph *graph: the graph to load
 * Return:
 * - void
 */
void menu_load_graph(struct Graph *graph);

/* Menu to add a node into a graph
 * Params:
 * - Graph *graph: the graph to which we want to add a node
 * Return:
 * - void
 */
void menu_add_node(struct Graph *graph);

/* Menu to add an edge into a graph
 * Params:
 * - Graph *graph: the graph to which we want to add an edge
 * Return:
 * - void
 */
void menu_add_edge(struct Graph *graph);

/* Menu to remove a node from a graph
 * Params:
 * - Graph *graph: the graph in which we want to remove a node
 * Return:
 * - void
 */
void menu_remove_node(struct Graph *graph);

/* Menu to remove an edge from a graph
 * Params:
 * - Graph *graph: the graph from which we want to remove an edge
 * Return:
 * - void
 */
void menu_remove_edge(struct Graph *graph);

/* Menu to view a graph
 * Params:
 * - Graph *graph: the graph to view
 * Return:
 * - void
 */
void menu_view_graph(struct Graph *graph);

/* Menu to save a graph
 * Params:
 * - Graph *graph: the graph to save
 * Return:
 * - void
 */
void menu_save_graph(struct Graph *graph);

/* Menu to quit the program
 * Params:
 * - Graph *graph: the graph created in the menu
 * Return:
 * - boolean: true if the user decides to quits, false otherwise
 */
bool menu_quit(struct Graph *graph);

#ifdef __cplusplus
}
#endif

#endif // MENU_H
