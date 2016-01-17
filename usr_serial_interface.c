#include "usr_serial_interface.h"

void (*processRawDataCallBack)(uint8_t *, uint32_t) = NULL;
void (*processCommandCallBack)(char *) = NULL;
void (*processBinaryPacketCallBack)(void *) = NULL;
void (*sedDataCallBack)(uint8_t *data, uint32_t size) = NULL;

void initSerialHAL() {
	/* Implement serial hardware interface
	here!! */
}

