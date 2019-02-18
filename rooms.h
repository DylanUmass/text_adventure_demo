#ifndef _ROOMS_H
#define _ROOMS_H
#include "items.h"

typedef struct Room Room;
struct Room
	{
		char *desc;
		Inventory *items;
		Room *north;
		Room *south;
		Room *east;
		Room *west;
		Room *up;
		Room *down;
	};

Room *createRoom(char *desc, Inventory *items, Room *n, Room *s, Room *e, Room *w, Room *u, Room *d);
#endif
