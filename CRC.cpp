#include "CRC.h"
#include "Packet.h"

void computeCRC(Packet* pkt) {
  pkt->crc = computeCRC8((uint8_t*)pkt->data, strlen(pkt->data));
}

uint8_t computeCRC8(uint8_t* data, size_t len) {
  uint8_t crc = 0x00;   // Initial value
  uint8_t poly = 0x07;  // Generator polynomial, 0x07 is equal to x^8 + x + 1

  for (size_t i = 0; i < len; i++) {
    crc ^= data[i];  // XOR byte into CRC

    for (uint8_t bit = 0; bit < 8; bit++) {
      if (crc & 0x80) {
        crc = (crc << 1) ^ poly;
      } else {
        crc <<= 1;
      }
    }
  }

  return crc;
}