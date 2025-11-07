#include "Message.h"
#include "Packet.h"

int minNonce = 0;
int usedNonces[10];
int freeIndex = 0;

int counter = -1;

void resetNonces() {
  for (int i = 0; i < 10; i++) {
    usedNonces[i] = -1;
  }
}

void buildMessage(Packet* pkt, MessageType type) {
  String command;

  switch (type) {
    case ESTOP:
      command = "E-STOP"; break;
    case MAINTENANCE:
      command = "MAINTAIN"; break;
    // ... more cases
    default:
      command = "MAINTAIN"; break;
  }

  counter++;
  uint32_t nonce = generateNonce();

  String msg = command + ":" + String(counter) + ":" + String(nonce);

  // Allocate memory for char array
  pkt->data = (char*)malloc(msg.length() + 1);  // +1 for null terminator "\0"
  msg.toCharArray(pkt->data, msg.length() + 1); // MUST FREE pkt->data AFTER USE!
}

uint16_t generateNonce() {
  int freeIndex = -1;

  // Find first unused slot
  for (int i = 0; i < 10; i++) {
    if (usedNonces[i] == -1) {
      freeIndex = i;
      break;
    }
  }

  if (freeIndex == -1) {
    // All used — reset and shift range
    minNonce += 10;
    resetNonces();
    freeIndex = 0;
  }

  long randomNonce;
  bool unique = false;

  // Generate a unique nonce in the current range
  while (!unique) {
    randomNonce = random(minNonce, minNonce + 10);
    unique = true;
    for (int i = 0; i < 10; i++) {
      if (usedNonces[i] == randomNonce) {
        unique = false;
        break;
      }
    }
  }

  usedNonces[freeIndex] = randomNonce;
  Serial.print("Generated nonce: ");
  Serial.println(randomNonce);
  return randomNonce;
}
