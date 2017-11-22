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
#include <pthread.h>

#include "../../../common/ErrorHelper.h"
#include "../../../common/TCPClientUtility.h"
#include "../../../common/ErrorProtocol.h"
#include "../../../common/DelimiterFramer.h"
#include "../../../common/LoginEncodingText.h"
#include "../../../common/MessageEncodingText.h"

void handleMessages(int clntSocket);
void *threadMain(void *arg); // Main program of a thread

// Structure of arguments to pass to client thread
struct ThreadArgs
{
    int clntSock; // Socket descriptor for client
};

int main()
{
    char server[] = "127.0.0.1";
    char port[] = "5000";
    
    // Create a connected TCP socket
    int socket = setupTCPClientSocket(server, port);
    if (socket < 0)
    {
        dieWithUserMessage("setupTCPClientSocket() failed", "unable to connect");
    }
    
    // Wrap for stream I/O
    FILE *socketStream = fdopen(socket, "r+");
    if (socketStream == NULL)
    {
        dieWithSystemMessage("fdopen() failed");
    }
    
    Login login;
    memset(&login, 0, sizeof(Login));
    strcpy(login.value, "kovalgek");
    
    // Encode for transmission
    uint8_t outbuf[MAX_WIRE_SIZE];
    size_t reqSize = encodeLogin(&login, outbuf, MAX_WIRE_SIZE);
    
    // Print info
    printf("Sending %lu-byte with login %s...\n", reqSize, login.value);
    
    // Frame and send
    if (putMessage(outbuf, reqSize, socketStream) < 0)
    {
        dieWithSystemMessage("putMessage() failed");
    }
    

    size_t mSize;
    uint8_t inbuf[MAX_WIRE_SIZE];
    Token token;
    
    // Receive and print response
    
    while ((mSize = getNextMesage(socketStream, inbuf, MAX_WIRE_SIZE)) > 0)
    {
        memset(&token, 0, sizeof(Token));
        
        printf("Received message (%zu bytes)\n", mSize);
        
        if (decodeToken(inbuf, mSize, &token))
        {
            printf("token=%s\n", token.value);
            
            // Create separate memory for client argument
            struct ThreadArgs *threadArgs = (struct ThreadArgs *) malloc(sizeof(struct ThreadArgs));
            if (threadArgs == NULL)
            {
                dieWithSystemMessage("malloc() failed");
            }
            threadArgs->clntSock = socket;
            
            // Create client thread
            pthread_t threadID;
            int returnValue = pthread_create(&threadID, NULL, threadMain, threadArgs);
            if (returnValue != 0)
            {
                dieWithUserMessage("pthread_create() failed", strerror(returnValue));
            }
            
            char *line = NULL;  /* forces getline to allocate with malloc */
            size_t len = 0;     /* ignored when line = NULL */
            ssize_t read;
            
            printf ("\nEnter string below [ctrl + d] to quit\n");
            
            while ((read = getline(&line, &len, stdin)) != -1)
            {
                if (read > 0)
                {
                    ClientMessage clientMessage;
                    memset(&clientMessage, 0, sizeof(ClientMessage));
                    
                    line[strlen(line) - 1] = 0;
                    strcpy(clientMessage.token, token.value);
                    strcpy(clientMessage.text, line);
                    
                    uint8_t outbuf[MAX_WIRE_SIZE];
                    size_t reqSize = encodeClientMessage(&clientMessage, outbuf, MAX_WIRE_SIZE);
                    printf("outbuf=%s\n",(char *) outbuf);
                    if (putMessage(outbuf, reqSize, socketStream) < 0)
                    {
                        dieWithSystemMessage("putMessage() failed\n");
                    }
                    else
                    {
                        printf("I'm here\n");
                    }
                }
            }
            free (line);
        }
    }
    
    fclose(socketStream);
    exit(0);
}

void *threadMain(void *threadArgs)
{
    // Guarantees that thread resources are deallocated upon return
    pthread_detach(pthread_self());
    
    // Extract socket file descriptor from argument
    int clntSock = ((struct ThreadArgs *) threadArgs)->clntSock;
    free(threadArgs); // Deallocate memory for argument
    
    handleMessages(clntSock);
    
    return (NULL);
}

void handleMessages(int socket)
{
    // Receive and print response
    
    size_t mSize;
    uint8_t inbuf[MAX_WIRE_SIZE];
    ServerMessage serverMessage;
    
    // Wrap for stream I/O
    FILE *socketStream = fdopen(socket, "r+");
    if (socketStream == NULL)
    {
        dieWithSystemMessage("fdopen() failed");
    }
    
    while ((mSize = getNextMesage(socketStream, inbuf, MAX_WIRE_SIZE)) > 0)
    {
        memset(&serverMessage, 0, sizeof(ServerMessage));
        printf("Received message (%zu bytes)\n", mSize);
        
        if (decodeServerMessage(inbuf, mSize, &serverMessage))
        {
            printf("%s: %s\n",serverMessage.name,serverMessage.text);
        }
        memset(&inbuf, 0, MAX_WIRE_SIZE);
    }
}

