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
	self->adjList = malloc(sizeof(struct Neighbour) * nbMaxNodes);
	for (int i = 0; i < nbMaxNodes; i++) {
		self->adjList[i] = NULL;
	}
}	

/*
 * Destroy a graph
 */
void destroy_graph(struct Graph *self) {
	assert(self);
	for (int i = 0; i < self->nbMaxNodes; i++) {
		if (self->adjList[i]) {
			remove_node(self, i+1);
		}
	}

	free(self->adjList);
	self->adjList = NULL;
	free(self);
	self = NULL;
}

/*
 * Load graph from file
 */ 
void load_graph(struct Graph *self, const char *filename) {
	FILE* f = fopen(filename, "r");
	if (!f) {
		fprintf(stderr, "Error: couldn't open file \"%s\"\n", filename);
		exit(EXIT_FAILURE);
	}
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	int nbMaxNodes = -1;
	bool isDirected = false;
	int lineCount = 0;
	int instructionCount = 0;
	char *part = NULL;
	int c = 0;
	int node = -1;
	int weight = -1;
	int neigh = -1;
	char *neighbours = NULL;
	// Read the file for the first time to add all the nodes in the graph
	while ((read = getline(&line, &len, f)) != -1) {
		// Count the number of lines for error display purposes	
		lineCount++;
		// Ignore lines starting with '#' (we consider they are comments)
		if (line[0] != '#' && line[0] != '\n') {
			// Count the number of instructions to determine what we are expected to find
			instructionCount++;
			switch(instructionCount) {
				case 1: // On first instruction, we get the number max of nodes
					for (int i = 0; i < read - 1; i++) {
						if (!isdigit(line[i])) {
							fprintf(stderr, "Error: in %s on line %d: expected digits, found '%c'\n", filename, lineCount, line[i]);
							return;
						}
					}
					nbMaxNodes = atoi(line);
					if (nbMaxNodes < 1) {
						fprintf(stderr, "Error: in %s on line %d: the max number of nodes can't be null or negative\n", filename, lineCount);
						return;					
					}
					break;
				case 2: // On second instruction, we get the boolean that says whether the graph is directed or not
					switch (line[0]) {
						case 'y': isDirected = true;break;
						case 'n': isDirected = false;break;
						default:
							fprintf(stderr, "Error: in %s on line %d: expected 'y' or 'n', found '%c'\n", filename, lineCount, line[0]);
							return;			
					}
					if (read - 1 != 1) {
						fprintf(stderr, "Warning: in %s on line %d: expected 'y' or 'n', found multiple characters. Only the first character was used\n", filename, lineCount);
					}
					create_graph(self, isDirected, nbMaxNodes);break;
				default: // We add the nodes to the graph
					part = strtok(line, ":");
					node = atoi(part);
					if (node < 1) {
						fprintf(stderr, "Error: in %s on line %d: The node, neighbour and weight values must be positive integers\n", filename, lineCount);
						return;
					}				
					add_node(self, node);
			}
		}
	}
	if (instructionCount < 2) {
		fprintf(stderr, "Warning: in %s: instruction missing. Expected 'y' or 'n', found nothing. Your graph will automatically be created as an undirected graph\n", filename);
	}
	lineCount = 0;
	instructionCount = 0;
	free(line);
	line = NULL;
	rewind(f);
	// Read the file line by line
	while ((read = getline(&line, &len, f)) != -1) {	
		lineCount++;
		if (line[0] != '#' && line[0] != '\n') {
			instructionCount++; 
			if (instructionCount > 2) {
				// We only consider the lines representing the adjacency list here
				// First we split each line in 2 with ':' as a separator
				part = strtok(line, ":");
				while (part != NULL) {
					switch (c) {
						case 0:node = atoi(part);break;
						case 1:neighbours = part;break;
						default:
							fprintf(stderr, "Error: in %s on line %d: wrong format. Expected: \"node: (neighbour/weight), ...\"\n", filename, lineCount);
							return;
					}
					c++;
					part = strtok(NULL, ":");
				}
				c = 0;
				// Now we only consider the right part of each line
				part = strtok(neighbours, ", (/)");
				while (part != NULL) {
					if (c%2 == 0) {
						neigh = atoi(part);
					} else {
						weight = atoi(part);
						if (neigh < 0 || weight < 0) {
							fprintf(stderr, "Error: in %s on line %d: The node, neighbour and weight values must be positive integers\n", filename, lineCount);
							return;
						}
						add_edge(self, node, neigh, weight, false);
						neigh = -1;
						weight = -1;
					}
					c++;
					part = strtok(NULL, ", (/)");
				}
				c=0;
			}
		}
	}
	free(line);
	line = NULL;
	fclose(f);
}

/*
 * Add a node to a graph
 */
