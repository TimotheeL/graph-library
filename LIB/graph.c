#include "../INCLUDE/graph.h"

/*
 * Create an empty graph
 */
void create_graph(struct Graph *self, int nbMaxNodes) {
	self->nbMaxNodes = nbMaxNodes;
	self->adjList = NULL;
	self->isDirected = false;
}

/*
 * Destroy a graph
 */
void destroy_graph(struct Graph *self) {

}

/*
 * Load graph from file
 */ 
void load_graph() {

}

/*
 * Add a node to a graph
 */
void add_node() {

}

/*
 * Remove a node from a graph
 */
void remove_node() {

}

/*
 * Add an edge to a graph
 */
void add_edge() {

}

/*
 * Remove an edge from the graph
 */
void remove_edge() {

}

/*
 * Display the graph on the standard output
 */
void view_graph(const struct Graph *self) {
	printf("# maximum number of nodes\n%d\n# directed", self->nbMaxNodes);
	printf(self->isDirected ? "y" : "n"); 
	printf("\n# node: neighbours");
}

/*
 * Save the graph in a file
 */
void save_graph() {

}

/*
 * Exit the program
 */
void quit() {

}
