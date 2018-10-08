#include <stdio.h>
#include <stdlib.h>
#include "./INCLUDE/list.h"
#include "./INCLUDE/graph.h"

int main() {
	printf("hello");
	struct list *self = malloc(sizeof(struct list));
	list_create(self);
	list_is_empty(self) ? printf("empty") : printf("pas empty");
	list_destroy(self);
	return 0;
}
