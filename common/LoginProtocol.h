#include <stdio.h>
#include <stdbool.h>
#include "inttypes.h"

const int MAX_LOGIN_SIZE = 128;
const int MAX_TOKEN_SIZE = 128;
const int MAX_WIRE_SIZE = 500;

// Login request
struct LoginRequest
{
	char login[MAX_LOGIN_SIZE];
};
typedef struct LoginInfo LoginInfo;

// Login response
struct LoginResponse
{
	char token[MAX_TOKEN_SIZE];
};
typedef struct LoginResponse LoginResponse;
