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

size_t encodeClientMessage(const ClientMessage *clientMessage, uint8_t *outputBuffer, const size_t bufferSize)
{
	uint8_t *bufferPtr = outputBuffer;
	long size = (size_t) bufferSize;
	int rv = snprintf((char *) bufferPtr, size, "%s %s %s", MAGIC, clientMessage->token, clientMessage->text);

	bufferPtr += rv;
	size -= rv;
	return (size_t) (bufferPtr - outputBuffer);
}

bool decodeClientMessage(uint8_t *inputBuffer, const size_t size, ClientMessage *clientMessage)
{
    printf("0decodeMessageClient %s\n",(char *) inputBuffer);
    
    char *buffer = calloc(strlen((char *)inputBuffer) + 1, sizeof(char));
    strcpy(buffer, (char *)inputBuffer);
    
	char *token = strtok(buffer, DELIMSTR);
    
	// Check for magic
	if (token == NULL || strcmp(token, MAGIC) != 0)
    {
		return false;
    }
    
    printf("1decodeMessageClient %s\n",token);

	// Get token 
	token = strtok(NULL, DELIMSTR);
	if (token == NULL)
    {
		return false;
    }
    
    printf("2decodeMessageClient %s\n",token);

    strcpy(clientMessage->token, token);

	// Get text 
	token = strtok(NULL, DELIMSTR);
	if (token == NULL)
    {
		return false;
    }
    
    printf("3decodeMessageClient %s\n",token);

    strcpy(clientMessage->text, token);
	return true;
}

size_t encodeServerMessage(const ServerMessage *serverMessage, uint8_t *outputBuffer, const size_t bufferSize)
{
	uint8_t *bufferPtr = outputBuffer;
	long size = (size_t) bufferSize;
	int rv = snprintf((char *) bufferPtr, size, "%s %s %s", MAGIC, serverMessage->name, serverMessage->text);

	bufferPtr += rv;
	size -= rv;
	return (size_t) (bufferPtr - outputBuffer);
}

bool decodeServerMessage(uint8_t *inputBuffer, const size_t size, ServerMessage *serverMessage)
{
    char *buffer = calloc(strlen((char *)inputBuffer) + 1, sizeof(char));
    strcpy(buffer, (char *)inputBuffer);
    
	char *token = strtok(buffer, DELIMSTR);

	// Check for magic
	if (token == NULL || strcmp(token, MAGIC) != 0)
    {
		return false;
    }
    
    printf("1decodeMessageServer %s\n",token);

	// Get token 
	token = strtok(NULL, DELIMSTR);
	if (token == NULL)
    {
		return false;
    }

    printf("2decodeMessageServer %s\n",token);
    
    strcpy(serverMessage->name, token);

	// Get text 
	token = strtok(NULL, DELIMSTR);
	if (token == NULL)
    {
		return false;
    }
    
    printf("3decodeMessageServer %s\n",token);

    strcpy(serverMessage->text, token);
	return true;
}
