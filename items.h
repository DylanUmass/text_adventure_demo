#ifndef _ITEMS_H
#define _ITEMS_H
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
Inventory* createInv(char* name, int maxSize);
Item createItem(char* name, char* description);
_Bool compareItem(char* name, Item itm);
_Bool compareInv(char* name, Inventory* inv);
int getItemIndex(char *name, Inventory* inv);
int removeItem(char* name, Inventory* inv);
int addItem(Item itm, Inventory* inv);
void printItem(Item itm);
void printInventory(Inventory* inv);
Item getItem(char* name, Inventory* inv);
Item takeItem(char* name, Inventory* inv);
int swapItem(char* itmName, Inventory* src, Inventory* dest);
void freeInventory(Inventory* inv);
#endif
