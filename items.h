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
