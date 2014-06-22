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
	
	CURLcode setoptBool(CURLoption option, bool val);
	CURLcode setoptNumber(CURLoption option, int val);
	CURLcode setoptString(CURLoption option, const char* val);

	bool	IsAwaitingDestruction(void) { return bAwaitingDestruction; };
	void	MakeAwaitDestruction(void) { bAwaitingDestruction = true; };
	void*	GetUserData(void) { return pUserData; };

	void	DoPulse();

private:
	CURL* pCurl;
	void* pUserData;

	bool bAwaitingDestruction;
};

