/*
	PW2 - Graph Library Representation by Adjacency Lists
	graph.h
	Thibault BERTIN - Timothée LAURENT
	Master 1 CMI Informatique - TP1A
*/
#define _GNU_SOURCE
#include "../INCLUDE/graph.h"

/*
 * Create an empty graph"
 * Params:
 * - Graph *self: the graph you wish to create
 * - bool isDirected: true if the graph is directed
 * - int nbMaxNodes: the maximum number of nodes the graph can have
 * Return:
 * - void
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
 * Params:
 * - Graph *self: the graph you wish to destroy
 * Return:
 * - void
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
}

/*
 * Load a graph from a file
 * Params:
 * - Graph *self: the graph structure in which to load the saved graph
 * - char *filename: the file from which you wish to load a graph
 * Return:
 * - int 0: success, -1: error
 */
int load_graph(struct Graph *self, const char *filename) {
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
							return -1;
						}
					}
					nbMaxNodes = atoi(line);
					if (nbMaxNodes < 1) {
						fprintf(stderr, "Error: in %s on line %d: the max number of nodes can't be null or negative\n", filename, lineCount);
						return -1;					
					}
					break;
				case 2: // On second instruction, we get the boolean that says whether the graph is directed or not
					switch (line[0]) {
						case 'y': isDirected = true;break;
						case 'n': isDirected = false;break;
						default:
							fprintf(stderr, "Error: in %s on line %d: expected 'y' or 'n', found '%c'\n", filename, lineCount, line[0]);
							return -1;			
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
						return -1;
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
							return -1;
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
							return -1;
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
	return 0;
}

/*
 * Add a node to a graph
 * Params:
 * - Graph *self: the graph in which you wish to add a node 
 *
 * Return:
 * - int 0: success, -1: error
 */
int add_node(struct Graph *self, int node) {
	assert(self);
	
	// Verifies that the node is not already in the graph and that the node's number is correct
	if (node > self->nbMaxNodes) {
		fprintf(stderr, "Error: Can't add more than %d nodes to this graph. Please choose a value <= %d\n", self->nbMaxNodes, self->nbMaxNodes);
		return -1;
	}
	if (node < 1) {
		fprintf(stderr, "Error: Can't add this node to this graph. Please choose a value >= 1\n");
		return -1;
	}
	if (self->adjList[node-1] != NULL) {
		fprintf(stderr, "Error: This node already exists in the graph. Please choose another value\n");
		return -1;
	}
	struct Neighbour *new = malloc(sizeof(struct Neighbour));
	create_neighbour(new, -1, 0);
	self->adjList[node-1] = new;
	return 0;
}

/*
 * Remove a node from a graph
 * Params:
 * - Graph *self: the graph from which you wish to remove a node
 * - int node: the node you wish to remove
 * Return:
 * - int 0: success, -1: error
 */
int remove_node(struct Graph *self, int node) {
	assert(self);
	
	// Verifies that the node is in the graph and that the node's number is correct
	if (node > self->nbMaxNodes || node < 1 || self->adjList[node-1] == NULL) {
		fprintf(stderr, "Error: This node does not exist in the graph\n");
		return -1;
	}
	
	destroy_neighbour(&self->adjList[node-1]);
	
	for (int i = 0; i < self->nbMaxNodes; i++) {
		if (self->adjList[i]) {
			struct Neighbour *curr = self->adjList[i];
			while (curr != NULL) {
				if (curr->neighbour == node) {
					remove_neighbour(curr);
				}
				curr = curr->nextNeighbour;
			}
		}
	}
	
	return 0;
}

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
int add_edge(struct Graph *self, int nodeTail, int nodeHead, int weight, bool symmetric) {
	assert(self);
	
	// Both endpoints need to be nodes in the graph and the edge must not already exist in the graph
	if (self->adjList[nodeTail-1] == NULL || self->adjList[nodeHead-1] == NULL) {
		fprintf(stderr, "Error: The %s node doesn't exist in the graph. Please choose another node.\n", self->adjList[nodeTail-1] ? "head" : "tail");
		return -1;
	}
	
	struct Neighbour *curr = self->adjList[nodeTail - 1];
	while (curr != NULL) {
		if (curr->neighbour == nodeHead) {
			fprintf(stderr, "Error: This edge already exists in the graph. Please choose another value.\n");
			return -1;
		}
		curr = curr->nextNeighbour;
	}
	if (nodeTail != nodeHead && symmetric) {
		struct Neighbour *curr = self->adjList[nodeHead - 1];
		while (curr != NULL) {
			if (curr->neighbour == nodeTail) {
				fprintf(stderr, "Error: The symmetric edge already exists in the graph. Try removing it or trying again without adding the symmetric edge\n");
				return -1;
			}
			curr = curr->nextNeighbour;
		}
		add_neighbour(&self->adjList[nodeHead-1], nodeTail, weight);
	}
	add_neighbour(&self->adjList[nodeTail-1], nodeHead, weight);
	if (nodeTail == nodeHead && symmetric && !self->isDirected) {
		fprintf(stderr, "Warning: Symmetric was not created because this is a self-loop\n");	
	}
	return 0;
}

