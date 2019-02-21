#include <stdio.h>
#include <stdlib.h>
#include "rooms.h"
#include "items.h"

//Initialize the game's 8 Rooms and return an array of the 8 rooms
Room **resetRooms() {
	//some code
}

int main() {
	//Create and connect rooms
	Room *rooms[8] = resetRooms();
	
	deleteRooms(rooms, 8);
	return 0;
}
