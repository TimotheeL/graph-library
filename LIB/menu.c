/*
	PW2 - Graph Library Representation by Adjacency Lists
	menu.c
	Thibault BERTIN - Timothée LAURENT
	Master 1 CMI Informatique - TP1A
*/
#include "../INCLUDE/menu.h"

/* Clear a buffer
 * Return:
 * - void
 */
void clear_buffer() {
	int c = 0;
	while (c != '\n' && c != EOF) {
		c = getchar();
	}
}
 
/* Read a string from stdin
 * Params:
 * - char *string: entry string
 * - int length: length of the string
 * Return:
 * - int 0: success, -1: error
 */
int read_string(char *string, int length) {
	char *positionEntry = NULL;
	
	// We read the text entered on the keyboard
	if (fgets(string, length, stdin) != NULL) { // Check entry error
		positionEntry = strchr(string, '\n'); // We search '\n' to replace it with '\0'
		
		if (positionEntry != NULL) {
			*positionEntry = '\0';
		}
		else {
			clear_buffer();
		}
		return 0;
	}
	else {
		clear_buffer();
		return -1;
	}
}

/* Read a long from stdin
 * Return:
 * - long inputted
 */
long read_long() {
	char TextNumber[1000] = {0};
	
	if (read_string(TextNumber, 1000) == 0) {
		return strtol(TextNumber, NULL, 10);
	}
	else {
		return -1; // We return -1 if the function can't convert to long
	}
}

/* Menu to create a graph
 * Params:
 * - Graph *graph: the graph to create
 * Return:
 * - void
 */
void menu_create_graph(struct Graph *graph) {
	if (graph->adjList == NULL) {
		long nbMaxNodes = 0;
		long tmpChoice = 0;
		do  {
			printf("Input a number for the maximum number of nodes your graph can have :\n");

			nbMaxNodes = read_long();
		} while (nbMaxNodes < 1);

	
		do  {
			printf("Is your graph directed ? 1 for yes, 0 for no : \n");
			tmpChoice = read_long();
		} while (tmpChoice != 0 && tmpChoice != 1);
		create_graph(graph, (tmpChoice == 1) ? true : false, nbMaxNodes);
		printf("Your graph was created with success!\n\n");
	} else {
		printf("/!\\ Please first destroy your current graph before creating a new one\n\n");
	}
	back_to_menu();
}

/* Menu to load a graph
 * Params:
 * - Graph *graph: the graph to load
 * Return:
 * - void
 */
void menu_load_graph(struct Graph *graph) {
	long delete = 1;
	if (graph->adjList != NULL) {
		// If a graph is already loaded or created we ask the user if he wants to replace it with a new one
		
		printf("/!\\ You already have a graph loaded. Do you wish to replace it with a new one?\n\t1) Yes\n\t2) No\n");
		do {
			delete = read_long();
		} while (delete < 1 || delete > 2);
		
		// If the user chooses to replace the graph with a new one.
		
		if (delete == 1) {
			destroy_graph(graph);
			graph = malloc (sizeof(struct Graph));
		}
	}
	if (delete == 1) {
		char *filename = malloc(1000 * sizeof(char));		
		do {
			printf("Write the name of the file (relative path from the root directory of this project) : \n");
		} while (read_string(filename, 1000));
		
		if (load_graph(graph, filename) == 0) printf("Your graph was loaded with success!\n\n");

		free(filename);
	}
	back_to_menu();
}

/* Menu to add a node into a graph
 * Params:
 * - Graph *graph: the graph to which we want to add a node
 * Return:
 * - void
 */
void menu_add_node(struct Graph *graph) {
	if (graph->adjList != NULL) {
		long nbNode = 0;
		do  {
			printf("Write the number of the node you want to insert : \n");
		
			nbNode = read_long();
		
			// Verifies that the node is not already in the graph and that the node's number is correct
			if (nbNode > graph->nbMaxNodes || nbNode < 1) {
				printf("Please choose a value between 1 and %d\n\n", graph->nbMaxNodes);
			}
			if (graph->adjList[nbNode-1] != NULL) {
				printf("This node already exists in the graph. Please choose another value\n\n");
			}
		} while ((nbNode > graph->nbMaxNodes) || (nbNode < 1) || (graph->adjList[nbNode-1] != NULL));
	
		if (add_node(graph, nbNode) == 0) printf("The node %ld was added to the graph with success!\n\n", nbNode);
	
	} else {
		printf("/!\\ Please create or load a graph first\n");
	}
	back_to_menu();
}

/* Menu to add an edge into a graph
 * Params:
 * - Graph *graph: the graph to which we want to add an edge
 * Return:
 * - void
 */