/*
 * Remove an edge from a graph
 * Params:
 * - Graph *self: the graph from which you wish to remove an edge
 * - int nodeTail: the node from which the edge starts
 * - int nodeHead: the node to which the edge arrives
 * Return:
 * - int 0: success, -1: error
 */
int remove_edge(struct Graph *self, int nodeTail, int nodeHead) {
	assert(self);
	
	// Verifies that both its endpoints are nodes of the graph
	if (self->adjList[nodeTail-1] == NULL || self->adjList[nodeHead-1] == NULL) {
		fprintf(stderr, "Error: The %s node doesn't exist in the graph. Please choose another node\n", self->adjList[nodeTail-1] ? "head" : "tail");
		return -1;
	}
	
	struct Neighbour *curr = self->adjList[nodeTail - 1];
	while (curr) {
		if (curr->neighbour == nodeHead) {
			remove_neighbour(curr);
		}
		curr = curr->nextNeighbour;
	}
	
	if (!self->isDirected) {
		curr = self->adjList[nodeHead - 1];
		while (curr) {
			if (curr->neighbour == nodeTail) {
				remove_neighbour(curr);
			}
			curr = curr->nextNeighbour;
		}
	}
	return 0;
}

/*
 * Display a graph on the standard output
 * Params:
 * - Graph *self: the graph you wish to view
 * Return:
 * - void
 */
void view_graph(const struct Graph *self) {
	save_graph(self, ":");
}

/*
 * Save a graph in a file
 * Params:
 * - Graph *self: the graph you wish to save
 * - char *filename : the filename in which to save the file. ':' for stdout
 * Return:
 * - void
 */
