#include <stdio.h>
#include <stdlib.h>
#include "rooms.h"
#include "items.h"

//Initialize the game's 8 Rooms and return an array of the 8 rooms
Room **resetRooms() {
	//some code that creates rooms
	Room **rooms = malloc(8 * sizeof(Room));
	return rooms;
}

int main() {
	//Create and connect rooms
	Room **rooms;
	int roomsArrLength = 8;
	rooms = resetRooms();
	
	deleteRooms(rooms, 8);
	rooms = NULL;
	return 0;
}
