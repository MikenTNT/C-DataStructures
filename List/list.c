/*
 *	Author: MikenTNT
 */
#include <stdio.h>
#include <stdlib.h>

#include "list.h"


static int isEmpty(const List *list);
static void freeNode(listNodeRef p);
static listNodeRef newNode(listData data);
static void firstNode(List *list, listData data);

/**
 * To use this list you will need this elements.
	List *list;
	listNodeRef node, temp;
	int *data;

	To insert data reserve memory for the data pointer.
 */


/**
 * Initializes the linked list pointer and its data.
 */
List * newList()
{
	List *list;

	// Reserve memory for the list.
	if ((list = (List *)malloc(sizeof(List))) == NULL) {
		perror("Unable to reserve memory.");
		exit(151);
	}

	// Initializes the data.
	list->first = NULL;
	list->last = NULL;
	list->size = 0;

	return list;
}

/**
 * Frees the linked list data and its pointer.
 */
void freeList(List *list)
{
	if (!isEmpty(list))  listRemoveAll(list);

	free(list);
}

/**
 * Checks if the linked list is empty.
 */
static int isEmpty(const List *list)
{
	return (list->first == NULL);
}

/**
 * Frees the node data and its pointer.
 */
static void freeNode(listNodeRef p)
{
	free(p->data);
	free(p);
}

/**
 * Creates a new node and set the data data.
 */
static listNodeRef newNode(listData data)
{
	listNodeRef node;

	// Reserve memory for the node.
	if ((node = (listNodeRef)malloc(sizeof(node))) == NULL) {
		perror("Unable to reserve memory.");
		exit(151);
	}

	// Initializes the data.
	node->prev = NULL;
	node->next = NULL;
	node->data = data;

	return node;
}

/**
 * Set the first node of the list.
 */
static void firstNode(List *list, listData data)
{
	listNodeRef node = newNode(data);

	list->first = node;
	list->last = node;

	(list->size)++;
}

/**
 * Creates and inserts a new node before another node.
 * IF: the list is empty creates a new node.
 */
void listInsertBefore(List *list, listData data, listNodeRef p)
{
	if (isEmpty(list)) {
		firstNode(list, data);
		return;
	}

	listNodeRef node = newNode(data);

	node->prev = p->prev;
	node->next = p;
	if (p->prev != NULL)  p->prev->next = node;
	p->prev = node;

	if (list->first == p)  list->first = node;

	(list->size)++;
}

/**
 * Replaces the node data.
 * IF: the list is empty creates a new node.
 */
void listInsertNode(List *list, listData data, listNodeRef p)
{
	if (isEmpty(list)) {
		firstNode(list, data);
		return;
	}

	free(p->data);
	p->data = data;
}

/**
 * Creates and inserts a new node after another node.
 * IF: the list is empty creates a new node.
 */
void listInsertAfter(List *list, listData data, listNodeRef p)
{
	if (isEmpty(list)) {
		firstNode(list, data);
		return;
	}

	listNodeRef node = newNode(data);

	node->prev = p;
	node->next = p->next;
	if (p->next != NULL)  p->next->prev = node;
	p->next = node;

	if (list->last == p)  list->last = node;

	(list->size)++;
}

/**
 * Remove one node of the list.
 */
void listRemoveNode(List *list, listNodeRef p)
{
	if (isEmpty(list))  return;

	if ((list->first == p) && (list->last == p)) {
		list->first = NULL;
		list->last = NULL;
	}
	else if (list->first == p) {
		list->first = p->next;
		p->next->prev = NULL;
	}
	else if (list->last == p) {
		list->last = p->prev;
		p->prev->next = NULL;
	}
	else {
		p->prev->next = p->next;
		p->next->prev = p->prev;
	}

	freeNode(p);

	(list->size)--;
}

/**
 * Frees and removes all nodes, and reset the list data.
 */
void listRemoveAll(List *list)
{
	if (isEmpty(list))  return;

	listNodeRef temp;

	while(list->first != NULL) {
		temp = list->first;
		list->first = list->first->next;
		freeNode(temp);
	}

	list->last = NULL;
	list->size = 0;
}
