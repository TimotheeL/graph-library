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
		printf("\n\t---------------CREATE GRAPH---------------\n\n");
		printf("Maximum number of nodes of your graph : ");
		nbMaxNodes = read_long();
		
		while (nbMaxNodes < 1) {
			printf("\nPlease input a positive integer : ");
			nbMaxNodes = read_long();
		}

	
		do  {
			printf("\nIs your graph directed ?\n\t1. Yes\n\t2. No\n");
			tmpChoice = read_long();
		} while (tmpChoice != 1 && tmpChoice != 2);
		create_graph(graph, (tmpChoice == 1) ? true : false, nbMaxNodes);
		printf("\n\t+--------------------------------------+\n\t| Your graph was created with success! |\n\t+--------------------------------------+\n\n");
	} else {
		// If a graph is already loaded or created we ask the user if he wants to destroy it
		long delete = 0;
		printf("\n\t+--------------------------------------+\n\t| /!\\ You already have a graph loaded. |\n\t+--------------------------------------+\n\n Do you wish to destroy your current graph?\n\n\t1. Yes\n\t2. No\n\n");
		do {
			delete = read_long();
		} while (delete < 1 || delete > 2);
		
		// If the user chooses to destroy the graph.
		
		if (delete == 1) {
			destroy_graph(graph);
			menu_create_graph(graph);
		}
	}
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
		
		printf("\n\t+--------------------------------------+\n\t| /!\\ You already have a graph loaded. |\n\t+--------------------------------------+\n\n Do you wish to replace your current graph with a new one?\n\n\t1. Yes\n\t2. No\n");
		do {
			delete = read_long();
		} while (delete < 1 || delete > 2);
		
		// If the user chooses to replace the graph with a new one.
		
		if (delete == 1) {
			destroy_graph(graph);
		}
	}
	if (delete == 1) {
		char *filename = malloc(1000 * sizeof(char));		
		printf("\n\t----------------LOAD GRAPH----------------\n");		
		do {
			printf("\nWrite the name of the file (relative path from the root directory of this project) : ");
		} while (read_string(filename, 1000));
		
		if (load_graph(graph, filename) == 0) printf("\n\n\t+-------------------------------------+\n\t| Your graph was loaded with success! |\n\t+-------------------------------------+\n\n");

		free(filename);
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
		printf("\n\t---------------ADD NODE---------------\n\n");
		
		// Check if there are empty slots to add nodes
		bool noEmptyNodes = true;
		for (int i = 0; i < graph->nbMaxNodes; i++) {
			if (!graph->adjList[i]) {
				noEmptyNodes = false;
			}
		}
		
		if (noEmptyNodes) {
			printf("\n\t+-----------------------------------------------+\n\t| /!\\ This graph is full, no node can be added. |\n\t+-----------------------------------------------+\n");
			return;
		}
		
		do  {
			printf("\nInput the number of the node you want to insert, or 0 if you want to cancel : ");
		
			nbNode = read_long();
		
			// Verifies that the node is not already in the graph and that the node's number is correct
			if (nbNode > graph->nbMaxNodes || nbNode < 0) {
				printf("\n\t+------------------------------------------------------------------------+\n\t| /!\\ Please choose a value between 1 and %d, or 0 if you want to cancel. |\n\t+------------------------------------------------------------------------+\n", graph->nbMaxNodes);
			}
			if (nbNode > 0 && graph->adjList[nbNode-1] != NULL) {
				printf("\n\t+-------------------------------------------------------------------------+\n\t| /!\\ This node already exists in the graph, please choose another value. |\n\t+-------------------------------------------------------------------------+\n");
			}
		} while ((nbNode > 0 && ((nbNode > graph->nbMaxNodes) || (graph->adjList[nbNode-1] != NULL))) || (nbNode < 0));
		
		if (nbNode == 0) return;
		if (add_node(graph, nbNode) == 0) printf("\n\t+-------------------------------------------------+\n\t| The node %ld was added to the graph with success! |\n\t+-------------------------------------------------+\n", nbNode);
						      
	} else {
		menu_empty_graph(graph);	
	}
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
		menu_empty_graph(graph);
		return;
	}

	if (get_node_number(graph) == 0) {
		printf("\n\t+---------------------------------------------+\n\t| /!\\ There are no nodes in the graph.        |\n\t| Please insert nodes before inserting edges. |\n\t+---------------------------------------------+\n\n");
		return;
	}
	printf("\n\t-----------------ADD EDGE-----------------\n\n");
	do {
		alreadyCreated = false;
		
		// INPUT THE TAIL NODE
		do  {
			printf("\nWrite the number of the tail node : ");
			nodeTail = read_long();
			
			// Verifies that the tail node is in the graph
			if (graph->adjList[nodeTail-1] == NULL) {
				printf("\n\t+-----------------------------------------------+\n\t| /!\\ The tail node doesn't exist in the graph. |\n\t| Please choose another node.                   |\n\t+-----------------------------------------------+\n");
			}
		} while (graph->adjList[nodeTail-1] == NULL);
		
		// INPUT THE HEAD NODE
		do  {
			printf("\nWrite the number of the head node : ");
			
			nodeHead = read_long();
			
			// Verifies that the head node is in the graph
			if (graph->adjList[nodeHead-1] == NULL) {
				printf("\n\t+-----------------------------------------------+\n\t| /!\\ The head node doesn't exist in the graph. |\n\t| Please choose another node.                   |\n\t+-----------------------------------------------+\n");
			}
		} while (graph->adjList[nodeHead-1] == NULL);
		
		// INPUT THE WEIGHT OF THE EDGE
		do  {
			if (weight < 0) {
				printf("\n\t+----------------------------------+\n\t| /!\\ The weight can't be negative |\n\t+----------------------------------+\n");
			}
			printf("\nInput the weight of the edge : ");
			weight = read_long();
		} while (weight < 0);
		
		// Check if the edge doesn't already exist
		struct Neighbour *curr = graph->adjList[nodeTail - 1];
		while (curr != NULL) {
			if (curr->neighbour == nodeHead) {
				printf("\n\t+--------------------------------------------+\n\t| /!\\ This edge already exists in the graph. |\n\t+--------------------------------------------+\n");
				long choice = 0;
				do {
					printf("\nDo you want to try to add another edge?\n\t1. Yes\n\t2. Get back to the menu\n");
					choice = read_long();
				} while (choice < 1 || choice > 2);
				if (choice == 1) {
					alreadyCreated = true;
				} else {
					return;
				}
			}
			curr = curr->nextNeighbour;
		}
		
		// Check if the symmetric doesn't already exist
		if (graph->isDirected) {
			struct Neighbour *curr = graph->adjList[nodeHead - 1];
			while (curr != NULL) {
				if (curr->neighbour == nodeTail) {
					symmetric = true;
				}
				curr = curr->nextNeighbour;
			}
		}
		
		// If the symmetric doesn't already exist
		if (!symmetric && graph->isDirected) {
			// We ask the user if he wants to add the symmetric
			long tmpChoice = 0;
			do  {
				printf("\nDo you want to add the corresponding symmetric edge ?\n\n\t1. Yes\n\t2. No\n");
				tmpChoice = read_long();
			} while (tmpChoice < 1 || tmpChoice > 2);
			symmetric = (tmpChoice == 1) ? true : false;
		}
	} while (alreadyCreated);
	//printf("%d", add_edge(graph, nodeTail, nodeHead, weight, symmetric));
	if (add_edge(graph, nodeTail, nodeHead, weight, symmetric) == 0) printf("\n\t+--------------------------------------------------------+\n\t| The edge %ld: (%ld/%ld) was added to the graph with success! |\n\t+--------------------------------------------------------+\n", nodeTail, nodeHead, weight);
}

