#include "CurlEasy.h"

CCurlEasy::CCurlEasy()
{
	pCurl = curl_easy_init();
}

CURL* CCurlEasy::getPointer()
{
	return pCurl;
}

CCurlEasy::~CCurlEasy(void)
{
	curl_easy_cleanup(pCurl);
	
	delete pCurl;
}

