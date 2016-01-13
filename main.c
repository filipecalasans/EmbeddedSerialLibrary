#include "circular_fifo.h"

#include <stdio.h>

#define FIFO_SIZE   1024

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

    printf("pop: %d\n", (int)pop(&fifo));
    printf("pop: %d\n", (int)pop(&fifo));
    printf("pop: %d\n", (int)pop(&fifo));
    printf("pop: %d\n", (int)pop(&fifo));
   
    printf("size %d\n", (int)getSize(&fifo));
    printf("isEmpty? %d\n", (int)isEmpty(&fifo));
    printf("num elements %d\n", (int)getNumElements(&fifo));
    
    push(&fifo, 13);
    printf("pop: %d\n", (int)pop(&fifo));
    push(&fifo, 14);
    printf("pop: %d\n", (int)pop(&fifo));
    push(&fifo, 15);
    printf("pop: %d\n", (int)pop(&fifo));
    printf("pop: %d\n", (int)pop(&fifo));
    
    printf("size %d\n", (int)getSize(&fifo));
    printf("isEmpty? %d\n", (int)isEmpty(&fifo));
    printf("num elements %d\n", (int)getNumElements(&fifo));
    
    printf("--------- Multiples Insertions/Remotions\n");
    
    uint8_t insertItens[1023] = {10};
    
    pushMultiple(&fifo, insertItens, 1023);
    printf("size %d\n", (int)getSize(&fifo));
    printf("isEmpty? %d\n", (int)isEmpty(&fifo));
    printf("num elements %d\n", (int)getNumElements(&fifo));
    return 0;
}
