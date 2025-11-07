#ifndef HMAC_H
#define HMAC_H
#include <Arduino.h>
#include "Packet.h"

struct SecretKey {
  char* key;
  uint16_t length;
};

void generateHMAC(Packet* pkt);

#endif