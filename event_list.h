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


EventList *newEList();

int getSize(EventList *list);

void addToFront(EventList *list, KeyEvent *event);

void deleteList(EventList *list);

#endif
