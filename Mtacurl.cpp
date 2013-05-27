/****************************************************************
*        Multi Theft Auto : San Andreas - Curl module.
*        Info: Win32/Linux Curl
*        Developers: mrdejong
****************************************************************/

#include "Mtacurl.h"

int write_data(char *data, size_t size, size_t nmemb, string* buffer)
{
	int result = 0;
	if(buffer != NULL)
	{
		buffer->append(data, size * nmemb);
		result = size * nmemb;
	}
	return result;
}

/**
Curl stuff!
*/
Mtacurl::Mtacurl( lua_State *luaVM )
{
	m_pUserData				= lua_newuserdata(luaVM, 128);
	m_pCurl					= curl_easy_init();
	m_pConnected			= true;
	m_bAwaitingDestruction	= false;
}

Mtacurl::Mtacurl( lua_State *luaVM, const char* url )
{
	m_pUserData				= lua_newuserdata(luaVM, 128);
	m_pCurl					= curl_easy_init();
	m_pConnected			= true;
	m_bAwaitingDestruction	= false;

	curl_easy_setopt(m_pCurl, CURLOPT_URL, url);
}

Mtacurl::~Mtacurl( )
{
	curl_easy_cleanup(m_pCurl);
	m_pCurl					= NULL;
	m_pUserData				= NULL;
	m_pConnected			= false;
}

CURLcode Mtacurl::setopt_boolean( CURLoption option, bool val)
{
	return curl_easy_setopt(m_pCurl, option, val);
}

CURLcode Mtacurl::setopt_number( CURLoption option, int val)
{
	return curl_easy_setopt(m_pCurl, option, val);
}

CURLcode Mtacurl::setopt_string( CURLoption option, const char* val)
{
	return curl_easy_setopt(m_pCurl, option, val);
}

CURLcode Mtacurl::perform( void )
{
	curl_easy_setopt( m_pCurl, CURLOPT_WRITEFUNCTION, write_data );
	curl_easy_setopt( m_pCurl, CURLOPT_WRITEDATA, &response );

	return curl_easy_perform( m_pCurl );
}

void Mtacurl::clearMemp( void )
{
	response.clear();
}

CURLcode Mtacurl::pause( int bitmask )
{
	return curl_easy_pause(m_pCurl, bitmask);
}

const char* Mtacurl::getResult( void )
{
	return response.c_str();
}

void Mtacurl::cleanup( void )
{
	return curl_easy_cleanup(m_pCurl);
}

char *Mtacurl::escape( const char* url, size_t length )
{
	return curl_easy_escape(m_pCurl, url, length);
}

const char* Mtacurl::strerror( CURLcode error )
{
	return curl_easy_strerror( error );
}

void Mtacurl::DoPulse( )
{
	// Everything here sucks like hell....
	/**if(sizeof(m_pBuffer) > 0)
	{
		CFunctions::triggerEvent("onCurlResult", GetUserData());
	}*/
}