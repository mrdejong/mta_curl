#include "CurlEasy.h"

CCurlEasy::CCurlEasy(lua_State *L)
{
	pCurl = curl_easy_init();
	pUserData = lua_newuserdata(L, 128);
}

CURL* CCurlEasy::getPointer()
{
	return pCurl;
}

void* CCurlEasy::getUserData()
{
	return pUserData;
}

void CCurlEasy::DoPulse()
{

}

CCurlEasy::~CCurlEasy(void)
{
	curl_easy_cleanup(pCurl);
	
	delete pCurl;
}

