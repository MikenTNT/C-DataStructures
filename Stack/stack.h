#ifndef __STACK_H
#define __STACK_H

/*
 * Data types declarations.
 */
#ifndef __STACK_NODE_DATA
#define __STACK_NODE_DATA
typedef void * stackData;
#endif

#ifndef __STACK_NODE
#define __STACK_NODE
typedef struct stackNode {
	stackData data;
	struct stackNode * next;
} stackNode;
#endif

#ifndef __STACK_NODE_REF
#define __STACK_NODE_REF
typedef stackNode * stackNodeRef;
#endif

#ifndef __STACK
#define __STACK
typedef struct Stack {
	stackNodeRef first;
	unsigned int size;
} Stack;
#endif

/*
 * Function prototypes.
 */
Stack * newStack();
void freeStack(Stack *stack);

void stackPush(Stack *stack, stackData data);
stackData stackPull(Stack *stack);
void stackRemoveAll(Stack *stack);


#endif
