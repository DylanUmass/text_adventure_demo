#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rooms.h"
#include "items.h"

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

//Frees a player struct from memory
void freePlayer(Player* player) {
	freeInventory(player -> pInv);
	free(player);
}

//Lets the player take an item from their current room by entering the name of it.
void playerTakeItem(Player* player, char* itemName) {
	int result = swapItem(itemName, player -> currentRoom -> items, player -> pInv);
	if(result == -1) {
		printf("\n\nThere isn't an item in the room with that name.");
	}
}

//Lets the player drop an item from their inventory into their current room by entering the name of it.
void playerDropItem(Player* player, char* itemName) {
	int result = swapItem(itemName, player -> pInv, player -> currentRoom -> items);
	if(result == -1) {
		printf("\n\nYou don't have that item.");
	}
}

//Lets the player view the items in their current room
void playerViewRoomItems(Player* player) {
	printf("\n\n");
	printInventory(player -> currentRoom -> items);
}

//Lets the player view their inventory.
void playerViewInventory(Player* player) {
	printf("\n\n");
	printInventory(player -> pInv);
}

//TBD
void playerUseItem(Player* player, char* itemName) {}

//TBD 
void playerChangeRoom(Player* player, char* itemName) {}

//Prints the list of commands the player can use.
void printCommandList() {
	printf("\n\nCommand list:");
	printf("\nt <itemname>: Take an item from the room you're in."); 
	printf("\nd <itemname>: Drop an item into the room you're in.");
	printf("\nl: Look at the items in the room.");
	printf("\ni: Look at your inventory.");
	printf("\nu <itemname>: Use an item on your current room.");
	printf("\nm <direction>: Move to a different room.");
	printf("\nh: Prints the command list.");
	printf("\nq: Quit the game.");
}

//Gets the object the user wants to use with a command from the command input
char* getObject(char* userInput) {
	if(userInput[1] != ' ') {
		return '\0';
	}
	char* object = (char*) malloc(sizeof(char) * 30);
	int i;
	for(i = 0; userInput[i + 2] != '\0'; i++) {
		object[i] = userInput[i + 2];
	}
	object[i + 1] = '\0';
	return object;
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

	Player* player = createPlayer();
	_Bool gameOver = 0; //This controls when the main game loop ends (when game is finished).
	
	//The main while loop for the game.
	while(gameOver == 0) {
		char* userInput;
		printf("\n\nType what you would like to do: ");
		scanf("%s", userInput);
		//Checking for valid user input (command followed by object if needed).
		if(userInput[0] == '\0') {
			printf("\n\nInvalid action. Type 'h' to get a list of actions.");
			continue;
		}
		//First letter of input should be the command type.
		char command = userInput[0];
		switch(command) {
			case 't': //Take item
				playerTakeItem(player, getObject(userInput));
				break;
			case 'd': //Drop item
				playerDropItem(player, getObject(userInput));
				break;
			case 'l': //Look at room's items
				playerViewRoomItems(player);
				break;
			case 'i': //Look at inventory
				playerViewInventory(player);
				break;
			case 'u': //Use item on current room
				playerUseItem(player, getObject(userInput));
				break;
			case 'm': //Move to different room
				playerChangeRoom(player, getObject(userInput));
				break;
			case 'h': //Look at commands
				printCommandList();
				break;
			case 'q': //Quit game
				printf("\n\nBye for now!");
				exit(0);
				break;
		}		
	}
	printf("\n\nThank you for playing!");
	deleteRooms(rooms, 8);
	rooms = NULL;
	return 0;
}
