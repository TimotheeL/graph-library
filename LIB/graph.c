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
	assert(self);
	
	self->isDirected = isDirected;
	self->nbMaxNodes = nbMaxNodes;
	self->adjList = malloc(nbMaxNodes * sizeof(struct Neighbour));
}

/*
 * Destroy a graph
 */
void destroy_graph(struct Graph *self) {
	assert(self);
	for (int nbNodes = 0; nbNodes < self->nbMaxNodes; nbNodes++) {
		remove_node(self, self->adjList[nbNodes].neighbour);
	}

	free(self->adjList);
	free(self);
}

/*
 * Load graph from file
 */ 
void load_graph(struct Graph *self, const char *filename) {
	/*FILE* f = fopen(filename, "r");
	if (f == NULL) {
		fprintf(stderr, "Error: couldn't open file \"%s\"", filename);
		exit(EXIT_FAILURE);
	}
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	int instructionCount = 0;
	int lineCount = 0;
	int nbMaxNodes;
	bool isDirected;
	
	while ((read = getline(&line, &len, fp)) != -1) {
		lineCount++;
		if (line[0] != "#")
			instructionCount++;
		if (instructionCount == 1) {
			size_t n = strlen(line);
			for (int i = 0; i < n; i++) {
				if (!isdigit(line[i])) {
					fprintf(stderr, "");
				}
			}
		}
	}
	fclose(f);*/
}

/*
 * Add a node to a graph
 */
void add_node(struct Graph *self, int nbNode) {
	assert(self);
	if (nbNode > self->nbMaxNodes) {
		fprintf(stderr, "Error: Can't add more than %d nodes to this graph. Please choose a value <= %d", self->nbMaxNodes, self->nbMaxNodes);
		exit(EXIT_FAILURE);
	}
	if (nbNode < 1) {
		fprintf(stderr, "Error: Can't add this node to this graph. Please choose a value >= 1");
		exit(EXIT_FAILURE);
	}
	if (&self->adjList[nbNode-1] != NULL) {
		fprintf(stderr, "Error: This node already exists in the graph. Please choose another value");
		exit(EXIT_FAILURE);
	}
	
	add_neighbour(&self->adjList[nbNode-1], -1, 0);
}

/*
 * Remove a node from a graph
 */
void remove_node(struct Graph *self, int node) {
	assert(self);
	
	for (int nbNodes = 0; nbNodes < self->nbMaxNodes; nbNodes++) {
		struct Neighbour *curr = &self->adjList[nbNodes];
		if ((nbNodes + 1) == node) {
			destroy_neighbour(curr);
		}
		else {
			while (curr != NULL) {
				if (curr->neighbour == node) {
					remove_neighbour(curr);
					break;
				}
				curr = curr->nextNeighbour;
			}
		}
	}
}

/*
 * Add an edge to a graph
 */
void add_edge(struct Graph *self) {
	assert(self);
}

/*
 * Remove an edge from the graph
 */
void remove_edge(struct Graph *self, int nodeTail, int nodeHead) {
	assert(self);
	
	struct Neighbour *curr = &self->adjList[nodeTail - 1];
	while (curr != NULL) {
		if (curr->neighbour == nodeHead) {
			remove_neighbour(curr);
			break;
		}
		curr = curr->nextNeighbour;
	}

	if (self->isDirected) {
		curr = &self->adjList[nodeHead - 1];
		while (curr != NULL) {
			if (curr->neighbour == nodeTail) {
				remove_neighbour(curr);
				break;
			}
			curr = curr->nextNeighbour;
		}
	}
}

/*
 * Display the graph on the standard output
 */
void view_graph(const struct Graph *self) {
	assert(self);
	save_graph(self, ":");
}

/*
 * Save the graph in a file
 */
void save_graph(const struct Graph *self, const char *filename) {
	assert(self);
	FILE *output = (filename[0] == ':' ? stdout : fopen(filename, "w"));
	fprintf(output, "# maximum number of nodes\n%d\n# directed", self->nbMaxNodes);
	fprintf(output, self->isDirected ? "y" : "n"); 
	fprintf(output, "\n# node: neighbours\n");
	for (int i = 0; i < self->nbMaxNodes; i++) {
		if (&self->adjList[i] != NULL) {
			fprintf(output, "%d: ", i);
			struct Neighbour *curr = &self->adjList[i];
			while (curr) {
				fprintf(output, "(%d/%d)",curr->neighbour, curr->weight);
				fprintf(output, curr->nextNeighbour ? ", " : "\n");
				curr = curr->nextNeighbour;
			}
		}	
	}
	fclose(output);
}

/*
 * Exit the program
 */
void quit() {

}
