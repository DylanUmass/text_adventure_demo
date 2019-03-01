#ifndef EVENT_LIST_H
#define EVENT_LIST_H
#include "rooms.h"

typedef struct node Node;
typedef struct eventList EventList;
typedef struct keyEvent KeyEvent;




/*	Holds information about an event where a "key" is used to connect one room 
	to another in a certain direction */
struct keyEvent 
	{
		Item key;
		Room *startRoom;
		Direction dir;
		Room *endRoom;
		char *desc;
		char *newDesc;
	};

struct node 
	{
		KeyEvent data;
		Node *next;
	};

struct eventList
	{
		Node *head;
		Node *tail;
		int size;
	};

//creates a new EventList
EventList *createEList();
//creates a new KeyEvent
KeyEvent createEvent(Item key, Room *startRoom, Direction dir, Room *endRoom, char *desc, char *newDesc);
//returns the size of the list
int getSize(EventList *list);
//Adds the given event to the front of the given EventList
void addEvent(EventList *list, KeyEvent event);
//frees the given list pointer and sets it to NULL
void deleteEList(EventList *list);
//frees and removes the given KeyEvent from the given EventList, returns 0 if the event does not exist
_Bool deleteEvent(EventList *list, KeyEvent event);
//Might be redundant
_Bool containsItem(EventList *list, Item item);
/* 	Returns the KeyEvent associated with the given item if it exists in the given list,
	If there is no event associated, then it returns a KeyEvent with an Item.name equal to "NULL" */ 
KeyEvent getEvent(EventList *list, Item item);

#endif
