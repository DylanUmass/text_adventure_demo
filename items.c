#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "items.h"

//Creates an item with the given name and description, and returns a pointer to it.
item* createItem(char name[25], char desciption[100]) {
	item* itmPnt = (item*) malloc(sizeOf(item));
	item newItem = {name, description};
	itmPnt[0] = newItem;
	return itmPnt;
}

//Creates an inventory with the given name and max size, and dynamically allocates memory for items.
inventory* createInv(char name[25], int maxSize) {
	item* items[maxSize];
	for(int i = 0; i < maxSize; i++) {
		items[i] = (item*) malloc(sizeOf(item*));
	}
	inventory* invPnt = (inventory*) malloc(sizeOf(inventory));
	inventory newInv = {name, 0, maximumSize, items};
	invPnt[0] = newInv;
	return invPnt;
}

//Compares a name to an item. Returns 0 if the item has that name.
_Bool compareItem(char[] name, item* itm) {
	return strcmp(name, itm -> name);
}

//Compares a name to an inventory. Returns 0 if the inventory has that name.
_Bool compareInv(char[] name, inventory* inv) {
	return strcmp(name, inv -> name);
}

//Checks to see if an item with the given name exists in the given inventory. Returns the index if so, otherwise -1.
int contains(char[] name, inventory* inv) {
	for(int i = 0; i < inv -> numItems; i++) {
		item currItem* = inv -> items[i];
		if(compareItems(name, currItem) == 0) {
			return i;
		} 
	}
	return -1;
}

//Removes an item with the given name from the given inventory. Returns 0 if successful, or -1 if the item wasn't found in the inv.
int removeItem(char[] name, inventory* inv) {
	int index = contains(name, inv);
	if(containsItem == -1) {return -1;}
	else {
		for(int i = index; i < inv -> numItems - 1; i++) {
			inv -> items[i] = inv -> items[i + 1];
		}
		inv -> items[numItems] == NULL;
		inv -> numItems--;
	}
	return 0;
}

//Adds a given item to the given inventory. Returns 0 if it was added successfully, or -1 if inv is full.
int addItem(item* itm, inventory* inv) {
	if(inv -> numItems == inv -> maximumSize) {
		return -1;
	}
	else {
		inv -> items[numItems] = itm;
		inv -> numItems++;
	}
	return 0;
}

//Prints an item in the form <itemname>: <itemdescription>
void printItem(item* itm) {
	prinf(%s: %s, itm -> name, itm -> description);
}

//Prints all of the items in the given inventory in the form <itemname>: <itemdescription>
void printInventory(inventory* inv) {
	for(int i = 0; i < inv -> numItems, i++) {
		printItem(inv -> items[i]);
		printf("\n");
	}
}

//Returns an item from an inventory with the given name, or NULL if that item doesn't exist in the inventory.
item* getItem(char[] name, inventory* inv) {
	int index = contains(name, inv);
	if(index == -1) {
		return NULL;
	}
	return inv -> items[index];
}

//Given a name, returns an item from the given inventory with that name, and then removes that item. Returns NULL if item not found.
item* takeItem(char[] name, inventory* inv) {
	item* itm = getItem(name, inv);
	if(itm == NULL) {return NULL;}
	removeItem(name, inv);
	return itm;
}

//Frees an inventory's location in memory, along with all its associated items.
void freeInventory(inventory* inv) {
	for(int i = 0; i < inv -> maximumSize; i++) {
		free(inv -> items[i]);
	}
	free(inv);
}