void save_graph(const struct Graph *self, const char *filename) {
	assert(self);

	FILE *output = stdout;
	// If filename starts with ':' we consider the output to be stdout. (Useful because then we can use this function for view_graph);
	if (filename[0] != ':') {
		if (access(filename, F_OK) != -1) {
	    		if ((output = fopen(filename, "w")) < 0) {
				fprintf(stderr, "Error: could not open %s\n", filename);
			}
		} else {
			char buffer[128];
			strcpy(buffer, "SAVES/");
			strcat(buffer, filename);		
			if ((output = fopen(buffer, "w")) < 0) {
				fprintf(stderr, "Error: could not open %s\n", filename);
			}
		}
	}
	
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

/*
 * Get the number of nodes in a graph
 * Params:
 * - Graph *self: Graph from which you wish to get the number of nodes
 * Return:
 * - int N the number of nodes in the graph
 */
size_t get_node_number(const struct Graph *self) {
	size_t n = 0;
	for (int i = 0; i < self->nbMaxNodes; i++) {
		if (self->adjList[i]) {
			n++;
		}
	}
	return n;
}

/*
 * Breadth first search
 * Params:
 * - Graph *self: the graph you wish to apply BFS on
 * - int source: the source node
 * - int sink: the sink node
 * - int *parent: array containing the parents of the path found by BFS
 * - int **flow: current flow values
 * Return:
 * - true if a path exists between source an sink, false otherwise
 */
bool breadth_first_search (const struct Graph *self, int source, int sink, int *parent, int **flow) {
	int nbMaxNodes = self->nbMaxNodes;
	
	int *queue = malloc(sizeof(int) * (nbMaxNodes + 2));
	int head = 0;
	int tail = 0;
	
	int *color = malloc(sizeof(int) * nbMaxNodes);
	for (int u = 0; u < nbMaxNodes; u++) {
		color[u] = WHITE;
		parent[u] = -1;
	}
	parent[nbMaxNodes] = -1;
	
	color[source-1] = GRAY;
	parent[source] = -1;
	
	queue[tail] = source;
	tail++;
	
	while (head != tail) {
		int u = queue[head];
		head++;
		
		// Search all adjacent white nodes v. If the capacity from u to v in the residual network is positive, enqueue v
		struct Neighbour *curr = self->adjList[u-1];
		while (curr) {
			if (curr->neighbour != -1) {
				int v = curr->neighbour;
				if (color[v-1] == WHITE && (curr->weight - flow[u-1][v-1]) > 0) {
					color[v-1] = GRAY;
					parent[v] = u;
					
					queue[tail] = v;
					tail++;
				
				}
			}
			curr = curr->nextNeighbour;
		}
		color[u-1] = BLACK;
	}
	
	free(queue);
	
	if (parent[sink] != -1) {
		free(color);
		return true;
	}
	free(color);
	return false;
}

/*
 * DFS visit : Recursive function for depth first search
 */
void dfs_visit(const struct Graph *self, int currentNode, int *color, int *parent, int **flow) {
	color[currentNode-1] = GRAY;
	struct Neighbour *curr = self->adjList[currentNode-1];
	while (curr) {
		if (curr->neighbour != -1) {
			int v = curr->neighbour;
			if (color[v-1] == WHITE && (curr->weight - flow[currentNode-1][v-1]) > 0) {
				parent[v] = currentNode;
				dfs_visit(self, v, color, parent, flow);
			}
		}
		curr = curr->nextNeighbour;
	}
	color[currentNode-1] = BLACK;
}

/*
 * Depth first search
 * Params:
 * - Graph *self: the graph you wish to apply DFS on
 * - int source: the source node
 * - int sink: the sink node
 * - int *parent: array containing the parents of the path found by DFS
 * - int **flow: current flow values
 * Return:
 * - true if a path exists between source an sink, false otherwise
 */
bool depth_first_search(const struct Graph *self, int source, int sink, int *parent, int **flow) {
	int nbMaxNodes = self->nbMaxNodes;
	
	int *color = malloc(sizeof(int) * nbMaxNodes);
	for (int u = 0; u < nbMaxNodes; u++) {
		color[u] = WHITE;
		parent[u] = -1;
	}
	parent[self->nbMaxNodes] = -1;

	for (int u = 1; u < nbMaxNodes+1; u++) {
		if (color[u-1] == WHITE) {
			dfs_visit(self, u, color, parent, flow);
		}
	}
	
	if (parent[sink] != -1) {
		free(color);
		return true;
	}
	free(color);
	return false;
}

/*
 * Returns minimum of x and y
 * Params:
 * - int x
 * - int y
 * Return:
 * - int z the minimum value between x and y
 */
int min(int x, int y) {
    return x < y ? x : y;
}

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
int ford_fulkerson(const struct Graph *self, int source, int sink, int function) {
	int nbMaxNodes = self->nbMaxNodes;
	
	int *parent = malloc(sizeof(int) * (nbMaxNodes + 1));
	
	int maxFlow = 0;
	
	// Initialize empty flow
	int **flow = malloc(sizeof(int *) * nbMaxNodes);
	for (int i = 0; i < nbMaxNodes; i++) {
		flow[i] = malloc(sizeof(int) * nbMaxNodes);
	}
	for (int i = 0; i < nbMaxNodes; i++) {
		for (int j = 0; j < nbMaxNodes; j++) {
			flow[i][j] = 0;
		}
	}
	
	// To manage the different function which find a path
	bool isThereAPath = false;
	switch (function) {
		case 1: // BFS
			isThereAPath = breadth_first_search(self, source, sink, parent, flow);
			break;
		case 2: // DFS
			isThereAPath = depth_first_search(self, source, sink, parent, flow);
			break;
		case 3: // Random path
			break;
		default: // Shortest path
			isThereAPath = breadth_first_search(self, source, sink, parent, flow);
	}
	
	for (int i = 0; i < (nbMaxNodes+1); i++) {
		printf("parent[%d] : %d\n", i, parent[i]);
	}
    
	// While there exists an augmenting path, increment the flow along this path
	while (isThereAPath) {
		// Determine the amount by which we can increment the flow
		int increment = INT_MAX;
		for (int i = sink; parent[i] >= 0; i = parent[i]) {
			struct Neighbour *curr = self->adjList[parent[i] - 1];
			while (curr) {
				if (curr->neighbour == i) {
					increment = min(increment, (curr->weight - flow[parent[i]-1][i-1]));
					printf("increment : %d\n", increment);
				}
				curr = curr->nextNeighbour;
			}
		}
		
		// Increment the flow
		for (int i = sink; parent[i] >= 0; i = parent[i]) {
			flow[parent[i]-1][i-1] += increment;
			flow[i-1][parent[i]-1] -= increment;
		}
		maxFlow += increment;
		
		// To find the next path
		switch (function) {
			case 1: // BFS
				isThereAPath = breadth_first_search(self, source, sink, parent, flow);
				break;
			case 2: // DFS
				isThereAPath = depth_first_search(self, source, sink, parent, flow);
				break;
			case 3: // Random path
				break;
			default: // Shortest path
				isThereAPath = breadth_first_search(self, source, sink, parent, flow);
		}
		
		for (int i = 0; i < (nbMaxNodes+1); i++) {
			printf("parent[%d] : %d\n", i, parent[i]);
		}
	}
	
	free(parent);
	for (int i = 0; i < nbMaxNodes; i++) {
		free(flow[i]);
	}
	free(flow);
	
	// No augmenting path anymore
	return maxFlow;
}
