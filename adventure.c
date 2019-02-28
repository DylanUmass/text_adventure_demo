#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rooms.h"
#include "items.h"
#include "event_list.h"

//Typedefs
typedef struct Player Player;

//A struct to represent the player. Has a field for an inventory, and a current room.
struct Player {
	Inventory* pInv; //Inventory
	Room* currentRoom; //Current room
};

//Returns a pointer to a player struct. 
Player* createPlayer() {
	Player* newPlayerPnt = (Player*) malloc(sizeof(Player));
	Player newPlayer = {createInv("Your Inventory", 25), NULL}; 
	(*newPlayerPnt) = newPlayer;
	return newPlayerPnt;
}

//Frees a player struct from memory
void freePlayer(Player* player) {
	freeInventory(player -> pInv);
	free(player);
}

/* 	Attempts to trigger a KeyEvent in the given room with the given item.
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

//Lets the player take an item from their current room.
void playerTakeItem(Player* player, char* itemName) {
	int result = swapItem(itemName, player -> currentRoom -> items, player -> pInv); //Result is -1 if item isn't in room
	if(result == -1) {
		printf("\nThere isn't an item in this room with that name.");
	}
}

//Lets the player drop an item from their inventory into their current room.
void playerDropItem(Player* player, char* itemName) {
	int result = swapItem(itemName, player -> pInv, player -> currentRoom -> items); //Result is -1 if item not in player inventory
	if(result == -1) {
		printf("\n\nYou don't have that item.");
	}
}

//Lets the player view the items in their current room.
void playerViewRoomItems(Player* player) {
	printf("\n\n");
	printInventory(player -> currentRoom -> items);
}

//Lets the player view their inventory.
void playerViewInventory(Player* player) {
	printf("\n\n");
	printInventory(player -> pInv);
}

//Attempts to have the player use an item
void playerUseItem(Player* player, char* itemName) {
	int itemIndex = getItemIndex(itemName,player->pInv);
	if (itemIndex != -1) {
		useKey(player->pInv->items[itemIndex], player->currentRoom);
		return;
	}
	printf("You do not have that item.\n");
}

//Attempts to move the player to a new room in the given direction 
void playerChangeRoom(Player* player, char *dir) {
	Room *newRoom = NULL;
	
	if(strcmp(dir, "north") == 0) 
		newRoom = player->currentRoom->north;
	else if(strcmp(dir, "south") == 0)
		newRoom = player->currentRoom->south;
	else if(strcmp(dir, "east") == 0)
		newRoom = player->currentRoom->east;
	else if(strcmp(dir, "west") == 0)
		newRoom = player->currentRoom->west;
	else if(strcmp(dir, "up") == 0)
		newRoom = player->currentRoom->up;
	else if(strcmp(dir, "down") == 0)
		newRoom = player->currentRoom->down;

	if (newRoom != NULL)
	{
		player->currentRoom = newRoom;
		return;
	}
	printf("You cannot go that direction\n");
}

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

//Initialize the game's 8 Rooms, sets up the rooms and items within them, and return an array of the 8 rooms
Room **resetRooms() {
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
	
	//Events
	addEvent(rooms[0] -> events, createEvent(bat, rooms[0], south, rooms[1], "You smashed open the door with the bat!"));
	addEvent(rooms[1] -> events, createEvent(pliers, rooms[1], up, rooms[4], "You cut the lock with the pliers!"));
	addEvent(rooms[5] -> events, createEvent(chem, rooms[5], east, rooms[6], "You melted the wall with acid!"));
	addEvent(rooms[4] -> events, createEvent(labnotes, rooms[4], south, rooms[7], "You unlocked the door with the passcode!"));
	addEvent(rooms[4] -> events, createEvent(liftkey, rooms[4], up, rooms[8], "You activated the lift with the lift key!"));
	
	return rooms;
}

//Splits a player's input into a command and the object of said command
char** splitInput(char* input) {
	char** tokens = (char**) malloc(sizeof(char*) * 2);
	int i;
	for(i = 0; input[i] != ' ' && input[i] != '\0'; i++) {
		(*tokens)[i] = input[i];
	}
	i++;
	(*tokens)[i] = '\0';
	if(input[i] == '\0') {
		(*tokens + 1)[0] = '\0';
		return tokens;
	}
	int j;
	for(j = 0; input[i] != ' ' && input[i] != '\0'; j++) {
		(*tokens + 1)[j] = input[i];
		i++;
	}
	(*tokens + 1)[j + 1] = '\0';
	return tokens;
}

int main() {
	//Create and connect rooms
	Room **rooms;
	int roomsArrLength = 9;
	rooms = resetRooms();
	
	printf("\n\nYou awaken with a start. You're not sure WHHAATTT happened last night, but you seem to be in the basement of some kind of laboratory.");
	printf("\n\nYou take a look at the room around you.");
	

	Player* player = createPlayer();
	player -> currentRoom = rooms[0];
	_Bool gameOver = 0; 
	
	while(gameOver == 0) {
		if(player -> currentRoom == rooms[8]) {
			gameOver = 1;
			continue;
		}
		printf("\n\n%s", player -> currentRoom -> desc);
		char* playerInput = (char*) calloc(100, sizeof(char));
		printf("\n\nPlease type a command: ");
		scanf("%s", playerInput);
		printf("1");
		char** tokens = splitInput(playerInput);
		printf("1");
		if(strcmp(tokens[0], "take") == 0) {
			playerTakeItem(player, tokens[1]);
		}
		else if(strcmp(tokens[0], "drop") == 0) {
			playerDropItem(player, tokens[1]);
		}
		else if(strcmp(tokens[0], "look") == 0) {
			printf("1");
			playerViewRoomItems(player);
		}
		else if(strcmp(tokens[0], "inv") == 0) {
			playerViewInventory(player);
		}
		else if(strcmp(tokens[0], "use") == 0) {
			playerUseItem(player, tokens[0]);
		}
		else if(strcmp(tokens[0], "move") == 0) {
			//playerChangeRoom(player, tokens[1]);
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
		free(tokens);
	} 
	printf("\n\nYou escaped!");
	printf("\n\nThank you for playing!");
	freePlayer(player);
	player = NULL;
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
