#ifndef _ITEMS_H
#define _ITEMS_H
//The item. Has a field for a name and a description.
struct Item {
	char* name;
	char* description;
};

//The inventory. Has a field for a name, the current number of items, the max # of items it can hold, and a pointer to items.
//Inventory will be used for rooms and player.
struct Inventory {
	char* name;
	int numItems;
	int maximumSize;
	struct Item* items;
};

//Typedefs for item and inventory structs.
typedef struct Item Item;
typedef struct Inventory Inventory;

//Function prototypes
int addItem(Item itm, Inventory* inv);
int contains(char *name, Inventory* inv);
#endif
