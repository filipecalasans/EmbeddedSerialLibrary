#include "serial_protocol.h"
#include "circular_fifo.h"

CircularFifo fifoIn, fifoOut;
uint8_t dataBufferIn[FIFO_IN_SIZE];
uint8_t dataBufferOut[FIFO_OUT_SIZE];

static uint64_t lastTimeDataReceived = 0;
static PacketDefinition packetDefinition = {0};

void (*processRawDataCallBack)() = NULL;
void (*processCommandCallBack)() = NULL;
void (*processBinaryPacketCallBack)() = NULL;

void (*sedDataCallBack)(uint8_t *data, uint32_t size) = NULL;

void initSerialProtocol() {
	initSerialUsr();
	initCircularFifo(&fifoIn, dataBufferIn, FIFO_IN_SIZE);
	initCircularFifo(&fifoOut, dataBufferOut, FIFO_OUT_SIZE);
	packetDefinition.isConfigured = false;
}

uint32_t bytesAvailable() {
	return getSize(&fifoIn);
}

void setPacketDefinition(PacketDefinition definition) {
	packetDefinition = definition;
	packetDefinition.isConfigured= true;
}

PacketDefinition getPacketDefinition() {
	return packetDefinition;
}

inline void dataReceived(uint8_t *data, uint32_t size) {
	bool sizeEnough = ((size + getNumElements(&fifoIn)) < getSize(&fifoIn));
	pushMultiple(&fifoIn, data, size);
	if(processBinaryPacketCallBack) {
		processBinaryPacketCallBack();
	}
	else {
		/* Jump to Hardfault */
		printf("[dataReceived] FIFO IN overflow.\n");
	}
}

/* 
   Read number of bytes passed on size variable and
   return number of bytes read. 
*/
uint32_t read(uint8_t *data, uint32_t size) {
	if(bytesAvailable() >= size) {
		popMultiple(&fifoIn, data, size);
	}
	return 0;
}

/* 
    Try to Read the next binary packet. Packet size must be specified
    in the variable packetSize. This function returns the number of bytes 
    read.
*/
uint32_t readNextPacket(void *packet) {
	if(packetDefinition.isConfigured) {
		if(packetDefinition.isPayloadSizeFixed) {
			uint16_t packetSize = packetDefinition.headerSize + packetDefinition.payloadSize;
			if(getSize(&fifoIn) >= packetSize) {
				popMultiple(&fifoIn, (uint8_t*)packet, packetSize);
				return packetSize;
			}
			else {
				return 0;
			}
		}
		else {
			if(getSize(&fifoIn) >= packetDefinition.headerSize) {
				peakMultiple(&fifoIn, (uint8_t*)packet, packetDefinition.headerSize);
				uint16_t payloadSize = *((((uint8_t*)packet) + packetDefinition.payloadSizeOffset));
				uint16_t packetSize = payloadSize + packetDefinition.headerSize;
				if(getSize(&fifoIn) >= packetSize) {
					peakMultiple(&fifoIn, ((uint8_t*)packet+packetDefinition.headerSize), payloadSize);
					discardMultiple(&fifoIn, packetSize);
					return packetSize;
				}
				else {
					return 0;
				}
			}
		}
	}
	return 0;
}
