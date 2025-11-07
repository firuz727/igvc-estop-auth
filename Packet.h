#ifndef PACKET_H
#define PACKET_H
#include <Arduino.h>

struct Packet{
  char* data;
  char* packet;
  uint8_t dataLength;
  uint8_t hmac[32];
  uint8_t crc;
};

void buildPacket(Packet* pkt);


#endif