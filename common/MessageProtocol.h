#include <stdio.h>
#include <stdbool.h>
#include "inttypes.h"
#include "Consts.h"

// Message Client 
struct ClientMessage
{
	char token[MAX_TOKEN_SIZE];
	char text[MAX_TEXT_SIZE];
};
typedef struct ClientMessage ClientMessage; 

// Message Server 
struct ServerMessage
{
	char name[MAX_LOGIN_SIZE];
	char text[MAX_TEXT_SIZE];
};
typedef struct ServerMessage ServerMessage; 

