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
#include "LoginProtocol.h"

static const char *MAGIC = "Login";
static const char *DELIMSTR = " ";

enum {
	BASE = 10
};

/* Encode voting message info as a text string.
 * WARNING: Message will be silently truncated if buffer is too small!
 * Invariants (e.g. 0 <= candidate <= 1000) not checked.
 */
size_t encode(const LoginRequest *loginRequest, uint8_t *outputBuffer, const size_t bufferSize) 
{
	uint8_t *bufferPtr = outputBuffer;
	long size = (size_t) bufferSize;
	int rv = snprintf((char *) bufferPtr, size, "%s %s", MAGIC, loginRequest->login);

	bufferPtr += rv;
	size -= rv;
	return (size_t) (bufferPtr - outputBuffer);
}

/* Extract message information from given buffer.
 * Note: modifies input buffer.
 */
bool decode(uint8_t *inputBuffer, const size_t size, LoginRequest *loginRequest) 
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
