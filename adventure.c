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
	printf("\nPlease enter your name: ");
	scanf("%s", name);
	Player* newPlayerPnt = (Player*) malloc(sizeof(Player));
	char* namecpy;
	strcpy(namecpy, name);
	Player newPlayer = {name, createInv(strcat(namecpy, "'s Inventory"), 25), NULL}; //Player can hold max 25 items
	(*newPlayerPnt) = newPlayer;
	return newPlayerPnt;
}

//Lets the player view their inventory.
void playerViewInventory(Player* player) {
	printf("\n\n");
	printInventory(player -> pInv);
}

void playerViewRoomItems(Player* player) {
	printf("\n\n");
	printInventory(player -> currentRoom -> items);
}

//Lets the player take an item from their current room by entering the name of it.
void playerTakeItem(Player* player) {
	char* itemName;
	printf("\nSelect an item to take: ");
	scanf("%s", itemName);
	int result = swapItem(itemName, player -> currentRoom -> items, player -> pInv);
	if(result == -1) {
		printf("\nNo item in the room with that name.");
	}
}

//Lets the player drop an item from their inventory into their current room by entering the name of it.
void playerDropItem(Player* player) {
	char* itemName;
	printf("\nSelect an item to drop: ");
	scanf("%s", itemName);
	int result = swapItem(itemName, player -> pInv, player -> currentRoom -> items);
	if(result == -1) {
		printf("\nYou don't have that item.");
	}
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
