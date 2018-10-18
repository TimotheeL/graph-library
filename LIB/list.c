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
 * Destroy every neighbour from a list
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
 */ 
void remove_neighbour(struct Neighbour **self) {
	assert(self);
	struct Neighbour *tmp = *self;	
	(*self) = tmp->nextNeighbour;
	free(tmp);
}

/*
 * Get the size of the list of neighbours
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
