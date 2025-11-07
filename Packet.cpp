#include <string.h>
#include "Packet.h"
#include "CRC.h"

void buildPacket(Packet* pkt) {
  String strMsg = String(pkt->data) + ":";
  uint8_t crc;

  for(int i = 0; i < 32; i++) {
    if (pkt->hmac[i] < 16) strMsg += "0";
    strMsg += String(pkt->hmac[i], HEX);
  }

  strMsg += ":";

  crc = computeCRC8((uint8_t*)strMsg.c_str(), strMsg.length());
  if (crc < 16) strMsg += "0";
  strMsg += String(crc, HEX);

  pkt->packet = (char*)malloc(strMsg.length() + 1);
  strMsg.toCharArray(pkt->packet, strMsg.length() + 1); // MUST FREE MESSAGE AFTER YOURE FINISHED.
}