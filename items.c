#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "items.h"

//Creates an item with the given name and description, and returns it.
item createItem(char* name, char* description) {
	item newItem = {name, description};
	return newItem;
}

//Null item. Returned by functions that return an item when there is an error.
item nullItem = {"", ""};

//Creates an inventory with the given name and max size, and dynamically allocates memory for items.
inventory* createInv(char* name, int maxSize) {
	item* items = (item*) malloc(maxSize * sizeof(item));
	inventory* invPnt = (inventory*) malloc(sizeof(inventory));
	inventory newInv = {name, 0, maxSize, items};
	(*invPnt) = newInv;
	return invPnt;
}

//Compares a name to an item. Returns 0 if the item has that name.
_Bool compareItem(char* name, item itm) {
	return strcmp(name, itm.name);
}

//Compares a name to an inventory. Returns 0 if the inventory has that name.
_Bool compareInv(char* name, inventory* inv) {
	return strcmp(name, inv -> name);
}

//Checks to see if an item with the given name exists in the given inventory. Returns the index if so, otherwise -1.
int contains(char* name, inventory* inv) {
	for(int i = 0; i < inv -> numItems; i++) {
		item currItem = inv -> items[i];
		if(compareItem(name, currItem) == 0) {
			return i;
		} 
	}
	return -1;
}

//Removes an item with the given name from the given inventory. Returns 0 if successful, or -1 if the item wasn't found in the inv.
int removeItem(char* name, inventory* inv) {
	int index = contains(name, inv);
	if(index == -1) {return -1;}
	else {
		for(int i = index; i < inv -> numItems - 2; i++) {
			inv -> items[i] = inv -> items[i + 1];
		}
		inv -> numItems--;
		inv -> items[inv -> numItems] = nullItem;
	}
	return 0;
}

//Adds a given item to the given inventory. Returns 0 if it was added successfully, or -1 if inv is full.
int addItem(item itm, inventory* inv) {
	if(inv -> numItems == inv -> maximumSize) {
		return -1;
	}
	else {
		inv -> items[inv -> numItems] = itm;
		inv -> numItems++;
	}
	return 0;
}

//Prints an item in the form <itemname>: <itemdescription>
void printItem(item itm) {
	printf("%s: %s\n", itm.name, itm.description);
}

//Prints all of the items in the given inventory in the form <itemname>: <itemdescription>
void printInventory(inventory* inv) {
	printf("%s's Contents:\n\n", inv -> name);
	for(int i = 0; i < inv -> numItems; i++) {
		printf("%i. ", i + 1);
		printItem(inv -> items[i]);
	}
}

//Returns an item from an inventory with the given name, or NULL if that item doesn't exist in the inventory.
item getItem(char* name, inventory* inv) {
	int index = contains(name, inv);
	if(index == -1) {
		return nullItem;
	}
	return inv -> items[index];
}

//Given a name, returns an item from the given inventory with that name, and then removes that item. Returns NULL if item not found.
item takeItem(char* name, inventory* inv) {
	item itm = getItem(name, inv);
	if(compareItem("", itm) == 0) {return nullItem;}
	removeItem(name, inv);
	return itm;
}

//Frees an inventory's location in memory, along with all its associated items.
void freeInventory(inventory* inv) {
	free(inv -> items);
	free(inv);
}

int main() {
	item sword = createItem("Silver Sword", "A large silver sword with a ruby.");
	item potion = createItem("Blue Potion", "A blue potion in a tall glass beaker.");
	item key = createItem("Rusty Key", "A rusty iron key to a jail lock.");
	inventory* chest = createInv("Wooden Chest", 10);
	addItem(sword, chest);
	addItem(potion, chest);
	addItem(key, chest);
	printInventory(chest);
	printf("--------\n");
	item keyAlias = takeItem("Rusty Key", chest);
	item invalid = takeItem("Rusty Key", chest);
	printItem(keyAlias);
	printf("--------\n");
	printInventory(chest);
	printf("--------\n");
	removeItem("Blue Potion", chest);
	for(int i = 0; i < 20; i++) {
		addItem(sword, chest);
	}
	printInventory(chest);
	printf("--------\n");
	for(int i = 0; i < 10; i++) {
		removeItem("Silver Sword", chest);
	}
	printInventory(chest);
	freeInventory(chest);
	return 0;
}
