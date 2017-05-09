#include "Queue.h"
#include <stdlib.h>

/* Standard queue FIFO implemented using Linked List */

Queue* initQueue() {
	
	return initLista();
}

void enQueue(Queue *queue, void *i, element pr) {
	
	insertEnd(queue, i, pr);	
}

void *deQueue(Queue *queue) {
	
	void *removed = removeBeginning(queue);
	return removed;
}

int EmptyQueue(Queue *queue) {
	
	return isEmpty(queue);
}

long int getSize(Queue *queue) {
	
	return size(queue);
}

void releaseQueue(Queue *queue) {
	
	releaseList(queue);
}