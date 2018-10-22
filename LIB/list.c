/*
	PW2 - Graph Library Representation by Adjacency Lists
	list.h - Implementation of linked list (Neighbour) structure
	Thibault BERTIN - Timothée LAURENT
	Master 1 CMI Informatique - TP1A
*/

#include "../INCLUDE/list.h"

/*
 * Create an empty neighbour
 * Params:
 * - Neighbour *self: the neighbour you wish to create
 * - int neighbour: the number of the neighbour
 * - int weight: the weight of the neighbour
 * Return:
 * - void
 */
void create_neighbour(struct Neighbour *self, int neighbour, int weight) {
	assert(self);
	self->nextNeighbour = NULL;
	self->neighbour = neighbour;
	self->weight = weight;
}

/*
 * Destroy every neighbour from a list
 * Params:
 * - Neighbour **self: the neighbour you wish to destroy
 * Return:
 * - void
 */
void destroy_neighbour(struct Neighbour **self) {
	assert(self);
	struct Neighbour *curr = *self;
	struct Neighbour *next;
	while (curr) {
		next = curr->nextNeighbour;
		free(curr);
		curr = next;
	}
	*self = NULL;
}

/*
 * Add an element in front of a neighbour
 * Params:
 * - Neighbour **self: the neighbour to whom you wish to add a neighbour
 * - int neighbour: the number of the neighbour
 * - int weight: the weight of the neighbour
 * Return:
 * - void
 */
void add_neighbour(struct Neighbour **self, int neighbour, int weight) {
	assert(self);
	struct Neighbour *new = malloc(sizeof(struct Neighbour));
	new->weight = weight;
	new->neighbour = neighbour;
	new->nextNeighbour = (*self);
	(*self) = new;
}

/*
 * Remove a neighbour
 * Params:
 * - Neighbour **self: the neighbour you wish to remove
 * Return:
 * - void
 */
void remove_neighbour(struct Neighbour *self) {
	assert(self);
	
	struct Neighbour *next = self->nextNeighbour;
	self->nextNeighbour = next->nextNeighbour;
	self->neighbour = next->neighbour;
	self->weight = next->weight;
	free(next);
}

/*
 * Get the size of the list of neighbours
 * Params:
 * - Neighbour *self: the neighbour of whom you wish to get the size
 * Return:
 * - size_t the size of the neighbour
 */
size_t neighbour_size(struct Neighbour *self) {
	if (!self) return 0;
	
	size_t neighbourSize = 0;
	struct Neighbour *curr = self;
	while(curr) {
		neighbourSize++;
		curr = curr->nextNeighbour;
	}
	
	return neighbourSize;
}
