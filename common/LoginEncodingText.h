#include <stdio.h>
#include "LoginProtocol.h"
#include "inttypes.h"

size_t encodeLogin(const Login *loginRequest, uint8_t *outputBuffer, const size_t bufferSize); 
bool decodeLogin(uint8_t *inputBuffer, const size_t size, Login *loginRequest); 

size_t encodeToken(const Token *loginResponse, uint8_t *outputBuffer, const size_t bufferSize); 
bool decodeToken(uint8_t *inputBuffer, const size_t size, Token *loginResponse); 
