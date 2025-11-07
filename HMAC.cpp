#include <Crypto.h>
#include <SHA256.h>
#include "HMAC.h"
#include "Packet.h"

static const SecretKey key = {
  .key = "PUTKEYHERE",
  .length = strlen("PUTKEYHERE")
};

SHA256 sha;

void generateHMAC(Packet* pkt) {

  char* message = pkt->data;
  uint16_t messageLen = strlen(pkt->data);

  char* secretKey = key.key;
  uint16_t keyLen = strlen(secretKey);

  sha.resetHMAC(secretKey, keyLen);                       // Step 1: prepare inner hash with ipad
  sha.update(message, messageLen);                        // Step 2: feed in your message
  sha.finalizeHMAC(secretKey, keyLen, pkt->hmac, 32);  // Step 3: finalize with opad and get HMAC

}
