#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "UsersList.h"

struct User *userHead;

bool removeByName(const char *name)
{
   User *current = userHead;
   User *previous = NULL;
	
   //if list is empty
   if(userHead == NULL)
   {
      return false;
   }

   //navigate through list
   while(strcmp(current->name, name))
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

   if(current == userHead)
   {
      userHead = userHead->next;
   }
   else
   {
      previous->next = current->next;
   }    

   free(current);	
   return true;
}

User *findByName(const char *name)
{
   User *current = userHead;

   if(userHead == NULL)
   {
      return NULL;
   }

   while(strcmp(current->name, name))
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

User *findByToken(const char *token)
{
   User *current = userHead;

   if(userHead == NULL)
   {
      return NULL;
   }

   while(strcmp(current->token, token))
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

bool addUser(const char *name, const char *token)
{
	if (findByName(name) || findByToken(token))
    {
		return false;
    }

	User *user = (User *)malloc(sizeof(User));

	strcpy(user->name, name);
	strcpy(user->token, token);

    user->next = userHead;
	userHead = user;
	return true;	
}

void printUsers() 
{
   User *current = userHead;
   printf("\n[ ");
	
   while(current != NULL)
   {
      printf("(%s,%s) ",current->name, current->token);
	  current = current->next;
   }
	
   printf(" ]");
}