/* Menu to remove a node from a graph
 * Params:
 * - Graph *graph: the graph in which we want to remove a node
 * Return:
 * - void
 */
void menu_remove_node(struct Graph *graph) {

	// If there are no nodes in the graph
	if (get_node_number(graph) == 0) {
		printf("\n\t+-----------------------------------+\n\t| /!\\ There are no nodes to remove. |\n\t+-----------------------------------+\n");
		return;
	}
	if (graph->adjList != NULL) {
		printf("\n\t--------------REMOVE NODE-------------\n\n");
		long node = 0;
		do  {
			printf("\nInput the number of the node you want to remove, 0 to cancel : ");
		
			node = read_long();
		
			// Verifies that the node is in the graph and that the node's number is correct
			if (node > graph->nbMaxNodes || node < 0 || (node > 0 && graph->adjList[node-1] == NULL)) {
					   
				printf("\n\t+-----------------------------------+\n\t| /!\\ This node isn't in the graph. |\n\t+-----------------------------------+\n");
			}
		} while (node > graph->nbMaxNodes || node < 0 || (node > 0 && graph->adjList[node-1] == NULL));
		if (node == 0) return;
		if (remove_node(graph, node) == 0) printf("\n\t+-----------------------------------------------------+\n\t| The node %ld was removed from the graph with success! |\n\t+-----------------------------------------------------+\n\n", node);
	} else {
		menu_empty_graph(graph);
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
		printf("\n\t+-------------------------------------+\n\t| /!\\ There are no edges in the graph |\n\t+-------------------------------------+\n");
		return;	
	} 

	if (graph->adjList != NULL) {
		long nodeTail = 0;
		long nodeHead = 0;
		printf("\n\t--------------REMOVE EDGE-------------\n\n");
		do {
			printf("\nWrite the number of the tail node : ");
			
			nodeTail = read_long();
			
			// Verifies that the tail node is in the graph
			if (graph->adjList[nodeTail-1] == NULL) {
				printf("\n\t+-----------------------------------------------+\n\t| /!\\ The tail node doesn't exist in the graph. |\n\t| Please choose another node.                   |\n\t+-----------------------------------------------+\n");
			}
		} while (graph->adjList[nodeTail-1] == NULL);
		
		do {
			printf("\nWrite the number of the head node : ");
			
			nodeHead = read_long();
			
			// Verifies that the head node is in the graph
			if (graph->adjList[nodeHead-1] == NULL) {
				printf("\n\t+-----------------------------------------------+\n\t| /!\\ The head node doesn't exist in the graph. |\n\t| Please choose another node.                   |\n\t+-----------------------------------------------+\n");
			}
		} while (graph->adjList[nodeHead-1] == NULL);
		if (remove_edge(graph, nodeTail, nodeHead) == 0) printf("\n\t+---------------------------------------------------+\n\t| The edge was successfully removed from the graph! |\n\t+---------------------------------------------------+\n\n");
	} else {
		menu_empty_graph(graph);
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
		printf("\n\t---------------VIEW GRAPH---------------\n\n");
		view_graph(graph);
		printf("\n\t----------------------------------------\n\n");
	} else {
		menu_empty_graph(graph);
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
		printf("\n\t---------------SAVE GRAPH---------------\n\n");
		char *filename = malloc(1000 * sizeof(char));
		do  {
			printf("Write the name of the file : ");
		} while (read_string(filename, 1000) < 0);
	
		save_graph(graph, filename);
		printf("\n\t+-----------------------------------------+\n\t| The graph was successfully saved.       |\n\t| If you didn't specify an existing file, |\n\t| you will find your graph in SAVES/      |\n\t+-----------------------------------------+\n\n");
		free(filename);
	} else {
		menu_empty_graph(graph);
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
		printf("Are you sure you want to quit? Unsaved changes will be lost.\n\t1. quit\n\t0. stay\n");
		choice = read_long();
	} while (choice < 0 || choice > 1);
	if (choice == 1) {
		if (graph->adjList != NULL) {
			destroy_graph(graph);
		}
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
		return;
	} 

	// The graph must have at least two nodes
	if (get_node_number(graph) < 2) {
		printf("/!\\ Your graph must be composed of at least 2 nodes.\n");
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
		printf("What algorithm do you wish to use to find a path between the source and the sink node?\n\t- 1. Breadth First Search (BFS)\n\t- 2. Depth First Search (DFS)\n\t- 3. Shortest path Floyd-Warshall\n");

		alg = read_long();

		// Verifies that the input is between 1 and 3
		if (alg < 1 || alg > 3) {
			printf("Please choose a number between 1 and 3\n\n");
		}

	} while (alg < 1 || alg > 3);

	// print what the user chose (I <3 ternary expressions)
	printf ("You chose %s.\n\n", alg < 3 ? (alg == 1 ? "BFS" : "DFS") : "Shortest path Floyd-Warshall");

	printf("The maximum flow of the graph is : %d\n", ford_fulkerson(graph, source, sink, alg));
}

/* Menu to tell the user no graph is yet created and to redirect him to the graph creation or load menu
 * Params:
 * - Graph *graph: the graph created in the menu
 * Return:
 * - void
 */
void menu_empty_graph(struct Graph *graph) {
	printf("\n\t+-----------------------------------------+\n\t| /!\\ Please create or load a graph first |\n\t+-----------------------------------------+\n\n\t1. Create a graph\n\t2. Load a graph\n\t3. Get back to the menu\n");
	int action = 0;
	do {
		action = read_long();
		switch (action) {
			case 1: menu_create_graph(graph);break;
			case 2: menu_load_graph(graph);break;
		}
	} while (action < 1 || action > 3);
}
