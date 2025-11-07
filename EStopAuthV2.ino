#include <MemoryFree.h>
#include <pgmStrToRAM.h>
#include <Crypto.h>
#include <SHA256.h>
#include <String.h>
#include <Serial.h>
#include "HMAC.h"
#include "Message.h"
#include "Packet.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  resetNonces();
}

void loop() {
  // put your main code here, to run repeatedly:
  enum MessageType command = ESTOP;

  Packet packet;          // Create a packet
  Packet* pkt = &packet;  // Create a pointer to it

  buildMessage(pkt, command);
  generateHMAC(pkt);
  buildPacket(pkt);

  Serial.println(pkt->packet);
  
  // Serial.println(freeMemory());

  clearPacket(pkt);
  delay(1000);
}

void clearPacket(Packet* pkt) { // MUST FREE MALLOC'd DATA!
  if (pkt->data) {
    free(pkt->data);
    pkt->data = nullptr;
  }
  if (pkt->packet) {
    free(pkt->packet);
    pkt->packet = nullptr;
  }
}
