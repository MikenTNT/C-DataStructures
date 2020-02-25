#ifndef __QUEUE_H
#define __QUEUE_H


/*
 * Data types declarations.
 */
#ifndef __QUEUE_NODE_DATA
#define __QUEUE_NODE_DATA
typedef void * queueData;
#endif

#ifndef __QUEUE_NODE
#define __QUEUE_NODE
typedef struct queueNode {
	queueData data;
	struct queueNode * next;
} queueNode;
#endif

#ifndef __QUEUE_NODE_REF
#define __QUEUE_NODE_REF
typedef queueNode * queueNodeRef;
#endif

#ifndef __QUEUE
#define __QUEUE
typedef struct Queue {
	queueNodeRef first;
	queueNodeRef last;
	unsigned int size;
} Queue;
#endif


/*
 * Function prototypes.
 */
Queue * newQueue();
void freeQueue(Queue *queue);

void queuePush(Queue *queue, queueData data);
queueData queuePull(Queue *queue);
void queueRemoveAll(Queue *queue);


#endif
