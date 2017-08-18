//
//  main.c
//  ChatServerTCP
//
//  Created by Anton Kovalchuk on 07.05.17.
//  Copyright © 2017 Anton Kovalchuk. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "../common/TCPServerUtility.h"
#include "../common/LoginEncodingText.h"
#include "../common/ErrorHelper.h"
#include "../common/DelimiterFramer.h"
#include "users.h"
#include <uuid/uuid.h>

int main(int argc, char *argv[]) 
{
	if (argc != 2) // Test for correct number of arguments
		dieWithUserMessage("Parameter(s)", "<Server Port/Service>");

	int servSock = setupTCPServerSocket(argv[1]);

	for (;;) {

		// Wait for a client to connect
		int clntSock = acceptTCPConnection(servSock);

		// Create an input stream from the socket
		FILE *channel = fdopen(clntSock, "r+");
		if (channel == NULL)
			dieWithSystemMessage("fdopen() failed");

		// Receive messages until connection closes
		int mSize;
		uint8_t inBuf[MAX_WIRE_SIZE];
		LoginRequest loginRequest;

		while ((mSize = getNextMesage(channel, inBuf, MAX_WIRE_SIZE)) > 0) 
		{
			memset(&loginRequest, 0, sizeof(loginRequest)); // Clear vote information

			printf("Received message (%d bytes)\n", mSize);

			if (decodeLoginRequest(inBuf, mSize, &loginRequest))
		   	{ 
				printf("login: %s", loginRequest.login);

                uuid_t uuid;
                uuid_generate_time(uuid);

                char uuid_str[37];
                uuid_unparse_lower(uuid, uuid_str);
                printf("generate uuid=%s\n", uuid_str);
			    addUser(loginRequest.login, uuid_str);
                printUsers();

				LoginResponse loginResponse;
			    memset(&loginResponse, 0, sizeof(loginResponse));
				strcpy(loginResponse.token, uuid_str);

				uint8_t outBuf[MAX_WIRE_SIZE];
				mSize = encodeLoginResponse(&loginResponse, outBuf, MAX_WIRE_SIZE);
				if (putMessage(outBuf, mSize, channel) < 0)
			   	{
					fputs("Error framing/outputting message\n", stderr);
					break;
				}
			   	else
			   	{
					printf("Processed login:%s token:%s", loginRequest.login, loginResponse.token); 
				}
				fflush(channel);
			}
		   	else 
			{
				fputs("Parse error, closing connection.\n", stderr);
				break;
			}
		}
		puts("Client finished");
		fclose(channel);
	}
}
