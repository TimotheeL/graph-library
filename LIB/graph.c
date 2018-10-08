/*
	PW2 - Graph Library Representation by Adjacency Lists
	Thibault BERTIN - Timothée LAURENT
	Master 1 CMI Informatique - TP1A
*/
#include "../INCLUDE/graph.h"

/*
 * Create an empty graph
 */
void create_graph(struct Graph *self, bool isDirected, int nbMaxNodes) {
	self->isDirected = isDirected;
	self->nbMaxNodes = nbMaxNodes;
	self->adjList = malloc(nbMaxNodes * sizeof(struct Neighbour));
}

/*
 * Destroy a graph
 */
void destroy_graph(struct Graph *self) {
	for (int nbNodes = 0; nbNodes < nbMaxNodes; nbNodes++) {
		remove_node(self->adjList[nbNodes]);
	}
	
	free(adjList);
	free(self);
}

/*
 * Load graph from file
 */ 
void load_graph() {

}

/*
 * Add a node to a graph
 */
void add_node(struct Graph *self) {

}

/*
 * Remove a node from a graph
 */
void remove_node(struct Graph *self, int node) {
	for (int nbNodes = 0; nbNodes < self->nbMaxNodes; nbNodes++) {
		struct Neighbour *curr = self->adjList[nbNodes];
		if ((nbNodes+1) == node) {
			destroy_neighbour(curr);
		}
		else {
			while (curr != NULL) {
				if (curr->neighbour == node) {
					remove_neighbour(curr);
				}
				curr = curr->nextNeighbour;
			}
		}
	}
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
	printf("\n# node: neighbours\n");
	for (int i = 0; i < self->nbMaxNodes; i++) {
		if (self->adjList[i]) {
			printf("%d: ",i);
			struct Neighbour *curr = self->adjList[i];
			while (curr) {
				printf("(%d/%d)",curr->neighbour, curr->weight);
				curr = curr->next;
			}
		}	
	}
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
