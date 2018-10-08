/*
	PW2 - Graph Library Representation by Adjacency Lists
	Thibault BERTIN - Timothée LAURENT
	TP1A - CM1
*/
#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

struct Neighbour {
	int neighbour;
	int weight;
	struct Neighbour *nextNeighbour;
	struct Neighbour *previousNeighbour;
};

/*
 * Create an empty neighbour
 */
void create_neighbour(struct Neighbour *self, int neighbour, int weight);

/*
 * Destroy a neighbour
 */
void destroy_neighbour(struct Neighbour *self);

/*
 * Add an element in front of a neighbour
 */
void add_neighbour(struct Neighbour *self, int neighbour, int weight);

/*
 * Remove a neighbour
 */ 
void remove_neighbour(struct Neighbour *self);

/*
 * Get the size of the list of neighbours
 */
size_t neighbour_size(const struct Neighbour *self);

#endif // LIST_H
