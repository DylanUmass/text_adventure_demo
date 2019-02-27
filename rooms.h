#ifndef _ROOMS_H
#define _ROOMS_H
#include "items.h"
#include "event_list.h"

typedef struct Room Room;
struct Room
	{
		char *desc;
		Inventory *items;
		struct eventList *events;
		Room *north;
		Room *south;
		Room *east;
		Room *west;
		Room *up;
		Room *down;
	};

enum direction {north, south, east, west, up, down};
typedef enum direction Direction;

/*	Holds information about an event where a "key" is used to connect one room 
	to another in a certain direction */
typedef struct KeyEvent KeyEvent;
struct KeyEvent 
	{
		Item key;
		Room *startRoom;
		Direction dir;
		Room *endRoom;
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

//Adds an item to a room
void addRoomItem(Room *room, Item item);

//Checks if two KeyEvents have the same data
_Bool keyEventIsEquals(KeyEvent event1, KeyEvent event2);

#endif
