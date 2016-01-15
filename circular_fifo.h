#ifndef CIRCULAR_FIFO_H_
#define CIRCULAR_FIFO_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

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

static uint8_t peak(CircularFifo *fifo) {
    uint8_t item = fifo->data[fifo->head];
    fifo->head++;
    return item; 
}

static void pushMultiple(CircularFifo *fifo, uint8_t *data, uint32_t size) {
    if(fifo->tail + size > fifo->size) {
        uint32_t upperSize = fifo->size - fifo->tail;
        memcpy(&fifo->data[fifo->tail], data, upperSize);
        uint32_t lowerSize = size - upperSize;
        memcpy(fifo->data, &data[upperSize], lowerSize);
        fifo->tail = lowerSize;
    }
    else {
        memcpy(&fifo->data[fifo->tail], data, size);
        fifo->tail += size;
        if(fifo->tail >= fifo->size) {
            fifo->tail = 0;
        } 
    }
}


static void peakMultiple(CircularFifo *fifo, uint8_t *data, uint32_t size) {
    if(fifo->head + size > fifo->size) {
        uint32_t upperSize = fifo->size - fifo->head;
        memcpy(data, &fifo->data[fifo->head], upperSize);
        uint32_t lowerSize = size - upperSize;
        memcpy(&data[upperSize], &fifo->data, lowerSize);
    }
    else {
        memcpy(data, &fifo->data[fifo->head], size);
    }
}

static void discardMultiple(CircularFifo *fifo, uint32_t size){
    if(fifo->head + size > fifo->size) {
        uint32_t upperSize = fifo->size - fifo->head;
        uint32_t lowerSize = size - upperSize;
        fifo->head = lowerSize;
    }
    else {
        fifo->head += size;
        if(fifo->head >= fifo->size) {
            fifo->head = 0;
        }    
    }
}

static void popMultiple(CircularFifo *fifo, uint8_t *data, uint32_t size) {
    peakMultiple(fifo, data, size);   
    discardMultiple(fifo, size);
}

#endif



