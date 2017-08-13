#include <stdio.h>
#include "LoginProtocol.h"
#include "inttypes.h"

size_t encode(const LoginRequest *loginRequest, uint8_t *outputBuffer, const size_t bufferSize); 
bool decode(uint8_t *inputBuffer, const size_t size, LoginRequest *loginRequest); 
