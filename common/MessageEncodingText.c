#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "MessageEncodingText.h"

static const char *MAGIC = "Message";
static const char *DELIMSTR = " ";

enum {
	BASE = 10
};

size_t encodeMessageClient(const MessageClient *messageClient, uint8_t *outputBuffer, const size_t bufferSize)
{
	uint8_t *bufferPtr = outputBuffer;
	long size = (size_t) bufferSize;
	int rv = snprintf((char *) bufferPtr, size, "%s %s %s", MAGIC, messageClient->token, messageClient->text);

	bufferPtr += rv;
	size -= rv;
	return (size_t) (bufferPtr - outputBuffer);
}

bool decodeMessageClient(uint8_t *inputBuffer, const size_t size, MessageClient *messageClient)
{
	char *token = strtok((char *) inputBuffer, DELIMSTR);

	// Check for magic
	if (token == NULL || strcmp(token, MAGIC) != 0)
		return false; 

	// Get token 
	token = strtok(NULL, DELIMSTR);
	if (token == NULL)
		return false;

    strcpy(messageClient->token, token);

	// Get text 
	token = strtok(NULL, DELIMSTR);
	if (token == NULL)
		return false;

    strcpy(messageClient->text, token);
	return true;
}

size_t encodeMessageServer(const MessageServer *messageServer, uint8_t *outputBuffer, const size_t bufferSize)
{
	uint8_t *bufferPtr = outputBuffer;
	long size = (size_t) bufferSize;
	int rv = snprintf((char *) bufferPtr, size, "%s %s %s", MAGIC, messageServer->name, messageServer->text);

	bufferPtr += rv;
	size -= rv;
	return (size_t) (bufferPtr - outputBuffer);
}

bool decodeMessageServer(uint8_t *inputBuffer, const size_t size, MessageServer *messageServer)
{
	char *token = strtok((char *) inputBuffer, DELIMSTR);

	// Check for magic
	if (token == NULL || strcmp(token, MAGIC) != 0)
		return false; 

	// Get token 
	token = strtok(NULL, DELIMSTR);
	if (token == NULL)
		return false;

    strcpy(messageServer->name, token);

	// Get text 
	token = strtok(NULL, DELIMSTR);
	if (token == NULL)
		return false;

    strcpy(messageServer->text, token);
	return true;
}
