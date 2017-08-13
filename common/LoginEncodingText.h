#include <stdio.h>
#include "LoginProtocol.h"
#include "inttypes.h"

size_t encodeLoginRequest(const LoginRequest *loginRequest, uint8_t *outputBuffer, const size_t bufferSize); 
bool decodeLoginRequest(uint8_t *inputBuffer, const size_t size, LoginRequest *loginRequest); 

size_t encodeLoginResponse(const LoginResponse *loginResponse, uint8_t *outputBuffer, const size_t bufferSize); 
bool decodeLoginResponse(uint8_t *inputBuffer, const size_t size, LoginResponse *loginResponse); 
