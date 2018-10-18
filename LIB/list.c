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
	self->nextNeighbour = NULL;
	self->neighbour = neighbour;
	self->weight = weight;
}

/*
 * Recursively remove all neighbours
 */
void destroy_neighbour_rec(struct Neighbour *self) {
	if (!self) {
		return;
	}	
	destroy_neighbour_rec(self->nextNeighbour);
	remove_neighbour(self);
}

/*
 * Destroy every neighbour from a list
 */
void destroy_neighbour(struct Neighbour *self) {
	assert(self);
	destroy_neighbour_rec(self);
}

/*
 * Add an element in front of a neighbour
 */
void add_neighbour(struct Neighbour *self, int neighbour, int weight) {
	assert(self);
	struct Neighbour *new = malloc(sizeof(struct Neighbour));
	new->weight = weight;
	new->neighbour = neighbour;
	new->nextNeighbour = self;
	self = new;
}

/*
 * Remove a neighbour
 */ 
void remove_neighbour(struct Neighbour *self) {
	assert(self);	
	self = self->nextNeighbour;
		free(self);
}

/*
 * Get the size of the list of neighbours
 */
size_t neighbour_size(struct Neighbour *self) {
	assert(self);
	
	size_t neighbourSize = 0;
	struct Neighbour *curr = self;
	while(curr) {
		neighbourSize++;
		curr = curr->nextNeighbour;
	}
	
	return neighbourSize;
}
