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
int read(char *string, int length) {
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
	char TextNumber[100] = {0};
	
	if (read(TextNumber, 100)) {
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
				char *filename = malloc(1000 * sizeof(struct char));
				
				long tmpChoice = 0;
				do  {
					printf("Write the name of the file : \n");
					
					if (read(filename, 1000)) {
						tmpChoice = 1;
					}
				} while (tmpChoice != 1);
				
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
					if (nbNode > self->nbMaxNodes) {
						printf("Error: Can't add more than %d nodes to this graph. Please choose a value <= %d", self->nbMaxNodes, self->nbMaxNodes);
					}
					if (nbNode < 1) {
						printf("Error: Can't add this node to this graph. Please choose a value >= 1");
					}
					if (&self->adjList[nbNode-1] != NULL) {
						printf("Error: This node already exists in the graph. Please choose another value");
					}
				} while ((nbNode > self->nbMaxNodes) || (nbNode < 1) || (&graph->adjList[nbNode-1] != NULL));
				
				add_node(graph, nbNode);
			}
			break;
		case 4: // Add edge
			if (graph->adjList != NULL) {
				
			}
			break;
		case 5: // Remove node
			if (graph->adjList != NULL) {
				long node = 0;
				do  {
					printf("Write the number of the node you want remove : \n");
					
					node = readLong();
					
					// Verifies that the node is in the graph and that the node's number is correct
					if (node > self->nbMaxNodes) {
						fprintf("Error: This node isn't in the graph");
					}
					if (node < 1) {
						fprintf("Error: This node isn't in the graph");
					}
					if (&self->adjList[node-1] == NULL) {
						fprintf("Error: This node didn't exists in the graph. Please choose another value");
					}
				} while ((node > self->nbMaxNodes) || (node < 1) || (&graph->adjList[node-1] == NULL));
				
				remove_node(graph, node);
			}
			break;
		case 6: // Remove edge
			if (graph->adjList != NULL) {
				
			}
			break;
		case 7: // View graph
			if (graph->adjList != NULL) {
				
			}
			break;
		case 8: // Save graph
			if (graph->adjList != NULL) {
				
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