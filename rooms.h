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

//Function prototypes

//Creates a room and initializes its values
Room *createRoom(char *desc, Inventory *items, Room *n, Room *s, Room *e, Room *w, Room *u, Room *d);
//deletes all rooms in an array of rooms
void deleteRooms(Room **rooms, int length);

void setNorth(Room *current, Room *toAdd);
void setSouth(Room *current, Room *toAdd);
void setEast(Room *current, Room *toAdd);
void setWest(Room *current, Room *toAdd);
void setUp(Room *current, Room *toAdd);
void setDown(Room *current, Room *toAdd);

void addRoomItem(Room *room, Item *item);


#endif
