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

size_t encodeLogin(const Login *login, uint8_t *outputBuffer, const size_t bufferSize) 
{
	uint8_t *bufferPtr = outputBuffer;
	long size = (size_t) bufferSize;
	int rv = snprintf((char *) bufferPtr, size, "%s %s", MAGIC, login->value);

	bufferPtr += rv;
	size -= rv;
	return (size_t) (bufferPtr - outputBuffer);
}

bool decodeLogin(uint8_t *inputBuffer, const size_t size, Login *login) 
{
    char *buffer = calloc(strlen((char *)inputBuffer) + 1, sizeof(char));
    strcpy(buffer, (char *)inputBuffer);
    
	char *token = strtok(buffer, DELIMSTR);

	// Check for magic
	if (token == NULL || strcmp(token, MAGIC) != 0)
    {
		return false;
    }
    
    printf("1decodeLoginRequest %s\n",token);

	// Get indicator
	token = strtok(NULL, DELIMSTR);
	if (token == NULL)
    {
		return false;
    }

    printf("2decodeLoginRequest %s\n",token);
    
    strcpy(login->value, token);

	return true;
}

size_t encodeToken(const Token *loginResponse, uint8_t *outputBuffer, const size_t bufferSize) 
{
	uint8_t *bufferPtr = outputBuffer;
	long size = (size_t) bufferSize;
	int rv = snprintf((char *) bufferPtr, size, "%s %s", MAGIC, loginResponse->value);

	bufferPtr += rv;
	size -= rv;
	return (size_t) (bufferPtr - outputBuffer);
}

bool decodeToken(uint8_t *inputBuffer, const size_t size, Token *token) 
{
    char *buffer = calloc(strlen((char *)inputBuffer) + 1, sizeof(char));
    strcpy(buffer, (char *)inputBuffer);
    
    char *tokenString = strtok((char *) buffer, DELIMSTR);
    
	// Check for magic
	if (token == NULL || strcmp(tokenString, MAGIC) != 0)
    {
		return false;
    }
    
    printf("1decodeLoginResponse %s\n",tokenString);

	// Get indicator
	tokenString = strtok(NULL, DELIMSTR);
	if (tokenString == NULL)
    {
		return false;
    }
    
    printf("2decodeLoginResponse %s\n",tokenString);

    strcpy(token->value, tokenString);

	return true;
}