void add_node(struct Graph *self, int node) {
	assert(self);
	
	// Verifies that the node is not already in the graph and that the node's number is correct
	if (node > self->nbMaxNodes) {
		fprintf(stderr, "Error: Can't add more than %d nodes to this graph. Please choose a value <= %d\n", self->nbMaxNodes, self->nbMaxNodes);
		return;
	}
	if (node < 1) {
		fprintf(stderr, "Error: Can't add this node to this graph. Please choose a value >= 1\n");
		return;
	}
	if (self->adjList[node-1] != NULL) {
		fprintf(stderr, "Error: This node already exists in the graph. Please choose another value\n");
		return;
	}
	struct Neighbour *new = malloc(sizeof(struct Neighbour));
	create_neighbour(new, -1, 0);
	self->adjList[node-1] = new;
}

/*
 * Remove a node from a graph
 */
void remove_node(struct Graph *self, int node) {
	assert(self);
	
	// Verifies that the node is in the graph and that the node's number is correct
	if (node > self->nbMaxNodes || node < 1 || self->adjList[node-1] == NULL) {
		fprintf(stderr, "Error: This node does not exist in the graph\n");
		return;
	}
	
	destroy_neighbour(&self->adjList[node-1]);
}

/*
 * Add an edge to a graph
 */
void add_edge(struct Graph *self, int nodeTail, int nodeHead, int weight, bool symmetric) {
	assert(self);
	
	// Both endpoints need to be nodes in the graph and the edge must not already exist in the graph
	if (self->adjList[nodeTail-1] == NULL || self->adjList[nodeHead-1] == NULL) {
		fprintf(stderr, "Error: The %s node doesn't exist in the graph. Please choose another node.\n", self->adjList[nodeTail-1] ? "head" : "tail");
		return;
	}
	
	struct Neighbour *curr = self->adjList[nodeTail - 1];
	while (curr != NULL) {
		if (curr->neighbour == nodeHead) {
			fprintf(stderr, "Error: This edge already exists in the graph. Please choose another value.\n");
			return;
		}
		curr = curr->nextNeighbour;
	}
	if (nodeTail != nodeHead && symmetric) {
		struct Neighbour *curr = self->adjList[nodeHead - 1];
		while (curr != NULL) {
			if (curr->neighbour == nodeTail) {
				fprintf(stderr, "Error: The symmetric edge already exists in the graph. Try removing it or trying again without adding the symmetric edge\n");
				return;
			}
			curr = curr->nextNeighbour;
		}
		add_neighbour(&self->adjList[nodeHead-1], nodeTail, weight);
	}
	add_neighbour(&self->adjList[nodeTail-1], nodeHead, weight);
	if (nodeTail == nodeHead && symmetric && !self->isDirected) {
		fprintf(stderr, "Warning: Symmetric was not created because this is a self-loop\n");	
	}
}

/*
 * Remove an edge from the graph
 */
void remove_edge(struct Graph *self, int nodeTail, int nodeHead) {
	assert(self);
	
	// Verifies that both its endpoints are nodes of the graph
	if (self->adjList[nodeTail-1] == NULL || self->adjList[nodeHead-1] == NULL) {
		fprintf(stderr, "Error: The %s node doesn't exist in the graph. Please choose another node\n", self->adjList[nodeTail-1] ? "head" : "tail");
		return;
	}
	
	struct Neighbour *curr = self->adjList[nodeTail - 1];
	while (curr) {
		if (curr->neighbour == nodeHead) {
			remove_neighbour(&curr);
		}
		curr = curr->nextNeighbour;
	}
	
	if (self->isDirected) {
		curr = self->adjList[nodeHead - 1];
		while (curr) {
			if (curr->neighbour == nodeTail) {
				remove_neighbour(&curr);
			}
			curr = curr->nextNeighbour;
		}
	}

}

/*
 * Display the graph on the standard output
 */
void view_graph(const struct Graph *self) {
	save_graph(self, ":");
}

/*
 * Save the graph in a file
 */
void save_graph(const struct Graph *self, const char *filename) {
	assert(self);
	
	FILE *output = (filename[0] == ':' ? stdout : fopen(filename, "w"));
	fprintf(output, "# maximum number of nodes\n%d\n# directed\n", self->nbMaxNodes);
	fprintf(output, self->isDirected ? "y" : "n"); 
	fprintf(output, "\n# node: neighbours\n");
	for (int i = 0; i < self->nbMaxNodes; i++) {
		if (self->adjList[i] != NULL) {
			fprintf(output, "%d: ", i+1);
			struct Neighbour *curr = self->adjList[i];
			while (curr) {
				if (curr->neighbour != -1) {
					fprintf(output, "(%d/%d)", curr->neighbour, curr->weight);
					if (curr->nextNeighbour->neighbour != -1) fprintf(output, ", ");
				} else {
					fprintf(output, "\n");
				}
				curr = curr->nextNeighbour;
			}
		}
	}
	if (filename[0] != ':') fclose(output);
}
