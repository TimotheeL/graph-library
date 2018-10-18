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
/*	FILE* f = fopen(filename, "r");
	if (f == NULL) {
		fprintf(stderr, "Error: couldn't open file \"%s\"\n", filename);
		exit(EXIT_FAILURE);
	}
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	int nbMaxNodes;
	bool isDirected;
	int lineCount = 0;
	int instructionCount = 0;	

	while ((read = getline(&line, &len, fp)) != -1) {
		lineCount++;
		if (line[0] != "#") {
			instructionCount++;
			if (instructionCount == 1) {
				for (int i = 0; i < read - 1; i++) {
					if (!isdigit(line[i])) {
						fprintf(stderr, "Error: in %s on line %d: expected digits, found \"%c\"\n", filename, lineCount, line[i]);
						exit(EXIT_FAILURE);
					}
				}
				nbMaxNodes = atoi(line);
			} else if (instructionCount == 2) {
				switch (line[0]) {
					case 'y': isDirected = true;break;
					case 'n': isDirected = false;break;
					default:
						fprintf(stderr, "Error: in %s on line %d: expected 'y' or 'n', found \"%c\" ", filename, lineCount, line[0]);
						exit(EXIT_FAILURE);				
				}
				if (read - 1 != 1) {
					fprintf(stderr, "Warning: in %s on line %d: expected 'y' or 'n', found multiple characters. Only the first character was used", filename, lineCount);
				}
			} else {
				char *part;
				int c = 0;
				int node;
				char *neighbours;
				part = strtok(line, ":");
				while (part != NULL) {
					switch (c) {
						case 0:node = atoi(part);break;
						case 1:neighbours = part;break;
						default:
							fprintf(stderr, "Error: in %s on line %d: wrong format. Expected: \"node: (neighbour/weight), ...\"", filename, lineCount);
							exit(EXIT_FAILURE);
					}
					c++;
				}
				if (c == 0) {
					fprintf(stderr, "Error: in %s on line %d: wrong format. Expected: \"node: (neighbour/weight), ...\"", filename, lineCount);
					exit(EXIT_FAILURE);
				}
				part = strtok(neighbour, ", ");
				while (part != NULL) {
					
				}
			}
		}
	}
	free(line);
	fclose(f);*/
}

/*
 * Add a node to a graph
 */
void add_node(struct Graph *self, int nbNode) {
	assert(self);
	
	// Verifies that the node is not already in the graph and that the node's number is correct
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
	
	// Verifies that the node is in the graph and that the node's number is correct
	if (node > self->nbMaxNodes) {
		fprintf(stderr, "Error: This node isn't in the graph");
		exit(EXIT_FAILURE);
	}
	if (node < 1) {
		fprintf(stderr, "Error: This node isn't in the graph");
		exit(EXIT_FAILURE);
	}
	if (&self->adjList[node-1] == NULL) {
		fprintf(stderr, "Error: This node didn't exists in the graph. Please choose another value");
		exit(EXIT_FAILURE);
	}
	
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
void add_edge(struct Graph *self, int nodeTail, int nodeHead, int weight, bool symmetric) {
	assert(self);
	
	// Verifies that both its endpoints are nodes of the graph and that the edge is not already in the graph
	if (&self->adjList[nodeTail-1] == NULL) {
		fprintf(stderr, "Error: The tail node doesn't exist in the graph. Please choose another node");
		exit(EXIT_FAILURE);
	}
	if (&self->adjList[nodeHead-1] == NULL) {
		fprintf(stderr, "Error: The head node doesn't exist in the graph. Please choose another node");
		exit(EXIT_FAILURE);
	}
	
	struct Neighbour *curr = &self->adjList[nodeTail - 1];
	while (curr != NULL) {
		if (curr->neighbour == nodeHead) {
			fprintf(stderr, "Error: This edge already exists in the graph. Please choose another value");
			exit(EXIT_FAILURE);
		}
		curr = curr->nextNeighbour;
	}
	add_neighbour(&self->adjList[nodeTail-1], nodeHead, weight);

	if (symmetric) {
		struct Neighbour *curr = &self->adjList[nodeHead - 1];
		while (curr != NULL) {
			if (curr->neighbour == nodeTail) {
				fprintf(stderr, "Error: This edge already exists in the graph. Please choose another value");
				exit(EXIT_FAILURE);
			}
			curr = curr->nextNeighbour;
		}
		add_neighbour(&self->adjList[nodeHead-1], nodeTail, weight);
	}
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
