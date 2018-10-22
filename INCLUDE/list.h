/*
	PW2 - Graph Library Representation by Adjacency Lists
	list.h - Implementation of linked list (Neighbour) structure
	Thibault BERTIN - Timothée LAURENT
	Master 1 CMI Informatique - TP1A
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
};

/*
 * Create an empty neighbour
 * Params:
 * - Neighbour *self: the neighbour you wish to create
 * - int neighbour: the number of the neighbour
 * - int weight: the weight of the neighbour
 * Return:
 * - void
 */
void create_neighbour(struct Neighbour *self, int neighbour, int weight);

/*
 * Destroy every neighbour from a list
 * Params:
 * - Neighbour **self: the neighbour you wish to destroy
 * Return:
 * - void
 */
void destroy_neighbour(struct Neighbour **self);

/*
 * Add an element in front of a neighbour
 * Params:
 * - Neighbour **self: the neighbour to whom you wish to add a neighbour
 * - int neighbour: the number of the neighbour
 * - int weight: the weight of the neighbour
 * Return:
 * - void
 */
void add_neighbour(struct Neighbour **self, int neighbour, int weight);

/*
 * Remove a neighbour
 * Params:
 * - Neighbour **self: the neighbour you wish to remove
 * Return:
 * - void
 */ 
void remove_neighbour(struct Neighbour *self);

/*
 * Get the size of the list of neighbours
 * Params:
 * - Neighbour *self: the neighbour of whom you wish to get the size
 * Return:
 * - size_t the size of the neighbour
 */
size_t neighbour_size(struct Neighbour *self);

#endif // LIST_H
