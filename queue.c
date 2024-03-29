#include <stdio.h>
#include <stdlib.h>

/*
	QUEUE
	-----

	Inizializzazione:
		Queue *myQueue;
		QueueInit(&myQueue);

	Operazione ENQUEUE:
		QueueEnqueue(&myStack, 1);		/// <<<--- 1

	Operazione BACK:
		QueueBack(&myStack)				/// --->>> (valore int)

	Operazione FRONT:
		QueueFront(&myStack)			/// --->>> (valore int)

	Operazione DEQUEUE:
		QueueDequeue(&myStack)			/// --->>> (valore int)

*/

typedef struct QueueElement {
	struct QueueElement *backElement;
	int value;
} QueueElement;

typedef struct Queue {
	QueueElement *frontElement;
	QueueElement *backElement;
} Queue;

void QueueInit(Queue **ptrQueue) {
	(*ptrQueue) = (Queue *) malloc( sizeof(Queue) );
	(*ptrQueue)->frontElement = NULL;
	(*ptrQueue)->backElement = NULL;
}


void QueueFinish(Queue **ptrQueue) {
	free((*ptrQueue));
}

void QueueEnqueue(Queue **ptrQueue, int enqueueValue) {
	QueueElement *newElement = (QueueElement *) malloc( sizeof(QueueElement) );
	newElement->value = enqueueValue;
	newElement->backElement = NULL;
	if ((*ptrQueue)->backElement != NULL) {
		QueueElement *queueBackElement = (*ptrQueue)->backElement;
		(*queueBackElement).backElement = newElement;
	}
	(*ptrQueue)->backElement = newElement;
	if ( (*ptrQueue)->frontElement == NULL ) (*ptrQueue)->frontElement = newElement;
}

int QueueFront(Queue **ptrQueue) {
	if ( (*ptrQueue)->frontElement == NULL ) return (0);
	return ( (*ptrQueue)->frontElement->value );
}

int QueueBack(Queue **ptrQueue) {
	if ( (*ptrQueue)->backElement == NULL ) return (0);
	return ( (*ptrQueue)->backElement->value );
}

int QueueDequeue(Queue **ptrQueue) {
	if ( (*ptrQueue)->frontElement == NULL ) return (0);
	int returnValue = ((*ptrQueue)->frontElement)->value;
	QueueElement *next = ((*ptrQueue)->frontElement)->backElement;
	free((*ptrQueue)->frontElement);
	(*ptrQueue)->frontElement = next;
	return (returnValue);
}

void QueuePrint(Queue **ptrQueue) {
	QueueElement *scanQueue = (*ptrQueue)->frontElement;
	printf("-- Queue ----------------------------\n");
	while ( (scanQueue != NULL) ) {
		printf("[ %d\t ]\n", scanQueue->value);
		scanQueue = scanQueue->backElement;
	}
	printf("-------------------------------------\n");
}

int main() {
	Queue *myQueue;
	QueueInit(&myQueue);
	QueuePrint(&myQueue);

	QueueEnqueue(&myQueue, 1);
	QueueEnqueue(&myQueue, 2);
	QueuePrint(&myQueue);

	QueueEnqueue(&myQueue, 3);
	QueuePrint(&myQueue);

	printf("Dequeue: %d\n", QueueDequeue(&myQueue));
	printf("Dequeue: %d\n", QueueDequeue(&myQueue));
	QueuePrint(&myQueue);

	QueueEnqueue(&myQueue, 4);
	QueuePrint(&myQueue);

	printf("Dequeue: %d\n", QueueDequeue(&myQueue));
	printf("Dequeue: %d\n", QueueDequeue(&myQueue));
	printf("Dequeue: %d\n", QueueDequeue(&myQueue));
	printf("Dequeue: %d\n", QueueDequeue(&myQueue));
	printf("Dequeue: %d\n", QueueDequeue(&myQueue));
	QueuePrint(&myQueue);
	
	// Test per verificare il NON-CONSUMO di memoria... 
	int valTest = 0;
	while (1) {
		QueueEnqueue(&myQueue, 15);
		valTest = QueueDequeue(&myQueue);
	}
	
	QueueFinish(&myQueue);

	return(0);
}
