#include "circular_fifo.h"

#include <stdio.h>

#define FIFO_SIZE  7 

void printFifo(CircularFifo *fifo) {
    printf("FIFO: ");
    uint32_t currentHead = fifo->head;

    while(currentHead != fifo->tail) {
        printf("%d,", fifo->data[currentHead++]);
        if(currentHead == fifo->size) {
            currentHead = 0;
        } 
    }
    printf("\n"); 
}


int main () {
    
    CircularFifo fifo;
    int data[FIFO_SIZE];

    initCircularFifo(&fifo, (unsigned char *)data, FIFO_SIZE);
     
    printf("size %d\n", (int)getSize(&fifo));
    printf("isEmpty? %d\n", (int)isEmpty(&fifo));
    printf("num elements %d\n", (int)getNumElements(&fifo));
    
    push(&fifo, 8);
    push(&fifo, 9);
    push(&fifo, 10);
    push(&fifo, 11);
    push(&fifo, 12);
    printFifo(&fifo);

    printf("pop: %d\n", (int)pop(&fifo));
    printf("pop: %d\n", (int)pop(&fifo));
    printf("pop: %d\n", (int)pop(&fifo));
    printf("pop: %d\n", (int)pop(&fifo));
   
    printf("size %d\n", (int)getSize(&fifo));
    printf("isEmpty? %d\n", (int)isEmpty(&fifo));
    printf("num elements %d\n", (int)getNumElements(&fifo));
    printFifo(&fifo);
 
    push(&fifo, 13);
    printf("pop: %d\n", (int)pop(&fifo));
    printFifo(&fifo);
    push(&fifo, 14);
    printf("pop: %d\n", (int)pop(&fifo));
    printFifo(&fifo);
    push(&fifo, 15);
    printf("pop: %d\n", (int)pop(&fifo));
    printFifo(&fifo);
    printf("pop: %d\n", (int)pop(&fifo));
    printFifo(&fifo);
    
    printf("size %d\n", (int)getSize(&fifo));
    printf("isEmpty? %d\n", (int)isEmpty(&fifo));
    printf("num elements %d\n", (int)getNumElements(&fifo));
    
    printf("--------- Multiples Insertions/Removals\n");
    
    uint8_t insertItens[6] = {1, 2, 4, 8, 10, 12};
    
    pushMultiple(&fifo, insertItens, 6);
    printFifo(&fifo);
    popMultiple(&fifo, insertItens, 4);
    printFifo(&fifo);
    printf("size %d\n", (int)getSize(&fifo));
    printf("isEmpty? %d\n", (int)isEmpty(&fifo));
    printf("num elements %d\n", (int)getNumElements(&fifo));
    return 0;
}
