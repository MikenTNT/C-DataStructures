/*
 *	Author: MikenTNT
 */
#include <stdio.h>
#include <stdlib.h>

#include "queue.h"


static int isEmpty(const Queue *queue);
static void freeNode(queueNodeRef p);
static queueNodeRef newNode(queueData data);
static void firstNode(Queue *queue, queueData data);

/**
 * To use this queue you will need this elements.
	Queue *queue;
	int *data;

	To push data reserve memory for the data pointer.
	Make sure free data pointer after pulling and using the data.
 */


/**
 * Initializes the queue pointer and its data.
 */
Queue * newQueue()
{
	Queue *queue;

	// Reserve memory for the queue.
	if ((queue = (Queue *)malloc(sizeof(Queue))) == NULL) {
		perror("Unable to reserve memory.");
		exit(151);
	}

	// Initializes the data.
	queue->first = NULL;
	queue->last = NULL;
	queue->size = 0;

	return queue;
}

/**
 * Frees the queue data and its pointer.
 */
void freeQueue(Queue *queue)
{
	if (!isEmpty(queue))  queueRemoveAll(queue);

	free(queue);
}

/**
 * Checks if the queue is empty.
 */
static int isEmpty(const Queue *queue)
{
	return (queue->first == NULL);
}

/**
 * Frees the node data and its pointer.
 */
static void freeNode(queueNodeRef p)
{
	free(p->data);
	free(p);
}

/**
 * Creates a new node and set the data data.
 */
static queueNodeRef newNode(queueData data)
{
	queueNodeRef node;

	// Reserve memory for the node.
	if ((node = (queueNodeRef)malloc(sizeof(node))) == NULL) {
		perror("Unable to reserve memory.");
		exit(151);
	}

	// Initializes the data.
	node->next = NULL;
	node->data = data;

	return node;
}

/**
 * Set the first node of the queue.
 */
static void firstNode(Queue *queue, queueData data)
{
	queueNodeRef node = newNode(data);

	queue->first = node;
	queue->last = node;

	(queue->size)++;
}

/**
 * Push data in the queue.
 * IF: the queue is empty creates a new node.
 */
void queuePush(Queue *queue, queueData data)
{
	if (isEmpty(queue)) {
		firstNode(queue, data);
		return;
	}

	queueNodeRef node = newNode(data);

	queue->last->next = node;
	queue->last = node;

	(queue->size)++;
}

/**
 * Pull data of the queue.
 */
queueData queuePull(Queue *queue)
{
	if (isEmpty(queue))  return NULL;

	queueNodeRef temp;
	queueData data;

	temp = queue->first;
	data = temp->data;

	if (queue->first == queue->last) {
		queue->first = NULL;
		queue->last = NULL;
	}
	else {
		queue->first = queue->first->next;
	}

	free(temp);

	(queue->size)--;

	return data;
}

/**
 * Frees and removes all nodes, and reset the queue data.
 */
void queueRemoveAll(Queue *queue)
{
	if (isEmpty(queue))  return;

	queueNodeRef temp;

	while(queue->first != NULL) {
		temp = queue->first;
		queue->first = queue->first->next;
		freeNode(temp);
	}

	queue->size = 0;
}
