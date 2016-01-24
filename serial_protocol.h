#ifndef __SERIAL_PROTOCOL_H_
#define __SERIAL_PROTOCOL_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "usr_serial_interface.h"

typedef struct{
    bool isConfigured;
    uint16_t headerSizeOffset;
    uint16_t headerSize;
    bool isPayloadSizeFixed;
    uint16_t payloadSizeOffset;     
    uint16_t payloadSize;
}PacketDefinition;

#define FIFO_OUT_SIZE 2048
#define FIFO_IN_SIZE 2048

void initSerialProtocol();
uint32_t bytesAvailable();


void setPacketDefinition(PacketDefinition definition);
PacketDefinition getPacketDefinition();

inline void dataReceived(uint8_t *data, uint32_t size);
/* 
   Read number of bytes passed on size variable and
   return number of bytes read. 
*/
uint32_t read(uint8_t *data, uint32_t size);

/* 
    Try to Read the next binary packet. Packet size must be specified
    in the variable packetSize. This function returns the number of bytes 
    read.
*/
uint32_t readNextPacket(void *packet);



#endif
