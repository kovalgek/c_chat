#include <stdio.h>
#include <stdbool.h>
#include "inttypes.h"
#include "Consts.h"

// Login request
struct LoginRequest
{
	char login[MAX_LOGIN_SIZE];
};
typedef struct LoginRequest LoginRequest;

// Login response
struct LoginResponse
{
	char token[MAX_TOKEN_SIZE];
};
typedef struct LoginResponse LoginResponse;
