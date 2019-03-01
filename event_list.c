#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "event_list.h"
//#define DEBUG 1

EventList *createEList() {
	EventList *listPtr = malloc(sizeof(EventList));
	if (listPtr == NULL)
		fprintf(stderr, "Failed to allocate memory\n");
	listPtr->head = NULL;
	listPtr->tail = NULL;
	listPtr->size = 0;
	return listPtr;
}

static Node *newNode(Node *next, KeyEvent data) {
	Node *nodePtr = malloc(sizeof(Node));
	if (nodePtr == NULL)
		fprintf(stderr, "Failed to allocate memory\n");
	nodePtr->data = data;
	nodePtr->next = next;
	return nodePtr;
}

//Creates a new KeyEvent
KeyEvent createEvent(Item key, Room *startRoom, Direction dir, Room *endRoom, char *desc, char *newDesc) {
	KeyEvent newEvent = (KeyEvent) {key, startRoom, dir, endRoom, desc, newDesc};
	return newEvent;
}

int getSize(EventList *list) {
	return list->size;
}

/* 	Returns the KeyEvent associated with the given item if it exists in the given list,
	If there is no event associated, then it returns a KeyEvent with an Item.name equal to "NULL" */ 
KeyEvent getEvent(EventList *list, Item item) {
	for (Node *curr = list->head; curr != NULL; curr = curr->next) {
		if (strcmp(item.name, curr->data.key.name) == 0) {
			return curr->data;
		}
	}
	KeyEvent noEvent;
	noEvent.key.name = "NULL";
	return noEvent;
}

//Adds the given KeyEvent to the given EventList
void addEvent(EventList *list, KeyEvent data) {
	Node *node = newNode(list->head, data);
	node->next = list->head;
	list->head = node;
	if (list->tail == NULL)
		list->tail = list->head;
	list->size++;
}

//helper for deleteList
static void deleteNodes(Node *node) {
	if (node != NULL) {
		deleteNodes(node->next);
		free(node);
	}
}
//frees a list pointer as well as its nodes
void deleteEList(EventList *list){
	deleteNodes(list->head);
	free(list);
	list = NULL;
}

//Checks if two KeyEvents have the same data
_Bool keyEventIsEquals(KeyEvent event1, KeyEvent event2) {
	return (compareItem(event1.key.name, event2.key) == 0 
				&& event1.startRoom == event2.startRoom
					&& event1.endRoom == event2.endRoom
						&& event1.dir == event2.dir);
}

//frees and removes the given KeyEvent from the given EventList, returns 0 if the event does not exist
_Bool deleteEvent(EventList *list, KeyEvent event) {
	Node *prev = NULL;
  	Node *curr = list->head;
  	if (keyEventIsEquals(curr->data, event)){
    	list->head = list->head->next;
 		free(curr);
		list->size--;
    	return 1;
  	} 
  	while (curr != NULL) {
    	if (keyEventIsEquals(curr->data, event)) {
      		prev->next = curr->next;
      		free(curr);
			list->size--;
      		return 1;
    	}
    	prev = curr;
    	curr = curr->next;
  	}
  	return 0;
}

#ifdef DEBUG
	//some testing
	int main() {
		EventList *list = createEList();
		if (list->head != NULL || list->tail != NULL || getSize(list) != 0)
			return 1;
		Room *room1 = createRoom("r1",createInv("invName",8),NULL,NULL,NULL,NULL,NULL,NULL);
		Room *room2 = createRoom("r2",createInv("invName2",8),NULL,NULL,NULL,NULL,NULL,NULL);
		KeyEvent myEvent = createEvent(createItem("iName","iDesc"),room1,north,room2,"eDesc");
		KeyEvent copy = myEvent;
		if (keyEventIsEquals(myEvent,copy) == 0)
			return 2;
		addEvent(list, myEvent);
		if (strcmp(getEvent(list, createItem("iName","")).key.name,"iName")){
			return 3;
		}
		if (deleteEvent(list,myEvent) == 0)
			return 4;
		if (strcmp(getEvent(list, myEvent.key).key.name,"NULL")){
			return 5;
		}
	}
#endif