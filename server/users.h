#include <stdbool.h>

static const int MAX_NAME = 128;
static const int MAX_TOKEN = 128;

struct User
{
	char name[MAX_NAME];
	char token[MAX_TOKEN];
	struct User *next;
};
typedef struct User User;

bool removeByName(const char *name);
bool addUser(const char *name, const char *token);
User *findByToken(const char *token);
User *findByName(const char *name);
