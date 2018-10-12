#include <stdio.h>
#include <stdlib.h>
#include "../INCLUDE/list.h"
#include "../INCLUDE/graph.h"

int main() {
	int gameFinish = 0;
	
	while (!gameFinish) {
		printf("---MENU---");
		printf("1. Create graph");
		printf("2. Load graph");
		printf("3. Add node");
		printf("4. Add edge");
		printf("5. Remove node");
		printf("6. Remove edge");
		printf("7. View graph");
		printf("8. Save graph");
		printf("9. Quit");
	}
	
	return 0;
}