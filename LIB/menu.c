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
		return -1; // We return 0 if the function can't convert to long
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
		printf("Please first destroy your current graph before creating a new one\n\n");
	}
}

/* Menu to load a graph
 * Params:
 * - Graph *graph: the graph to load
 * Return:
 * - void
 */
void menu_load_graph(struct Graph *graph) {
	if (graph->adjList == NULL) {
		char *filename = malloc(1000 * sizeof(char));		
		do {
			printf("Write the name of the file (relative path from the root directory of this project) : \n");
		} while (!read_string(filename, 1000));

		if (load_graph(graph, filename) == 0) printf("Your graph was loaded with success!\n\n");

		free(filename);
	}
	else {
		printf("Please first destroy your current graph before loading a new one\n\n");
	}
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
		printf("Please create or load a graph first\n");
	}
}

/* Menu to add an edge into a graph
 * Params:
 * - Graph *graph: the graph to which we want to add an edge
 * Return:
 * - void
 */
void menu_add_edge(struct Graph *graph) {
	if (graph->adjList != NULL) {
		long nodeTail = 0;
		long nodeHead = 0;
		long weight = 0;
		bool symmetric = false;
		bool alreadyCreated = false;
		
		if (get_node_number(graph) == 0) {
			printf("There are no nodes in the graph. Please insert nodes before inserting edges\n\n");
		}
		else {
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
		}
	} else {
		printf("Please create or load a graph first\n\n");
	}
}

/* Menu to remove a node from a graph
 * Params:
 * - Graph *graph: the graph in which we want to remove a node
 * Return:
 * - void
 */
void menu_remove_node(struct Graph *graph) {
	if (get_node_number(graph) == 0) {
		printf("There are no nodes in the graph\n\n");
	}
	else if (graph->adjList != NULL) {
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
		printf("Please create or load a graph first\n\n");
	}
}

/* Menu to remove an edge from a graph
 * Params:
 * - Graph *graph: the graph from which we want to remove an edge
 * Return:
 * - void
 */
void menu_remove_edge(struct Graph *graph) {
	if (get_node_number(graph) == 0) {
		printf("There are no edges in the graph\n\n");
	}
	else if (graph->adjList != NULL) {
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
		printf("Please create or load a graph first\n\n");
	}
}

/* Menu to view a graph
 * Params:
 * - Graph *graph: the graph to view
 * Return:
 * - void
 */
void menu_view_graph(struct Graph *graph) {
	if (graph->adjList != NULL) {
		view_graph(graph);
	} else {
		printf("Please create or load a graph first\n\n");
	}
}

/* Menu to save a graph
 * Params:
 * - Graph *graph: the graph to save
 * Return:
 * - void
 */
void menu_save_graph(struct Graph *graph) {
	if (graph->adjList != NULL) {
		char *filename = malloc(1000 * sizeof(char));
		do  {
			printf("Write the name of the file : \n");
		} while (!read_string(filename, 1000));
	
		save_graph(graph, filename);
		printf("The graph was successfully saved into %s\n\n", filename);
		free(filename);
	} else {
		printf("Please create or load a graph first\n\n");
	}
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
