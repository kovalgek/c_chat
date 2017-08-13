//
//  ErrorHelper.c
//  Chat 
//
//  Created by Anton Kovalchuk on 16.04.17.
//  Copyright © 2017 Anton Kovalchuk. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "ErrorHelper.h"

void dieWithUserMessage(const char *message, const char *detail) 
{
	printf("%s: %s\n",message, detail);
    exit(1);
}

void dieWithSystemMessage(const char *message) 
{
    perror(message);
    exit(1);
}
