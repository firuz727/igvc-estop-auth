#ifndef MESSAGE_H
#define MESSAGE_H
#include <Arduino.h>
#include "Packet.h"

enum MessageType {
  ESTOP,
  MAINTENANCE
  // ...
};

void resetNonces();
uint16_t generateNonce();
void buildMessage(Packet*, MessageType type);

#endif