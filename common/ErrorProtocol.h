#include <stdio.h>
#include <stdbool.h>
#include "inttypes.h"

const int MAX_ERROR_DESCRIPTION = 128;

// Login request
struct ErrorInfo 
{
	unsigned int number;
	char description[MAX_ERROR_DESCRIPTION];
};
typedef struct ErrorInfo ErrorInfo;
