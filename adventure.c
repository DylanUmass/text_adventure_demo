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
	printf("\ntake <itemname>: Take an item from the room you're in."); 
	printf("\ndrop <itemname>: Drop an item into the room you're in.");
	printf("\nlook: Look at the items in the room.");
	printf("\ninv: Look at your inventory.");
	printf("\nuse <itemname>: Use an item on your current room.");
	printf("\nmove <direction>: Move to a different room.");
	printf("\nhelp: Prints the command list.");
	printf("\nquit: Quit the game.");
}

//Initialize the game's 8 Rooms and return an array of the 8 rooms
Room **resetRooms() {
	//some code that creates rooms
	Room **rooms = malloc(9 * sizeof(Room));
	
	//Rooms
	rooms[0] = createRoom("Beaker Storage: A dusty, dark room with beakers on shelves lining the walls. The only exit is to the South, and the door is weaky barricaded.", createInv("Beaker Storage", 25), NULL, NULL, NULL, NULL, NULL, NULL);
	rooms[1] = createRoom("Main Basement: A large, barren room. The doorway upstairs is locked with a rusty padlock, and there's open doors to the North, South, and West.", createInv("Main Basement", 25), NULL, NULL, NULL, NULL, NULL, NULL);
	rooms[2] = createRoom("Basement Office: A cramped office that looks like it's been torn apart. The exit is to the North.", createInv("Basement Office", 25), NULL, NULL, NULL, NULL, NULL, NULL);
	rooms[3] = createRoom("Breaker Room: A room lined with electrical wires. There are various boxes of tools haphazardly placed on the floor. The exit is to the East.", createInv("Breaker Room", 25), NULL, NULL, NULL, NULL, NULL, NULL);
	rooms[4] = createRoom("Atrium: A large, immaculate, dome-shaped room. There's an elevator out, but it required a lift key to use. There's also a password protected door to the South and an open door to the north.", createInv("Atrium", 25), NULL, NULL, NULL, NULL, NULL, NULL);
	rooms[5] = createRoom("Break Room: A comforable looking kitchen with a few tables scattered around. The only door is to the South, but there's a weak point in the wall to the East.", createInv("Break Room", 25), NULL, NULL, NULL, NULL, NULL, NULL);
	rooms[6] = createRoom("Chemical Lab: A large white room with a few rows of lab tables, each with various chemical mixtures on them. The exit is to the West", createInv("Chemical Lab", 25), NULL, NULL, NULL, NULL, NULL, NULL);
	rooms[7] = createRoom("Hadron Collider: A metal plated circular room with a Large Hadron Collider in the center. The exit is to the North.", createInv("Hadron Collider", 25), NULL, NULL, NULL, NULL, NULL, NULL);
  	rooms[8] = createRoom("EXIT", NULL, NULL, NULL, NULL, NULL, NULL, NULL);
	
	//Room entrances/exits
	//Room 0
	setSouth(rooms[0], rooms[1]);
	
	//Room 1
	setNorth(rooms[1], rooms[0]);
	setWest(rooms[1], rooms[3]);
	setSouth(rooms[1], rooms[2]);
	setUp(rooms[1], rooms[4]);

	//Room 2
	setNorth(rooms[2], rooms[1]);

	//Room 3
	setEast(rooms[3], rooms[1]);

	//Room 4
	setNorth(rooms[4], rooms[5]);
	setSouth(rooms[4], rooms[7]);
	setUp(rooms[4], rooms[8]);
	setDown(rooms[4], rooms[1]);

	//Room 5
	setSouth(rooms[5], rooms[4]);
	setEast(rooms[5], rooms[6]);

	//Room 6
	setWest(rooms[6], rooms[5]);

	//Room 7
	setNorth(rooms[7], rooms[4]);

	//Items
	//Room 0
	Item bat = createItem("Metal Bat", "A metal baseball bat.");
	Item beaker = createItem("Broken Beaker", "A cracked glass beaker.");
	Item chem = createItem("Acid Bottle", "A bottle full of green acid.");
	addItem(bat, rooms[0] -> items); 
	addItem(beaker, rooms[0] -> items);
	addItem(chem, rooms[0] -> items);

	//Room 1

	//Room 2
	Item pencil = createItem("Pencil", "A wooden pencil with a worn out eraser.");
	Item keycard = createItem("Keycard", "A keycard that's been snapped in half.");
	addItem(pencil, rooms[2] -> items);
	addItem(keycard, rooms[2] -> items);

	//Room 3
	Item pliers = createItem("Pliers", "A pair of steel pliers.");
	Item wire = createItem("Red Wire", "A segment of rusty wire with worn out red insulation.");
	Item fuse = createItem("Fuse", "A fuse to a standard fusebox.");
	addItem(pliers, rooms[3] -> items);
	addItem(wire, rooms[3] -> items);
	addItem(fuse, rooms[3] -> items);

	//Room 4
	Item plant = createItem("Potted Plant", "A small fern in a pot.");
	Item wallet = createItem("Wallet", "A wallet with a license inside. You can't quite make out the name on it.");
	addItem(plant, rooms[4] -> items);
	addItem(wallet, rooms[4] -> items);

	//Room 5
	Item coffee = createItem("Cold Cup of Coffee", "It looks like the owner never even took a sip.");
	Item popcorn = createItem("Box of Popcorn", "A box of microwavable popcorn bags.");
	addItem(coffee, rooms[5] -> items);
	addItem(popcorn, rooms[5] -> items);

	//Room 6
	Item volchem = createItem("Volatile Chemicals", "A beaker full of bubbling yellow liquid.");
	Item labnotes = createItem("Lab Notes", "A sheet of notes with a string of numbers written in the top margin.");
	Item glasses = createItem("Safety Glasses", "A pair of dirty glass protective eyeglasses.");
	addItem(volchem, rooms[6] -> items);
	addItem(labnotes, rooms[6] -> items);
	addItem(glasses, rooms[6] -> items);

	//Room 7
	Item liftkey = createItem("Lift Key", "The key to the atrium lift!");
	Item particles = createItem("Bouncing Particles", "A reinforced glass container with flashing particles inside that are bouncing off the walls");
	addItem(liftkey, rooms[7] -> items);
	addItem(particles, rooms[7] -> items);
	
	return rooms;
}

