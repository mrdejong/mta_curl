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

size_t CCurlEasy::WriteMemoryCallback(char *contents, size_t size, size_t nmemb)
{
	int r = 0;

	buffer.append(contents, size*nmemb);
	r = size*nmemb;

	return r;
}

void CCurlEasy::cleanMemory()
{
	buffer.clear();
}

const char* CCurlEasy::getResult()
{
	return buffer.c_str();
}

CCurlEasy::~CCurlEasy(void)
{
	curl_easy_cleanup(pCurl);
	
	delete pCurl;
}

