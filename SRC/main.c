/*
	PW2 - Graph Library Representation by Adjacency Lists
	Thibault BERTIN - Timothée LAURENT
	Master 1 CMI Informatique - TP1A
*/
#include "../INCLUDE/list.h"
#include "../INCLUDE/graph.h"

// To clear the buffer
void clearBuffer() {
	int c = 0;
	
	while (c != '\n' && c != EOF) {
		c = getchar();
	}
}
 
// To read a string in stdin
int readString(char *string, int length) {
	char *positionEntry = NULL;
	
	// We read the text entered on the keyboard
	if (fgets(string, length, stdin) != NULL) { // Check entry error
		positionEntry = strchr(string, '\n'); // We search '\n' to replace it with '\0'
		
		if (positionEntry != NULL) {
			*positionEntry = '\0';
		}
		else {
			clearBuffer();
		}
		return 0; // We return 0 if the function ran without error
	}
	else {
		clearBuffer();
		return 1; // We return 1 if the function ran with error
	}
}

// To read a long in stdin
long readLong() {
	char TextNumber[1000] = {0};
	
	if (readString(TextNumber, 1000)) {
		return strtol(TextNumber, NULL, 10);
	}
	else {
		return 0; // We return 0 if the function can't convert
	}
}

int main() {
	bool finish = false; // To know if it's finish
	long answerMain = 0; // Answer for the main menu
	
	struct Graph *graph = malloc(sizeof(struct Graph));
	
	while (!finish) {
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
			
			answerMain = readLong();
		} while (answerMain < 1 || answerMain > 9);
		
		switch (answerMain) {
		case 1: // Create graph
			if (graph->adjList == NULL) {
				long nbMaxNodes = 0;
				do  {
					printf("Write a number for the maximum node's number of your graph : \n");
					
					nbMaxNodes = readLong();
				} while (nbMaxNodes < 1);
				
				bool isDirected = false;
				long tmpChoice = 0;
				do  {
					printf("Is your graph directed ? 1 for yes, 0 for no : \n");
					
					tmpChoice = readLong();
				} while (tmpChoice != 0 || tmpChoice != 1);
				isDirected = (tmpChoice == 1) ? true : false;
				
				create_graph(graph, isDirected, nbMaxNodes);
			}
			break;
		case 2: // Load graph
			if (graph->adjList == NULL) {
				char *filename = malloc(1000 * sizeof(char));
				
				do {
					printf("Write the name of the file : \n");
				} while (!readString(filename, 1000));
				
				load_graph(graph, filename);
				
				free(filename);
			}
			break;
		case 3: // Add node
			if (graph->adjList != NULL) {
				long nbNode = 0;
				do  {
					printf("Write the number of the node you want insert : \n");
					
					nbNode = readLong();
					
					// Verifies that the node is not already in the graph and that the node's number is correct
					if (nbNode > graph->nbMaxNodes) {
						printf("Can't add more than %d nodes to this graph. Please choose a value <= %d", graph->nbMaxNodes, graph->nbMaxNodes);
					}
					if (nbNode < 1) {
						printf("Can't add this node to this graph. Please choose a value >= 1");
					}
					if (&graph->adjList[nbNode-1] != NULL) {
						printf("This node already exists in the graph. Please choose another value");
					}
				} while ((nbNode > graph->nbMaxNodes) || (nbNode < 1) || (&graph->adjList[nbNode-1] != NULL));
				
				add_node(graph, nbNode);
			}
			break;
		case 4: // Add edge
			if (graph->adjList != NULL) {
				long nodeTail = 0;
				long nodeHead = 0;
				long weight = 0;
				bool symmetric = false;
				
				bool alreadyCreate = false;
				do {
					alreadyCreate = false;
					do  {
						printf("Write the number of the tail node : \n");
						
						nodeTail = readLong();
						
						// Verifies that the tail node is in the graph
						if (&graph->adjList[nodeTail-1] == NULL) {
							printf("The tail node doesn't exist in the graph. Please choose another node");
						}
					} while (&graph->adjList[nodeTail-1] == NULL);
					
					do  {
						printf("Write the number of the head node : \n");
						
						nodeHead = readLong();
						
						// Verifies that the head node is in the graph
						if (&graph->adjList[nodeHead-1] == NULL) {
							printf("The head node doesn't exist in the graph. Please choose another node");
						}
					} while (&graph->adjList[nodeHead-1] == NULL);
					
					if (graph->isDirected) {
						long tmpChoice = 0;
						do  {
							printf("Do you want to add the corresponding symetric edge ? 1 for yes, 0 for no : \n");
							
							tmpChoice = readLong();
						} while (tmpChoice != 0 || tmpChoice != 1);
						symmetric = (tmpChoice == 1) ? true : false;
					}
					else {
						symmetric = true;
					}
					
					if (symmetric) {
						struct Neighbour *curr = &graph->adjList[nodeTail - 1];
						while (curr != NULL) {
							if (curr->neighbour == nodeHead) {
								printf("This edge already exists in the graph. Please choose another value");
								alreadyCreate = true;
							}
							curr = curr->nextNeighbour;
						}
						
						curr = &graph->adjList[nodeHead - 1];
						while (curr != NULL) {
							if (curr->neighbour == nodeTail) {
								printf("This edge already exists in the graph. Please choose another value");
								alreadyCreate = true;
							}
							curr = curr->nextNeighbour;
						}
					}
					else {
						struct Neighbour *curr = &graph->adjList[nodeTail - 1];
						while (curr != NULL) {
							if (curr->neighbour == nodeHead) {
								printf("This edge already exists in the graph. Please choose another value");
								alreadyCreate = true;
							}
							curr = curr->nextNeighbour;
						}
					}
				} while (alreadyCreate);
				
				do  {
					printf("Write the weight of the edge : \n");
					
					weight = readLong();
				} while (weight < 0);
				
				add_edge(graph, nodeTail, nodeHead, weight, symmetric);
			}
			break;
		case 5: // Remove node
			if (graph->adjList != NULL) {
				long node = 0;
				do  {
					printf("Write the number of the node you want remove : \n");
					
					node = readLong();
					
					// Verifies that the node is in the graph and that the node's number is correct
					if (node > graph->nbMaxNodes) {
						printf("This node isn't in the graph");
					}
					if (node < 1) {
						printf("This node isn't in the graph");
					}
					if (&graph->adjList[node-1] == NULL) {
						printf("This node didn't exists in the graph. Please choose another value");
					}
				} while ((node > graph->nbMaxNodes) || (node < 1) || (&graph->adjList[node-1] == NULL));
				
				remove_node(graph, node);
			}
			break;
		case 6: // Remove edge
			if (graph->adjList != NULL) {
				long nodeTail = 0;
				long nodeHead = 0;
				
				do  {
					printf("Write the number of the tail node : \n");
					
					nodeTail = readLong();
					
					// Verifies that the tail node is in the graph
					if (&graph->adjList[nodeTail-1] == NULL) {
						printf("The tail node doesn't exist in the graph. Please choose another node");
					}
				} while (&graph->adjList[nodeTail-1] == NULL);
				
				do  {
					printf("Write the number of the head node : \n");
					
					nodeHead = readLong();
					
					// Verifies that the head node is in the graph
					if (&graph->adjList[nodeHead-1] == NULL) {
						printf("The head node doesn't exist in the graph. Please choose another node");
					}
				} while (&graph->adjList[nodeHead-1] == NULL);
				
				remove_edge(graph, nodeTail, nodeHead);
			}
			break;
		case 7: // View graph
			if (graph->adjList != NULL) {
				view_graph(graph);
			}
			break;
		case 8: // Save graph
			if (graph->adjList != NULL) {
				char *filename = malloc(1000 * sizeof(char));
				
				do  {
					printf("Write the name of the file : \n");
				} while (!readString(filename, 1000));
				
				save_graph(graph, filename);
				
				free(filename);
			}
			break;
		default: // Quit
			destroy_graph(graph);
			finish = true;
			break;
		}
	}
	
	return 0;
}
