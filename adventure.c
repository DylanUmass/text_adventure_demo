#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rooms.h"
#include "items.h"
#include "event_list.h"
#define DEBUG 1

//Typedefs
typedef struct Player Player;

//A struct to represent the player. Has a field for a name that the player chooses, an inventory, and a current room.
struct Player {
	char* name;
	Inventory* pInv;
	Room* currentRoom;
};

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
void playerTakeItem(Player* player, char* itemName) {
	int result = swapItem(itemName, player -> currentRoom -> items, player -> pInv);
	if(result == -1) {
		printf("\nThere isn't an item in this room with that name.");
	}
}

//Lets the player drop an item from their inventory into their current room by entering the name of it.
void playerDropItem(Player* player, char* itemName) {
	int result = swapItem(itemName, player -> pInv, player -> currentRoom -> items);
	if(result == -1) {
		printf("\nYou don't have that item.");
	}
}

//Initialize the game's 8 Rooms and return an array of the 8 rooms
Room **resetRooms() {
	//some code that creates rooms goes here
	Room **rooms = malloc(8 * sizeof(Room));
	for (int i = 0; i < 8; i++) {
		rooms[i] = createRoom("blank",createInv("blank",8),NULL,NULL,NULL,NULL,NULL,NULL);
	}
	return rooms;
}

/* 	Attempts to trigger a KeyEvent in the given room with the given item
	Removes the Event from the room if successful */
void useKey(Item key, Room *currRoom) {
	KeyEvent event = getEvent(currRoom->events, key);
	if (strcmp(event.key.name, "NULL")) {
		printf("%s\n",event.desc);
		switch (event.dir) {
			case north:
				setNorth(event.startRoom, event.endRoom);
				break;
			case south:
				setSouth(event.startRoom, event.endRoom);
				break;
			case east:
				setEast(event.startRoom, event.endRoom);
				break;
			case west:
				setWest(event.startRoom, event.endRoom);
				break;
			case up:
				setUp(event.startRoom, event.endRoom);
				break;
			case down:
				setDown(event.startRoom, event.endRoom);
				break;
		}
		if (deleteEvent(currRoom->events, event) == 0)
			fprintf(stderr, "Failed to remove %s event from list\n",event.key.name);
	}
	else
		printf("%s cannot be used here.\n", key.name);
}

int main() {
	//Create and connect rooms
	Room **rooms;
	int roomsArrLength = 8;
	rooms = resetRooms();
	
	deleteRooms(rooms, 8);
	rooms = NULL;


	#ifdef DEBUG
		Room *start = createRoom("start", createInv("inventory", 8),NULL,NULL,NULL,NULL,NULL,NULL);
		Room *end = createRoom("end", createInv("inventory", 8),NULL,NULL,NULL,NULL,NULL,NULL);
		Item newItem = createItem("item", "desc");
		if (addItem(newItem,start->items) == -1)
			return 1;
		if (getItemIndex("item",start->items) == -1)
			return 2;
		addEvent(start->events, createEvent(newItem, start, down, end, "start->down->end"));
		if (start->events->size != 1)
			return 3;
		if (strcmp(start->events->head->data.key.name,"item") != 0)
			return 4;
		if (strcmp(getEvent(start->events, newItem).key.name, "item") != 0)
			return 5;
		printf("%s\n", getEvent(start->events, newItem).key.name);
		if (strcmp(getEvent(start->events, createItem("DSFSDF","Dargon_sximitar")).key.name, "NULL") != 0)
			return 6;
		useKey(newItem,start);
		if (start->down != end)
			return 7;

	#endif
	return 0;
}
