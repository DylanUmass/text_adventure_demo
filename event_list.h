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
		Item key; //The Item that triggers the event
		Room *startRoom; //The room that will be connected to another (doesn't have to be the same room that the event takes place in)
		Direction dir; //The direction that startRoom will connect to endRoom
		Room *endRoom; //The room that startRoom will connect to after the event is triggered
		char *desc; //Text that is printed during the event
		char *newDesc; //startRoom's new description after event is triggered
	};

//A node in the keyEvent linked list
struct node 
	{
		KeyEvent data;
		Node *next;
	};

//A linked list of keyEvents
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
/* 	Returns the KeyEvent associated with the given item if it exists in the given list,
	If there is no event associated, then it returns a KeyEvent with an Item.name equal to "NULL" */ 
KeyEvent getEvent(EventList *list, Item item);

#endif
