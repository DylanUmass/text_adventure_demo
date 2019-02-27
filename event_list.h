#ifndef EVENT_LIST_H
#define EVENT_LIST_H
#include "rooms.h"

typedef struct node Node;
struct node 
	{
		KeyEvent data;
		Node *next;
	};

typedef struct eventList EventList;
struct eventList
	{
		Node *head;
		Node *tail;
		int size;
	};

//creates and new EventList
EventList *newEList();
//returns the size of the list
int getSize(EventList *list);
//Adds the given event to the front of the given EventList
void addToFront(EventList *list, KeyEvent *event);
//Returns 1 if the given list contains the given event, 0 otherwise
_Bool containsEvent(EventList *list, KeyEvent event);
//frees the given list pointer and sets it to NULL
void deleteList(EventList *list);
//frees and removes the given KeyEvent from the given EventList, returns 0 if the event does not exist
_Bool deleteEvent(EventList *list, KeyEvent event);

#endif
