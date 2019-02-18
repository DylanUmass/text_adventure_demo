#include <stdio.h>
#include <stdlib.h>
#include "rooms.h"
#include "items.h"

Room *createRoom(char *desc, Inventory *items, Room *n, Room *s, Room *e, Room *w, Room *u, Room *d) {
	Room *newRoom = malloc(sizeof(Room));
	newRoom->items = items;
	newRoom->desc = desc;
	newRoom->north = n;
	newRoom->south = s;
	newRoom->east = e;
	newRoom->west = w;
	newRoom->up = u;
	newRoom->down = d;
	return newRoom;
}
