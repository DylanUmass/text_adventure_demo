#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "items.h"

//Creates an Item with the given name and description, and returns a pointer to it.
Item* createItem(char name[25], char description[100]) {
	Item* newItem = malloc(sizeof(Item));
	newItem->name = name;
	newItem->description = description;
	return newItem;
}

//Creates an Inventory with the given name and max size, and dynamically allocates memory for Items.
Inventory* createInv(char name[25], int maxSize) {
	Item* items[maxSize];
	for(int i = 0; i < maxSize; i++) {
		items[i] = (Item*) malloc(sizeof(Item));
	}
	Inventory newInv = (Inventory){name, 0, maxSize items};
	Inventory* invPnt = &newInv;
	return invPnt;
}

//Compares a name to an Item. Returns 0 if the Item has that name.
_Bool compareItem(char[] name, Item* itm) {
	return strcmp(name, itm -> name);
}

//Compares a name to an Inventory. Returns 0 if the Inventory has that name.
_Bool compareInv(char[] name, Inventory* inv) {
	return strcmp(name, inv -> name);
}

//Checks to see if an Item with the given name exists in the given Inventory. Returns the index if so, otherwise -1.
int contains(char name[], Inventory* inv) {
	for(int i = 0; i < inv->numItems; i++) {
		Item *currItem = inv->items[i];
		if(compareItems(name, currItem) == 0) {
			return i;
		} 
	}
	return -1;
}

//Removes an Item with the given name from the given Inventory. Returns 0 if successful, or -1 if the Item wasn't found in the inv.
int removeItem(char[] name, Inventory* inv) {
	int index = contains(name, inv);
	if(containsItem == -1) {return -1;}
	else {
		for(int i = index; i < inv -> numItems - 1; i++) {
			inv -> items[i] = inv -> items[i + 1];
		}
	}
	return 0;
}

//Adds a given Item to the given Inventory. Returns 0 if it was added successfully, or -1 if inv is full.
int addItem(Item* itm, Inventory* inv) {
	if(inv -> numItems == inv -> maximumSize) {
		return -1;
	}
	else {
		inv -> items[numItems] = itm;
	}
	return 0;
}

//Prints an Item in the form <itemname>: <itemdescription>
void printItem(Item* itm) {
	prinf(%s: %s, itm -> name, itm -> description);
}

//Prints all of the items in the given Inventory in the form <itemname>: <itemdescription>
void printInventory(Inventory* inv) {
	for(int i = 0; i < inv -> numItems, i++) {
		printItem(inv -> items[i]);
		printf("\n");
	}
}

//Returns an Item from an Inventory with the given name, or NULL if that Item doesn't exist in the Inventory.
Item* getItem(char[] name, Inventory* inv) {
	int index = contains(name, inv);
	if(index == -1) {
		return NULL;
	}
	return inv -> items[index];
}
