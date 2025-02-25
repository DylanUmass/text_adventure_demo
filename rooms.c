#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rooms.h"
#include "event_list.h"

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
	newRoom->events = createEList(); //creates empty list, events should be added manually
	return newRoom;
}

//deletes all rooms in an array of rooms, and frees their inventories and events
void deleteRooms(Room **rooms, int length){
	for (int i = 0; i < length; i++) {
		deleteEList(rooms[i]->events);
		freeInventory(rooms[i]->items);
		free(rooms[i]);
		rooms[i] = NULL;
	}
}

//Connects a given room to another room in each direction
void setNorth(Room *current, Room *toAdd) {
	if (current == NULL)
		fprintf(stderr, "The room you're trying to modify is NULL\n");
	else
		current->north = toAdd;
}
void setSouth(Room *current, Room *toAdd) {
	if (current == NULL)
		fprintf(stderr, "The room you're trying to modify is NULL\n");
	else
		current->south = toAdd;
}
void setEast(Room *current, Room *toAdd) {
	if (current == NULL)
		fprintf(stderr, "The room you're trying to modify is NULL\n");
	else
		current->east = toAdd;
}
void setWest(Room *current, Room *toAdd) {
	if (current == NULL)
		fprintf(stderr, "The room you're trying to modify is NULL\n");
	else
		current->west = toAdd;
}
void setUp(Room *current, Room *toAdd) {
	if (current == NULL)
		fprintf(stderr, "The room you're trying to modify is NULL\n");
	else
		current->up = toAdd;
}
void setDown(Room *current, Room *toAdd) {
	if (current == NULL)
		fprintf(stderr, "The room you're trying to modify is NULL\n");
	else
		current->down = toAdd;
}

//Adds an item to a room
void addRoomItem(Room *room, Item item) {
	int index = getItemIndex(item.name, room->items);
	if (index == -1) //Item is not already in room
		addItem(item, room->items);
	else
		fprintf(stderr, "Item is already in Room\n");
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

		Room *rooms[2];
		int roomsArrLength = 2;
		rooms[0] = testRoom;
		rooms[1] = testRoom->up;
		if (strcmp(rooms[0]->desc, "down!") != 0 || strcmp(rooms[1]->desc, "up!") != 0)
			return 4;
		deleteRooms(rooms, roomsArrLength);
		if (rooms[0] != NULL || rooms[1] != NULL)
			return 5;

		printf("Testing Complete, no obvious issues\n");
		return 0;
	}
#endif