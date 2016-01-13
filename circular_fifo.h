#ifndef CIRCULAR_FIFO_H_
#define CIRCULAR_FIFO_H_

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    uint32_t size;
    uint32_t head;
    uint32_t tail;
    uint8_t *data;
}CircularFifo;

static void initCircularFifo(CircularFifo *fifo, unsigned char* buffer, uint32_t size) {
    fifo->data = buffer;
    fifo->size = size;
    /* Initialize buffer empty */
    fifo->head = 0;
    fifo->tail = 0;
}

static uint32_t getNumElements(CircularFifo *fifo) {
    if(fifo->head <= fifo->tail) {
        return (fifo->tail - fifo->head);
    }
    else {
        return (fifo->size - (fifo->head - fifo->tail));
    }
}

static uint32_t getSize(CircularFifo *fifo) {
    return fifo->size;
}

static bool isEmpty(CircularFifo *fifo) {
    return fifo->tail == fifo->head;
}

static void push(CircularFifo *fifo, uint8_t data) {
    fifo->tail++;
    if(fifo->tail >= fifo->size) {
        fifo->tail = 0;
    }
    fifo->data[fifo->tail] = data;    
}

static uint8_t pop(CircularFifo *fifo) {
    uint8_t item = fifo->data[fifo->head];
    fifo->head++;
    if(fifo->head >= fifo->size) {
        fifo->head = 0;
    } 
    return item; 
}

#endif

