#ifndef __USR_SERIAL_INTERFACE_H_
#define __USR_SERIAL_INTERFACE_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void initSerialHAL();

void (*processRawDataCallBack)(uint8_t *, uint32_t) = NULL;
void (*processCommandCallBack)(char *) = NULL;
void (*processBinaryPacketCallBack)(char *) = NULL;
void (*sedDataCallBack)(uint8_t *data, uint32_t size) = NULL;

#endif
