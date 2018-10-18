/*
	PW2 - Graph Library Representation by Adjacency Lists
	Thibault BERTIN - Timothée LAURENT
	Master 1 CMI Informatique - TP1A
*/

#include "../INCLUDE/list.h"

/*
 * Create an empty neighbour
 */
void create_neighbour(struct Neighbour *self, int neighbour, int weight) {
	assert(self);
	
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
void destroy_neighbour_rec(struct Neighbour *self, int direction) {
	if (!self) {
		return;
	}
	if (direction <= 0) {
		destroy_neighbour_rec(self->previousNeighbour, -1);
	}
	if (direction >= 0) {	
		destroy_neighbour_rec(self->nextNeighbour, 1);
	}
	remove_neighbour(self);
}

/*
 * Destroy every neighbour from a list
 */
void destroy_neighbour(struct Neighbour *self) {
	assert(self);
	
	destroy_neighbour_rec(self, 0);
}

/*
 * Add an element in front of a neighbour
 */
void add_neighbour(struct Neighbour *self, int neighbour, int weight) {
	assert(self);
	
	struct Neighbour *new = malloc(sizeof(struct Neighbour));
	create_neighbour(new, neighbour, weight);
	
	if (!self->previousNeighbour) {
		self->previousNeighbour = new;
		new->nextNeighbour = self;
	}
	else {
		self->previousNeighbour->nextNeighbour = new;
		new->previousNeighbour = self->previousNeighbour;
		new->nextNeighbour = self;
		self->previousNeighbour = new;
	}
}

/*
 * Remove a neighbour
 */ 
void remove_neighbour(struct Neighbour *self) {
	assert(self);
	
	self->nextNeighbour->previousNeighbour = self->previousNeighbour;
	self->previousNeighbour->nextNeighbour = self->nextNeighbour;
	
	free(self);
}

/*
 * Recursively count all neighbours
 * direction indicates the direction to follow to avoid useless recursive calls :
 * direciton == 0 	-> call recursively on previous and next neighbours
 * direction  > 0 	-> call recursively on next neighbours
 * direction  < 0	-> call recursively on previous neighbours
 */
void neighbour_size_rec(const struct Neighbour *self, size_t *neighbourSize, int direction) {
	if (!self) {
		return;	
	}
	if (direction <= 0) {
		neighbour_size_rec(self, neighbourSize, -1);
	}
	if (direction >= 0) {	
		neighbour_size_rec(self, neighbourSize, 1);
	}
	(*neighbourSize)++;
}

/*
 * Get the size of the list of neighbours
 */
size_t neighbour_size(const struct Neighbour *self) {
	assert(self);
	
	size_t neighbourSize = 0;
	neighbour_size_rec(self, &neighbourSize, 0);
	
	return neighbourSize;
}