void menu_add_edge(struct Graph *graph) {
	long nodeTail = 0;
	long nodeHead = 0;
	long weight = 0;
	bool symmetric = false;
	bool alreadyCreated = false;
 
	if (graph->adjList == NULL) {
		printf("Please create or load a graph first\n\n");
		back_to_menu();
		return;	
	}

	if (get_node_number(graph) == 0) {
		printf("/!\\ There are no nodes in the graph. Please insert nodes before inserting edges\n\n");
		back_to_menu();
		return;
	}
	
	do {
		alreadyCreated = false;
		do  {
			printf("Write the number of the tail node : \n");
			
			nodeTail = read_long();
			
			// Verifies that the tail node is in the graph
			if (graph->adjList[nodeTail-1] == NULL) {
				printf("The tail node doesn't exist in the graph. Please choose another node\n\n");
			}
		} while (graph->adjList[nodeTail-1] == NULL);
		
		do  {
			printf("Write the number of the head node : \n");
			
			nodeHead = read_long();
			
			// Verifies that the head node is in the graph
			if (graph->adjList[nodeHead-1] == NULL) {
				printf("The head node doesn't exist in the graph. Please choose another node\n\n");
			}
		} while (graph->adjList[nodeHead-1] == NULL);
		
		if (graph->isDirected) {
			long tmpChoice = 0;
			do  {
				printf("Do you want to add the corresponding symetric edge ? 1 for yes, 0 for no : \n");
				
				tmpChoice = read_long();
			} while (tmpChoice != 0 && tmpChoice != 1);
			symmetric = (tmpChoice == 1) ? true : false;
		}
		else {
			symmetric = true;
		}
		
		struct Neighbour *curr = graph->adjList[nodeTail - 1];
		while (curr != NULL) {
			if (curr->neighbour == nodeHead) {
				printf("This edge already exists in the graph. Please choose another value\n\n");
				alreadyCreated = true;
			}
			curr = curr->nextNeighbour;
		}
		
		if (symmetric) {
			struct Neighbour *curr = graph->adjList[nodeHead - 1];
			while (curr != NULL) {
				if (curr->neighbour == nodeTail) {
					printf("This edge already exists in the graph. Please choose another value\n\n");
					alreadyCreated = true;
				}
				curr = curr->nextNeighbour;
			}
		}
	} while (alreadyCreated);
	
	do  {
		printf("Write the weight of the edge : \n");
		
		weight = read_long();
	} while (weight < 0);
	if (add_edge(graph, nodeTail, nodeHead, weight, symmetric)) printf("The edge %ld: (%ld/%ld) was added to the graph with success!\n\n", nodeTail, nodeHead, weight);
	back_to_menu();
}

/* Menu to remove a node from a graph
 * Params:
 * - Graph *graph: the graph in which we want to remove a node
 * Return:
 * - void
 */
void menu_remove_node(struct Graph *graph) {

	if (get_node_number(graph) == 0) {
		printf("/!\\ There are no nodes in the graph\n\n");
		back_to_menu();
		return;
	} 
	if (graph->adjList != NULL) {
		long node = 0;
		do  {
			printf("Write the number of the node you want to remove : \n");
		
			node = read_long();
		
			// Verifies that the node is in the graph and that the node's number is correct
			if (node > graph->nbMaxNodes || node < 1 || graph->adjList[node-1] == NULL) {
				printf("This node isn't in the graph\n\n");
			}
		} while ((node > graph->nbMaxNodes) || (node < 1) || (graph->adjList[node-1] == NULL));
	
		if (remove_node(graph, node)) printf("The node %ld was removed from the graph with success!\n\n", node);
	} else {
		printf("/!\\ Please create or load a graph first\n\n");
	}
	back_to_menu();
}

/* Menu to remove an edge from a graph
 * Params:
 * - Graph *graph: the graph from which we want to remove an edge
 * Return:
 * - void
 */
void menu_remove_edge(struct Graph *graph) {
	if (get_node_number(graph) == 0) {
		printf("/!\\ There are no edges in the graph\n\n");
		back_to_menu();
		return;	
	} 

	if (graph->adjList != NULL) {
		long nodeTail = 0;
		long nodeHead = 0;
		
		do {
			printf("Write the number of the tail node : \n");
			
			nodeTail = read_long();
			
			// Verifies that the tail node is in the graph
			if (graph->adjList[nodeTail-1] == NULL) {
				printf("The tail node doesn't exist in the graph. Please choose another node\n\n");
			}
		} while (graph->adjList[nodeTail-1] == NULL);
		
		do {
			printf("Write the number of the head node : \n");
			
			nodeHead = read_long();
			
			// Verifies that the head node is in the graph
			if (graph->adjList[nodeHead-1] == NULL) {
				printf("The head node doesn't exist in the graph. Please choose another node\n\n");
			}
		} while (graph->adjList[nodeHead-1] == NULL);
		
		if (remove_edge(graph, nodeTail, nodeHead) == 0) printf("The edge was successfully removed from the graph!\n\n");
	} else {
		printf("/!\\ Please create or load a graph first\n\n");
	}
	back_to_menu();
}

