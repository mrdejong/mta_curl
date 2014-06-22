#pragma once
#include "ml_system.h"
#include <curl\curl.h>

using namespace std;

class CCurlEasy
{
public:
	CCurlEasy(lua_State *L);

	~CCurlEasy(void);

	CURL* getPointer(void);
	void* getUserData();

	bool	IsAwaitingDestruction(void) { return bAwaitingDestruction; };
	void	MakeAwaitDestruction(void) { bAwaitingDestruction = true; };
	void*	GetUserData(void) { return pUserData; };

	size_t WriteMemoryCallback(char *contents, size_t size, size_t nmemb);
	const char* getResult();

	void	cleanMemory();

	void	DoPulse();

private:
	CURL* pCurl;
	void* pUserData;

	string buffer;

	bool bAwaitingDestruction;
};

