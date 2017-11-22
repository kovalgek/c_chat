#include <stdio.h>
#include <stdbool.h>

struct SocketInfo 
{
	int socket;
	FILE *stream;
	struct SocketInfo *next;
};
typedef struct SocketInfo SocketInfo; 


bool removeSocket(int socket);
SocketInfo *findSocket(int socket);
bool addSocket(int socket, FILE *stream);
void printSocketsList(void);
