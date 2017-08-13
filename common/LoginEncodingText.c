/* Routines for Text encoding of vote messages.
 * Wire Format:
 * "Login message"
 */
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "LoginEncodingText.h"
//#include "LoginProtocol.h"

static const char *MAGIC = "Login";
static const char *DELIMSTR = " ";

enum {
	BASE = 10
};

size_t encodeLoginRequest(const LoginRequest *loginRequest, uint8_t *outputBuffer, const size_t bufferSize) 
{
	uint8_t *bufferPtr = outputBuffer;
	long size = (size_t) bufferSize;
	int rv = snprintf((char *) bufferPtr, size, "%s %s", MAGIC, loginRequest->login);

	bufferPtr += rv;
	size -= rv;
	return (size_t) (bufferPtr - outputBuffer);
}

bool decodeLoginRequest(uint8_t *inputBuffer, const size_t size, LoginRequest *loginRequest) 
{
	char *token = strtok((char *) inputBuffer, DELIMSTR);

	// Check for magic
	if (token == NULL || strcmp(token, MAGIC) != 0)
		return false; 

	// Get indicator
	token = strtok(NULL, DELIMSTR);
	if (token == NULL)
		return false;

    strcpy(loginRequest->login, token);

	return true;
}

size_t encodeLoginResponse(const LoginResponse *loginResponse, uint8_t *outputBuffer, const size_t bufferSize) 
{
	uint8_t *bufferPtr = outputBuffer;
	long size = (size_t) bufferSize;
	int rv = snprintf((char *) bufferPtr, size, "%s %s", MAGIC, loginResponse->token);

	bufferPtr += rv;
	size -= rv;
	return (size_t) (bufferPtr - outputBuffer);
}

bool decodeLoginResponse(uint8_t *inputBuffer, const size_t size, LoginResponse *loginResponse) 
{
	char *token = strtok((char *) inputBuffer, DELIMSTR);

	// Check for magic
	if (token == NULL || strcmp(token, MAGIC) != 0)
		return false; 

	// Get indicator
	token = strtok(NULL, DELIMSTR);
	if (token == NULL)
		return false;

    strcpy(loginResponse->token, token);

	return true;
}
