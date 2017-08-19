#include <stdio.h>
#include "MessageProtocol.h"
#include "inttypes.h"

size_t encodeMessageClient(const MessageClient *messageClient, uint8_t *outputBuffer, const size_t bufferSize); 
bool decodeMessageClient(uint8_t *inputBuffer, const size_t size, MessageClient *messageClient); 

size_t encodeMessageServer(const MessageServer *messageServer, uint8_t *outputBuffer, const size_t bufferSize); 
bool decodeMessageServer(uint8_t *inputBuffer, const size_t size, MessageServer *messageServer); 
