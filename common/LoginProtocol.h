#include <stdio.h>
#include <stdbool.h>
#include "inttypes.h"
#include "Consts.h"

// Login request
struct Login
{
	char value[MAX_LOGIN_SIZE];
};
typedef struct Login Login;

// Login response
struct Token
{
	char value[MAX_TOKEN_SIZE];
};
typedef struct Token Token;
