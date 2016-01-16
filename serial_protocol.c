#include "serial_protocol.h"
#include "circular_fifo.h"

#define FIFO_SIZE 2048

static uint64_t lastTimeDataReceived = 0;

CircularFifo fifo;
uint8_t dataBuffer[FIFO_SIZE];

bool atModeEnable = false;





