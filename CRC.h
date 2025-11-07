#ifndef HMAC_H
#define HMAC_H
#include <Arduino.h>
#include "Packet.h"

void computeCRC(Packet* pkt);
uint8_t computeCRC8(uint8_t* message, size_t messageLen);

#endif