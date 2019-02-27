#include <stdio.h>
#include <stdlib.h>
#include "event_list.h"

EventList *newEList() {
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

int getSize(EventList *list) {
	return list->size;
}

//Returns 0 if the given list contains the given KeyEvent, 1 otherwise
_Bool containsEvent(EventList *list, KeyEvent event) {
	for (Node *curr = list->head; curr != NULL; curr = curr->next) {
		if (keyEventIsEquals(curr->data, event))
			return 1;
	}
	return 0;
}

//Adds the given KeyEvent to the given EventList
void addToList(EventList *list, KeyEvent data) {
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
void deleteList(EventList *list){
	deleteNodes(list->head);
	free(list);
	list = NULL;
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