char** splitInput(char* input) {
	return NULL;
}

int main() {
	//Create and connect rooms
	Room **rooms;
	int roomsArrLength = 9;
	rooms = resetRooms();
	Player* player = createPlayer();
	player -> currentRoom = rooms[0];
	_Bool gameOver = 0; 
	
	while(gameOver == 0) {
		if(player -> currentRoom == rooms[8]) {
			gameOver = 1;
			continue;
		}
		printf("\n\n%s", player -> currentRoom -> desc);
		char* playerInput;
		printf("Please type a command: ");
		scanf("%s", playerInput);
		char** tokens = splitInput(playerInput);
		if(strcmp(tokens[0], "take") == 0) {
			playerTakeItem(player, tokens[1]);
		}
		else if(strcmp(tokens[0], "drop") == 0) {
			playerDropItem(player, tokens[1]);
		}
		else if(strcmp(tokens[0], "look") == 0) {
			playerViewRoomItems(player);
		}
		else if(strcmp(tokens[0], "inv") == 0) {
			playerViewInventory(player);
		}
		else if(strcmp(tokens[0], "use") == 0) {
			playerUseItem(player, tokens[0]);
		}
		else if(strcmp(tokens[0], "move") == 0) {
			playerChangeRoom(player, tokens[1]);
		}
		else if(strcmp(tokens[0], "help") == 0) {
			printCommandList();
		}
		else if(strcmp(tokens[0], "quit") == 0) {
			printf("\n\nBye for now!");
			exit(0);
		}
		else{
			printf("Invalid command.Type 'help' to see the list of commands.");
		}
		//free(tokens);
	} 
	freePlayer(player);
	deleteRooms(rooms, 8);
	rooms = NULL;
	return 0;
}
