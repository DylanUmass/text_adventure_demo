#ifndef ITEMS_H
#define ITEMS_H
//The item. Has a field for a name and a description.
struct Item {
	char* name; //Name of the item
	char* description; //Description of item
};

//The inventory. Has a field for a name, the current number of items, the max # of items it can hold, and a pointer to items.
//Inventory will be used for rooms and player.
struct Inventory {
	char* name; //Name of inv
	int numItems; //# of items currently in inv 
	int maximumSize; //Maximum amount of items inv can hold
	struct Item* items; //Pointer for array of items
};

//Typedefs for item and inventory structs.
typedef struct Item Item;
typedef struct Inventory Inventory;

//Function prototypes

//Creates an Inventory with the given name and max size, and dynamically allocates memory for Items.
Inventory* createInv(char* name, int maxSize);
//Creates an Item with the given name and description, and returns it.
Item createItem(char* name, char* description);
//Compares a name to an Item. Returns 0 if the Item has that name.
_Bool compareItem(char* name, Item itm);
//Compares a name to an Inventory. Returns 0 if the Inventory has that name.
_Bool compareInv(char* name, Inventory* inv);
//Checks to see if an Item with the given name exists in the given Inventory. Returns the index if so, otherwise -1.
int getItemIndex(char *name, Inventory* inv);
//Removes an Item with the given name from the given Inventory. Returns 0 if successful, or -1 if the Item wasn't found in the inv.
int removeItem(char* name, Inventory* inv);
//Adds a given Item to the given Inventory. Returns 0 if it was added successfully, or -1 if inv is full.
int addItem(Item itm, Inventory* inv);
//Prints an Item in the form <itemname>: <itemdescription>
void printItem(Item itm);
//Prints all of the Items in the given Inventory in the form <itemname>: <itemdescription>
void printInventory(Inventory* inv, int maxSize);
//Returns an Item from an Inventory with the given name, or NULL if that Item doesn't exist in the Inventory.
Item getItem(char* name, Inventory* inv);
//Given a name, returns an Item from the given Inventory with that name, and then removes that Item. Returns NULL if Item not found.
Item takeItem(char* name, Inventory* inv);
//Swaps the item with the given name from the source inventory to the destination inventory. Returns -1 if swap was unsuccessful, otherwise 0.
int swapItem(char* itmName, Inventory* src, Inventory* dest);
//Frees an Inventory's location in memory, along with all its associated Items.
void freeInventory(Inventory* inv);
#endif
