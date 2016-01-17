#ifndef __SERIAL_PROTOCOL_H_
#define __SERIAL_PROTOCOL_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "usr_serial_interface.h"

/* You must implement this function */
typedef enum {
    SERIAL_MODE_TRANSPARENT, /* Handles data as a stream of bytes with no packet or command meaning.*/
    SERIAL_MODE_BINARY_PACKET, /* Data are transmitted as packets. Waits until alll packet has been tramitted to act */
    SERIAL_MODE_COMMAND /* Hanlds data as a sequence of AT commands */
}SerialMode;

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

void setSerialMode(SerialMode mode);
SerialMode getSerialMode();

void setPacketDefinition(PacketDefinition definition);
PacketDefinition getPacketDefinition();

/* 
   Read number of bytes passed on size variable and
   return number of bytes read. 
*/
uint32_t read(uint8_t *data, uint32_t size);

/* 
  Read next AT comamnd. Command String must
  be able to accommodate the longest command
  string possible. Format: AT[COMMAND]\n
  Return if it was possible to read a AT command from the buffer 
*/
bool readNextCommand(char *commandString);

/* 
    Try to Read the next binary packet. Packet size must be specified
    in the variable packetSize. This function returns the number of bytes 
    read.
*/
uint32_t readNextPacket(void *packet);

/* Get current serial mode */
SerialMode getCurrentSerialMode();

bool isAtCommandEnable();
void setAtCommandEnable(bool enable);

#endif
