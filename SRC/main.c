/*
	PW2 - Graph Library Representation by Adjacency Lists
	Thibault BERTIN - Timothée LAURENT
	Master 1 CMI Informatique - TP1A
*/
#include "../INCLUDE/list.h"
#include "../INCLUDE/graph.h"

// To clear the buffer
void clear_buffer() {
	int c = 0;
	
	while (c != '\n' && c != EOF) {
		c = getchar();
	}
}
 
// To read a string in stdin
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
		return 1; // We return 1 if the function ran without error
	}
	else {
		clear_buffer();
		return 0; // We return 0 if the function ran with error
	}
}

// Read a long from stdin
long read_long() {
	char TextNumber[1000] = {0};
	
	if (read_string(TextNumber, 1000)) {
		return strtol(TextNumber, NULL, 10);
	}
	else {
		return 0; // We return 0 if the function can't convert
	}
}

int main() {
	bool finish = false; // To know if it's finish
	long answerMain = 0; // Answer for the main menu
	long choice = 0;
	struct Graph *graph = malloc(sizeof(struct Graph));
	
	while (finish == false) {
		do  {
			printf("---MENU---\n");
			printf("1. Create graph\n");
			printf("2. Load graph\n");
			printf("3. Add node\n");
			printf("4. Add edge\n");
			printf("5. Remove node\n");
			printf("6. Remove edge\n");
			printf("7. View graph\n");
			printf("8. Save graph\n");
			printf("9. Quit\n");
			printf("-----------\n");
			printf("Input the number of the action you wish to execute:\n");
			
			answerMain = read_long();
		} while (answerMain < 1 || answerMain > 9);
		
		switch (answerMain) {
		case 1: // Create graph
			if (graph->adjList == NULL) {
				long nbMaxNodes = 0;
				do  {
					printf("Input a number for the maximum number of nodes your graph can have :\n");
					
					nbMaxNodes = read_long();
				} while (nbMaxNodes < 1);
				
				long tmpChoice = 0;
				do  {
					printf("Is your graph directed ? 1 for yes, 0 for no : \n");
					
					tmpChoice = read_long();
				} while (tmpChoice != 0 && tmpChoice != 1);
				create_graph(graph, (tmpChoice == 1) ? true : false, nbMaxNodes);
				printf("Your graph was created with success!\n\n");
			} else {
				printf("Please first destroy your current graph before creating a new one\n\n");
			}
			break;
		case 2: // Load graph
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
			break;
		case 3: // Add node
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
			break;
		case 4: // Add edge
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
			break;
		case 5: // Remove node
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
			break;
		case 6: // Remove edge
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
			break;
		case 7: // View graph
			if (graph->adjList != NULL) {
				view_graph(graph);
			} else {
				printf("Please create or load a graph first\n\n");
			}
			break;
		case 8: // Save graph
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
			break;
		case 9: // Quit
			do {
				printf("Are you sure you want to quit? Unsaved changes will be lost.\n1: quit\n0: stay\n");
				choice = read_long();
			} while (choice < 0 || choice > 1);
			if (choice == 1) {
				if (graph->adjList != NULL) {
					destroy_graph(graph);
				}
				else {
					free(graph);
				}
				finish = true;
			}
			break;
		default:
			break;
		}
	}
	return 0;
}
