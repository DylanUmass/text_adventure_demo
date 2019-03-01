#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "items.h"

//Creates an Item with the given name and description, and returns it.
Item createItem(char* name, char* description) {
	Item newItem = {name, description};
	return newItem;
}

//Null Item. Returned by functions that return an Item when there is an error.
static const Item nullItem = {"", ""};

//Creates an Inventory with the given name and max size, and dynamically allocates memory for Items.
Inventory* createInv(char* name, int maxSize) {
	Item* items = (Item*) malloc(maxSize * sizeof(Item));
	Inventory* invPnt = (Inventory*) malloc(sizeof(Inventory));
	Inventory newInv = {name, 0, maxSize, items};
	(*invPnt) = newInv;
	return invPnt;
}

//Compares a name to an Item. Returns 0 if the Item has that name.
_Bool compareItem(char* name, Item itm) {
	return strcmp(name, itm.name);
}

//Compares a name to an Inventory. Returns 0 if the Inventory has that name.
_Bool compareInv(char* name, Inventory* inv) {
	return strcmp(name, inv -> name);
}

//Checks to see if an Item with the given name exists in the given Inventory. Returns the index if so, otherwise -1.
int getItemIndex(char* name, Inventory* inv) {
	for(int i = 0; i < inv -> numItems; i++) {
		Item currItem = inv -> items[i]; //Looks at each item to see if the names match
		if(compareItem(name, currItem) == 0) {
			return i;
		} 
	}
	return -1;
}

//Removes an Item with the given name from the given Inventory. Returns 0 if successful, or -1 if the Item wasn't found in the inv.
int removeItem(char* name, Inventory* inv) {
	int index = getItemIndex(name, inv); //Gets index of item in inv, if it exists
	if(index == -1) {return -1;}
	else {
		for(int i = index; i < inv -> numItems - 1; i++) {
			inv -> items[i] = inv -> items[i + 1]; //Moves all item entries down in the array
		}
		inv -> numItems--;
		inv -> items[inv -> numItems] = nullItem; //Sets the next open item slot to the null item 
	}
	return 0;
}

//Adds a given Item to the given Inventory. Returns 0 if it was added successfully, or -1 if inv is full.
int addItem(Item itm, Inventory* inv) {
	if(inv -> numItems == inv -> maximumSize) { //If inv is full the item can't be added
		return -1;
	}
	else {
		inv -> items[inv -> numItems] = itm; //Sets the next available item slot to the item and increments the # of items
		inv -> numItems++;
	}
	return 0;
}

//Prints an Item in the form <itemname>: <itemdescription>
void printItem(Item itm) {
	printf("%s: %s\n", itm.name, itm.description);
}

//Prints all of the Items in the given Inventory in the form <itemname>: <itemdescription>
void printInventory(Inventory* inv, int maxSize) {
	printf("%s's Contents:\n\n", inv -> name);
	for(int i = 0; i < inv -> numItems; i++) {
		if (maxSize == -1)
			printf("%i. ", i + 1);
		else
			printf("%i/%i. ", i + 1, maxSize);
		printItem(inv -> items[i]);
	}
}

//Returns an Item from an Inventory with the given name, or NULL if that Item doesn't exist in the Inventory.
Item getItem(char* name, Inventory* inv) {
	int index = getItemIndex(name, inv); //Gets the index of the item
	if(index == -1) {
		return nullItem;
	}
	return inv -> items[index]; //Returns the item
}

//Given a name, returns an Item from the given Inventory with that name, and then removes that Item. Returns NULL if Item not found.
Item takeItem(char* name, Inventory* inv) {
	Item itm = getItem(name, inv); //Gets the item to be returned
	if(compareItem("", itm) == 0) {return nullItem;} //Returns null item if getItem did
	removeItem(name, inv); //Removes the item from the inventory
	return itm;
}

//Swaps the item with the given name from the source inventory to the destination inventory. Returns -1 if swap was unsuccessful, otherwise 0.
int swapItem(char* itmName, Inventory* src, Inventory* dest) {
	Item itm = takeItem(itmName, src); //Takes the item from the source inventory
	if(compareItem("", itm) == 0) {return -1;} //Returns -1 if takeItem returned the null item
	addItem(itm, dest); //Adds the item to the dest inventory
	return 0;
}

//Frees an Inventory's location in memory, along with all its associated Items.
void freeInventory(Inventory* inv) {
	free(inv -> items);
	free(inv);
}

#ifdef DEBUG
	int main() {
		Item sword = createItem("Silver Sword", "A large silver sword with a ruby.");
		Item potion = createItem("Blue Potion", "A blue potion in a tall glass beaker.");
		Item key = createItem("Rusty Key", "A rusty iron key to a jail lock.");
		Inventory* chest = createInv("Wooden Chest", 10);
		addItem(sword, chest);
		addItem(potion, chest);
		addItem(key, chest);
		printInventory(chest);
		printf("--------\n");
		Item keyAlias = takeItem("Rusty Key", chest);
		Item invalid = takeItem("Rusty Key", chest);
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

		Inventory *testInv = createInv("Inv", 5);
		Inventory *testInv2 = createInv("Inv2",7);
		printf("testInv.name: %s\n",testInv->name);
		printf("testInv2.name: %s\n",testInv2->name);
		if (strcmp(testInv->name, "Inv") != 0 || strcmp(testInv2->name, "Inv2") != 0)
			return 2;
		testInv->name = "Inv new name";
		if (strcmp(testInv->name, "Inv new name") != 0 || strcmp(testInv2->name, "Inv2") != 0)
			return 3;
		printf("testInv.name: %s\n",testInv->name);
		printf("testInv2.name: %s\n",testInv2->name);
		return 0;
	}
#endif
