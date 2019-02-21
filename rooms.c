#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rooms.h"
#include "items.h"
#define DEBUG 1

//Creates a Room and initializes values
Room *createRoom(char *desc, Inventory *items, Room *n, Room *s, Room *e, Room *w, Room *u, Room *d) {
	Room *newRoom = malloc(sizeof(Room));
	if (newRoom == NULL)
		fprintf(stderr, "Failed to allocate memory to a new Room\n");
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

//deletes all rooms in an array of rooms
void deleteRooms(Room **rooms, int length){
	for (int i = 0; i < length; i++) {
		free(rooms[i]);
		rooms[i] = NULL;
	}
}

//These set a pointer of a given Room to another room
void setNorth(Room *current, Room *toAdd) {
	if (current == NULL)
		fprintf(stderr, "The room you're trying to modify is NULL");
	else
		current->north = toAdd;
}
void setSouth(Room *current, Room *toAdd) {
	if (current == NULL)
		fprintf(stderr, "The room you're trying to modify is NULL");
	else
		current->south = toAdd;
}
void setEast(Room *current, Room *toAdd) {
	if (current == NULL)
		fprintf(stderr, "The room you're trying to modify is NULL");
	else
		current->east = toAdd;
}
void setWest(Room *current, Room *toAdd) {
	if (current == NULL)
		fprintf(stderr, "The room you're trying to modify is NULL");
	else
		current->west = toAdd;
}
void setUp(Room *current, Room *toAdd) {
	if (current == NULL)
		fprintf(stderr, "The room you're trying to modify is NULL");
	else
		current->up = toAdd;
}
void setDown(Room *current, Room *toAdd) {
	if (current == NULL)
		fprintf(stderr, "The room you're trying to modify is NULL");
	else
		current->down = toAdd;
}

//Adds a given item to a given Room's inventory
void addRoomItem(Room *room, Item item) {
	int index = contains(item.name, room->items);
	if (index == -1) {
		addItem(item, room->items);
	}
}

#ifdef DEBUG
//Tests
int main() {
	printf("Starting Tests...\n");
	Room *testRoom = createRoom("For Testing",NULL, createRoom("Test N",NULL,NULL,NULL,NULL,NULL,NULL,NULL)
		, NULL, NULL, NULL, NULL, NULL);
	if (strcmp("For Testing",testRoom->desc) != 0 || strcmp("Test N",testRoom->north->desc) != 0)
		return 2;
	free(testRoom->north);
	free(testRoom);
	testRoom = createRoom("down!",NULL,NULL,NULL,NULL,NULL,NULL,NULL);
	setUp(testRoom, createRoom("up!",NULL,NULL,NULL,NULL,NULL,NULL,testRoom));
	if (strcmp(testRoom->up->desc, "up!") != 0 || strcmp(testRoom->up->down->desc, "down!") != 0)
		return 3;
	free(testRoom->up);
	free(testRoom);
	printf("Testing Complete, no obvious issues\n");
	return 0;
}
#endif