#include "../INCLUDE/list.h"

/*
 * Create an empty neighbour
 */
void create_neighbour(struct Neighbour *self, int neighbour, int weight) {
	self->previousNeighbour = NULL;
	self->nextNeighbour = NULL;
	self->neighbour = neighbour;
	self->weight = weight;
}

/*
 * Recursively remove all neighbours
 * direction indicates the direction to follow to avoid useless recursive calls :
 * direciton == 0 	-> call recursively on previous and next neighbours
 * direction  > 0 	-> call recursively on next neighbours
 * direction  < 0	-> call recursively on previous neighbours
 */
void remove_all_neighbours(struct Neighbour *self, int direction) {
	if (!self) {
		return;	
	}
	if (direction <= 0) {
		remove_all_neighbours(self->previousNeighbour, -1);
	}
	if (direction >= 0) {	
		remove_all_neighbours(self->nextNeighbour, 1);
	}
	remove_neighbour(self);
}

/*
 * Destroy a neighbour
 */
void destroy_neighbour(struct Neighbour *self) {
	assert(self);
	remove_all_neighbours(self, 0);
}

/*
 * Add an element in front of a neighbour
 */
void add_neighbour(struct Neighbour *self, int neighbour, int weight) {
	assert(self);
	if (!self->previousNeighbour) {
		struct Neighbour *new = malloc(sizeof(struct Neighbour));
		create_neighbour(new, neighbour, weight);
		self->previousNeighbour = new;
	} 
	// CAREFUL, WON'T ADD IF PREVIOUS NEIGHBOUR IS OCCUPIED
}

/*
 * Remove a neighbour
 */ 
void remove_neighbour(struct Neighbour *self) {
	assert(self);
	self->nextNeighbour->previousNeighbour = self->previousNeighbour;
	free(self);	
}

/*
 * Get the size of the list of neighbours
 */
size_t neighbour_size(const struct Neighbour *self) {
	return 0;
}
