/*
	PW2 - Graph Library Representation by Adjacency Lists
	Thibault BERTIN - Timothée LAURENT
	Master 1 CMI Informatique - TP1A
*/
#include "../INCLUDE/menu.h"

int main() {
	bool finish = false; // To know if it's finished
	long answerMain = 0; // Answer for the main menu
	struct Graph *graph = calloc(1, sizeof(struct Graph));
	
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
			printf("9. Compute the maximum flow of the graph\n");
			printf("10. Quit\n");
			printf("-------------------------------------------\n");
			printf("Input the number of the action you wish to execute:\n");
			
			answerMain = read_long();
		} while (answerMain < 1 || answerMain > 10);
		
		printf("-------------------------------------------\n");
		switch (answerMain) {
			case 1: // Create graph
				menu_create_graph(graph);
				break;
			case 2: // Load graph
				menu_load_graph(graph);
				break;
			case 3: // Add node
				menu_add_node(graph);
				break;
			case 4: // Add edge
				menu_add_edge(graph);
				break;
			case 5: // Remove node
				menu_remove_node(graph);
				break;
			case 6: // Remove edge
				menu_remove_edge(graph);
				break;
			case 7: // View graph
				menu_view_graph(graph);
				break;
			case 8: // Save graph
				menu_save_graph(graph);
				break;
			case 9: // Maximum flow
				menu_maximum_flow(graph);
				break;
			default: // Quit
				finish = menu_quit(graph);
		}
	}
	
	free(graph);
	graph = NULL;
	
	return 0;
}
