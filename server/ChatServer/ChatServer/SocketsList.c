#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "SocketsList.h"

struct SocketInfo *head;

bool removeSocket(int socket)
{
   SocketInfo *current = head;
   SocketInfo *previous = NULL;
	
   //if list is empty
   if(head == NULL)
   {
      return false;
   }

   //navigate through list
   while(current->socket != socket)
   {
      if(current->next == NULL)
      {
         return false;
      }
      else
      {
         previous = current;
         current = current->next;
      }
   }

   if(current == head)
   {
      head = head->next;
   }
   else
   {
      previous->next = current->next;
   }    

   free(current);	
   return true;
}

SocketInfo *findSocket(int socket)
{
   SocketInfo *current = head;

   if(head == NULL)
   {
      return NULL;
   }

   while(current->socket != socket)
   {
      if(current->next == NULL)
      {
         return NULL;
      }
      else
      {
         current = current->next;
      }
   }      
	
   return current;
}

bool addSocket(int socket, FILE *stream)
{
	if (findSocket(socket))
    {
		return false;
    }

	SocketInfo *socketInfo = (SocketInfo *)malloc(sizeof(SocketInfo));
    socketInfo->socket = socket;
    socketInfo->stream = stream;
    socketInfo->next = head;
	head = socketInfo;
	return true;	
}

void printSocketsList() 
{
   SocketInfo *current = head;
   printf("\n[ ");
	
   while(current != NULL)
   {
      printf("(%d) ", current->socket);
	  current = current->next;
   }
	
   printf(" ]");
}