/* Menu to view a graph
 * Params:
 * - Graph *graph: the graph to view
 * Return:
 * - void
 */
void menu_view_graph(const struct Graph *graph) {
	if (graph->adjList != NULL) {
		view_graph(graph);
	} else {
		printf("/!\\ Please create or load a graph first\n\n");
	}
	back_to_menu();
}

/* Menu to save a graph
 * Params:
 * - Graph *graph: the graph to save
 * Return:
 * - void
 */
void menu_save_graph(const struct Graph *graph) {
	if (graph->adjList != NULL) {
		char *filename = malloc(1000 * sizeof(char));
		do  {
			printf("Write the name of the file : \n");
		} while (read_string(filename, 1000) < 0);
	
		save_graph(graph, filename);
		printf("The graph was successfully saved into %s. If you didn't specify an existing file, you will find your graph in SAVES/\n\n", filename);
		free(filename);
	} else {
		printf("/!\\ Please create or load a graph first\n\n");
	}
	back_to_menu();
}

/* Menu to quit the program
 * Params:
 * - Graph *graph: the graph created in the menu
 * Return:
 * - boolean: true if the user decides to quits, false otherwise
 */
bool menu_quit(struct Graph *graph) {
	long choice = -1;
	do {
		printf("Are you sure you want to quit? Unsaved changes will be lost.\n1: quit\n0: stay\n");
		choice = read_long();
	} while (choice < 0 || choice > 1);
	if (choice == 1) {
		(graph->adjList != NULL) ? destroy_graph(graph) : free(graph);
		return true;
	}
	return false;
}

/* Menu to calculate the maximum flow of a graph
 * Params:
 * - Graph *graph: the graph created in the menu
 * Return:
 * - void
 */
void menu_maximum_flow(const struct Graph *graph) {

	int source, sink, alg;

	// The graph must be directed. If it's not, we leave the function
	if (!graph->isDirected) {
		printf("/!\\ This operation can only be performed on a directed graph.\n");
		back_to_menu();
		return;
	} 

	// The graph must have at least two nodes
	if (get_node_number(graph) < 2) {
		printf("/!\\ Your graph must be composed of at least 2 nodes.\n");
		back_to_menu();
		return;
	}

	// Input the source node
	do {
		printf("Which node of the graph is your source node?\n");
		
		source = read_long();

		// Verifies that the source node is in the graph
		if (graph->adjList[source - 1] == NULL) {
			printf("The source node doesn't exist in the graph, please choose another one.\n\n");
		}

	} while (graph->adjList[source - 1] == NULL);

	printf("Your source node is %d.\n", source);

	// Input the sink node
	do {
		printf("Which node of the graph is your sink node?\n");
		
		sink = read_long();

		// Verifies that the source node is in the graph
		if (graph->adjList[sink - 1] == NULL) {
			printf("The sink node doesn't exist in the graph, please choose another one.\n\n");
		}

		// Verifies that the sink node isn't the source node
		if (source == sink) {
			printf("The node %d is already your source node. Please choose another one to be your sink node. \n", sink);
		} 
	} while (graph->adjList[sink - 1] == NULL || source == sink);

	printf("Your sink node is %d.\n", sink);

	// Choose the algorithm to be used
	do {
		printf("What algorithm do you wish to use to find a path between the source and the sink node?\n\t- 1) Breadth First Search (BFS)\n\t- 2) Depth First Search (DFS)\n\t- 3) Random path\n\t- 4) Shortest path\n");

		alg = read_long();

		// Verifies that the input is between 1 and 4
		if (alg < 1 || alg > 4) {
			printf("Please choose a number between 1 and 4\n\n");
		}

	} while (alg < 1 || alg > 4);

	// print what the user chose (I <3 ternary expressions)
	printf ("You chose %s.\n\n", alg < 3 ? (alg == 1 ? "BFS" : "DFS") : (alg == 3 ? "random path" : "shortest path"));

	printf("The maximum flow of the graph is : %d\n", ford_fulkerson(graph, source, sink, alg));
	back_to_menu();
	
}

// Function to get back to the main menu
void back_to_menu() {
	int res = -1;	
	do {
		printf("\n-------------------------------------------\n1) Get back to the menu\n");	
		res = read_long();

	} while (res != 1);
}
