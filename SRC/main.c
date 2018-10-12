#include <stdio.h>
#include <stdlib.h>
#include "../INCLUDE/list.h"
#include "../INCLUDE/graph.h"

int main() {
	int gameFinish = 0;
	int answerMain = 0;
	
	while (!gameFinish) {
		do  {
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
			
			// HUMAIN CHOISIR
		} while (answerMain < 1 || answerMain > 9);
		
		switch (answerMain) {
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			break;
		default:
			gameFinish = 1;
			break;
		}
	}
	
	return 0;
}