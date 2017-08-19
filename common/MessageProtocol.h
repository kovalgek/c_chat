#include <stdio.h>
#include <stdbool.h>
#include "inttypes.h"
#include "Consts.h"

// Message Client 
struct MessageClient
{
	char token[MAX_TOKEN_SIZE];
	char text[MAX_TEXT_SIZE];
};
typedef struct MessageClient MessageClient; 

// Message Server 
struct MessageServer
{
	char name[MAX_LOGIN_SIZE];
	char text[MAX_TEXT_SIZE];
};
typedef struct MessageServer MessageServer; 

