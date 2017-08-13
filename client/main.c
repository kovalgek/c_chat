#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "../common/ErrorHelper.h"
#include "../common/TCPClientUtility.h"
//#include "../common/LoginProtocol.h"
#include "../common/ErrorProtocol.h"
#include "../common/DelimiterFramer.h"
#include "../common/LoginEncodingText.h"

int main() 
{
	char server[] = "127.0.0.1";
	char port[] = "5000";

	// Create a connected TCP socket
	int socket = setupTCPClientSocket(server, port);
	if (socket < 0)
		dieWithUserMessage("setupTCPClientSocket() failed", "unable to connect");

	FILE *socketStream = fdopen(socket, "r+"); // Wrap for stream I/O
	if (socketStream == NULL)
		dieWithSystemMessage("fdopen() failed");

    LoginRequest loginRequest;
	memset(&loginRequest, 0, sizeof(loginRequest));

    strcpy(loginRequest.login, "kovalgek");


	// Encode for transmission
	uint8_t outbuf[MAX_WIRE_SIZE];
	size_t reqSize = encodeLoginRequest(&loginRequest, outbuf, MAX_WIRE_SIZE);

	// Print info
	printf("Sending %lu-byte with login %s...\n", reqSize, loginRequest.login);


	// Frame and send
	if (putMessage(outbuf, reqSize, socketStream) < 0)
		dieWithSystemMessage("putMessage() failed");

	// Receive and print response
	uint8_t inbuf[MAX_WIRE_SIZE];
	size_t respSize = getNextMesage(socketStream, inbuf, MAX_WIRE_SIZE); // Get the message

	LoginResponse loginResponse;
	memset(&loginResponse, 0, sizeof(loginResponse));

	if (decodeLoginResponse(inbuf, respSize, &loginResponse))
   	{
		printf("login=%s", loginResponse.token);
	}

	// Close up
	fclose(socketStream);

	exit(0);
}
