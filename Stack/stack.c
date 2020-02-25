/*
 *	Author: MikenTNT
 */
#include <stdio.h>
#include <stdlib.h>

#include "stack.h"


static int isEmpty(const Stack *stack);
static void freeNode(stackNodeRef p);
static stackNodeRef newNode(stackData data);
static void firstNode(Stack *stack, stackData data);

/**
 * To use this stack you will need this elements.
	Stack *stack;
	int *data;

	To push data reserve memory for the data pointer.
	Make sure free data pointer after pulling and using the data.
 */


/**
 * Initializes the stack pointer and its data.
 */
Stack * newStack()
{
	Stack *stack;

	// Reserve memory for the stack.
	if ((stack = (Stack *)malloc(sizeof(Stack))) == NULL) {
		perror("Unable to reserve memory.");
		exit(151);
	}

	// Initializes the data.
	stack->first = NULL;
	stack->size = 0;

	return stack;
}

/**
 * Frees the stack data and its pointer.
 */
void freeStack(Stack *stack)
{
	if (!isEmpty(stack))  stackRemoveAll(stack);

	free(stack);
}

/**
 * Checks if the stack is empty.
 */
static int isEmpty(const Stack *stack)
{
	return (stack->first == NULL);
}

/**
 * Frees the node data and its pointer.
 */
static void freeNode(stackNodeRef p)
{
	free(p->data);
	free(p);
}

/**
 * Creates a new node and set the data data.
 */
static stackNodeRef newNode(stackData data)
{
	stackNodeRef node;

	// Reserve memory for the node.
	if ((node = (stackNodeRef)malloc(sizeof(node))) == NULL) {
		perror("Unable to reserve memory.");
		exit(151);
	}

	// Initializes the data.
	node->next = NULL;
	node->data = data;

	return node;
}

/**
 * Set the first node of the stack.
 */
static void firstNode(Stack *stack, stackData data)
{
	stackNodeRef node = newNode(data);

	stack->first = node;

	(stack->size)++;
}

/**
 * Push data at the top of the stack.
 * IF: the stack is empty creates a new node.
 */
void stackPush(Stack *stack, stackData data)
{
	if (isEmpty(stack)) {
		firstNode(stack, data);
		return;
	}

	stackNodeRef node = newNode(data);

	node->next = stack->first;
	stack->first = node;

	(stack->size)++;
}

/**
 * Pull top data of the stack.
 */
stackData stackPull(Stack *stack)
{
	if (isEmpty(stack))  return NULL;

	stackNodeRef temp;
	stackData data;

	temp = stack->first;
	data = temp->data;

	stack->first = stack->first->next;

	free(temp);

	(stack->size)--;

	return data;
}

/**
 * Frees and removes all nodes, and reset the stack data.
 */
void stackRemoveAll(Stack *stack)
{
	if (isEmpty(stack))  return;

	stackNodeRef temp;

	while(stack->first != NULL) {
		temp = stack->first;
		stack->first = stack->first->next;
		freeNode(temp);
	}

	stack->size = 0;
}
