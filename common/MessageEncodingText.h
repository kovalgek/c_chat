#include <stdio.h>
#include "MessageProtocol.h"
#include "inttypes.h"

size_t encodeClientMessage(const ClientMessage *messageClient, uint8_t *outputBuffer, const size_t bufferSize); 
bool decodeClientMessage(uint8_t *inputBuffer, const size_t size, ClientMessage *messageClient); 

size_t encodeServerMessage(const ServerMessage *messageServer, uint8_t *outputBuffer, const size_t bufferSize); 
bool decodeServerMessage(uint8_t *inputBuffer, const size_t size, ServerMessage *messageServer); 
