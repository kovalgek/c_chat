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
#include <pthread.h>
#include <stdlib.h>

#include "../../../common/TCPServerUtility.h"
#include "../../../common/LoginEncodingText.h"
#include "../../../common/MessageEncodingText.h"
#include "../../../common/ErrorHelper.h"
#include "../../../common/DelimiterFramer.h"
#include "UsersList.h"
#include "SocketsList.h"
#include <uuid/uuid.h>

void handleTCPServer(int clntSocket);
void *threadMain(void *arg); // Main program of a thread

// Structure of arguments to pass to client thread
struct ThreadArgs
{
    int clntSock; // Socket descriptor for client
};

int main(int argc, char *argv[])
{
    if (argc != 2) // Test for correct number of arguments
    {
        dieWithUserMessage("Parameter(s)", "<Server Port/Service>");
    }
    
    int servSock = setupTCPServerSocket(argv[1]);
    
    for (;;)
    {
        // Wait for a client to connect
        int clntSock = acceptTCPConnection(servSock);
        
        // Create separate memory for client argument
        struct ThreadArgs *threadArgs = (struct ThreadArgs *) malloc(sizeof(struct ThreadArgs));
        if (threadArgs == NULL)
        {
            dieWithSystemMessage("malloc() failed");
        }
        threadArgs->clntSock = clntSock;
        
        // Create client thread
        pthread_t threadID;
        int returnValue = pthread_create(&threadID, NULL, threadMain, threadArgs);
        if (returnValue != 0)
        {
            dieWithUserMessage("pthread_create() failed", strerror(returnValue));
        }
        printf("with thread %lu\n", (unsigned long int) threadID);
    }
}

void handleTCPServer(int clntSocket)
{
    // Create an input stream from the socket
    FILE *channel = fdopen(clntSocket, "r+");
    if (channel == NULL)
    {
        dieWithSystemMessage("fdopen() failed");
    }
    
    // save socket to list
    if (!addSocket(clntSocket, channel))
    {
        dieWithSystemMessage("can't save socket to list");
    }
    
    // Receive messages until connection closes
    size_t mSize;
    uint8_t inBuf[MAX_WIRE_SIZE];
    Login login;
    ClientMessage clientMessage;
    
    while ((mSize = getNextMesage(channel, inBuf, MAX_WIRE_SIZE)) > 0)
    {
        memset(&login, 0, sizeof(Login));
        memset(&clientMessage, 0, sizeof(ClientMessage));
        
        printf("Received message (%zu bytes)\n", mSize);
        
        if (decodeLogin(inBuf, mSize, &login))
        {
            printf("login: %s\n", login.value);
            
            uuid_t uuid;
            uuid_generate_time(uuid);
            
            char uuid_str[37];
            uuid_unparse_lower(uuid, uuid_str);
            printf("generate uuid=%s\n", uuid_str);
            addUser(login.value, uuid_str);
            printUsers();
            
            Token token;
            memset(&token, 0, sizeof(Token));
            strcpy(token.value, uuid_str);
            
            uint8_t outBuf[MAX_WIRE_SIZE];
            mSize = encodeToken(&token, outBuf, MAX_WIRE_SIZE);
            if (putMessage(outBuf, mSize, channel) < 0)
            {
                fputs("Error framing/outputting message\n", stderr);
                break;
            }
            else
            {
                printf("Processed login:%s token:%s\n", login.value, token.value);
            }
            //fflush(channel);
        }
        else if (decodeClientMessage(inBuf, mSize, &clientMessage))
        {
            
            ServerMessage serverMessage;
            memset(&serverMessage, 0, sizeof(ServerMessage));
            strcpy(serverMessage.name, "Jopa");
            strcpy(serverMessage.text, "qwe"/*clientMessage.text*/);
            
            
            uint8_t outBuf[MAX_WIRE_SIZE];
            mSize = encodeServerMessage(&serverMessage, outBuf, MAX_WIRE_SIZE);
            if (putMessage(outBuf, mSize, channel) < 0)
            {
                fputs("Error framing/outputting message\n", stderr);
                break;
            }
            else
            {
                printf("Processed clientMessage name:%s text:%s\n", serverMessage.name, serverMessage.text);
            }
            
        }
        else
        {
            fputs("Parse error, closing connection.\n", stderr);
            break;
        }
    }
    puts("Client finished");
    //fclose(channel);
}

void *threadMain(void *threadArgs)
{
    // Guarantees that thread resources are deallocated upon return
    pthread_detach(pthread_self());
    
    // Extract socket file descriptor from argument
    int clntSock = ((struct ThreadArgs *) threadArgs)->clntSock;
    free(threadArgs); // Deallocate memory for argument
    
    handleTCPServer(clntSock);
    
    return (NULL);
}

