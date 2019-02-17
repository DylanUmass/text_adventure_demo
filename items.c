#include <stdio.h>
#include <stdlib.h>

//The item. Has a field for a name and a description.
struct Item {
	char name[25];
	char description[100];
};

//The inventory. Has a field for a name, the current number of items, the max # of items it can hold, and an array of item pointers.
//Inventory will be used for rooms and player.
struct Inventory {
	char name[25];
	int numItems;
	int maximumSize;
	struct Item* items[maximumSize];
};

//Typedefs
typedef struct Item item;
typedef struct Inventory inventory;

//Creates an item with the given name and description, and returns a pointer to it.
item* createItem(char name[25], char desciption[100]) {
	item newItem = {name, description};
	item* niPnt = &newItem;
	return niPnt;
}

//Creates an inventory with the given name and max size, and dynamically allocates memory for items.
inventory* createInv(char name[25], int maxSize) {
	item* items[maxSize];
	for(int i = 0; i < maxSize; i++) {
		items[i] = (item*) malloc(sizeOf(item));
	}
	inventory newInv = {name, 0, maxSize items};
	inventory* invPnt = &newInv;
	return invPnt;
}
