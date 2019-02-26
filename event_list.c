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

void addToList(EventList *list, KeyEvent data) {
	Node *node = newNode(list->head, data);
	node->next = list->head;
	list->head = node;
	if (list->tail == NULL)
		list->tail = list->head;
	list->size++;
}

//frees a list pointer as well as its nodes
void deleteList(EventList *list){
	deleteNodes(list->head);
	free(list);
	list = NULL;
}
static void deleteNodes(Node *node) {
	if (node != NULL) {
		deleteNodes(node->next);
		free(node);
	}
}