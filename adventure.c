#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rooms.h"
#include "items.h"

//A struct to represent the player. Has a field for a name that the player chooses, an inventory, and a current room.
struct Player {
	char* name;
	Inventory* pInv;
	Room* currentRoom;
}

//Typedefs
typedef struct Player Player;

//Returns a pointer to a player struct with the name the user types. 
Player* createPlayer() {
	char* name;
	printf("\n\nPlease enter your name: ");
	scanf("%s", name);
	Player* newPlayerPnt = (Player*) malloc(sizeof(Player));
	char* namecpy;
	strcpy(namecpy, name);
	Player newPlayer = {name, createInv(strcat(namecpy, "'s Inventory"), 25), NULL}; //Player can hold max 25 items
	(*newPlayerPnt) = newPlayer;
	return newPlayerPnt;
}

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
