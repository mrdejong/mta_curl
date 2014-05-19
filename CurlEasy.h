#pragma once

#include <curl\curl.h>

class CCurlEasy
{
public:
	CCurlEasy(void);

	~CCurlEasy(void);

	CURL* getPointer(void);

private:
	CURL* pCurl;
};

