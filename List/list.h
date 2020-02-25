#ifndef __LIST_H
#define __LIST_H


/*
 * Data types declarations.
 */
#ifndef __LIST_NODE_DATA
#define __LIST_NODE_DATA
typedef void * listData;
#endif

#ifndef __LIST_NODE
#define __LIST_NODE
typedef struct listNode {
	listData data;
	struct listNode * prev;
	struct listNode * next;
} listNode;
#endif

#ifndef __LIST_NODE_REF
#define __LIST_NODE_REF
typedef listNode * listNodeRef;
#endif

#ifndef __LIST
#define __LIST
typedef struct List {
	listNodeRef first;
	listNodeRef last;
	unsigned int size;
} List;
#endif


/*
 * Function prototypes.
 */
List * newList();
void freeList(List *list);

void listInsertBefore(List *list, listData data, listNodeRef p);
void listInsertNode(List *list, listData data, listNodeRef p);
void listInsertAfter(List *list, listData data, listNodeRef p);
void listRemoveNode(List *list, listNodeRef p);
void listRemoveAll(List *list);


#endif
