/**
mtacurl

curl extention class
*/

#ifndef __MTACURL_H
#define __MTACURL_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string>

#include "ml_system.h"

using namespace std;

#include <curl/curl.h>

class Mtacurl
{
friend class Mtacurls;
public:
			Mtacurl					( lua_State *luaVM );
private:
			Mtacurl					( lua_State *luaVM, const char* url );
protected:
			~Mtacurl				( void );
	void	DoPulse					( void );

public:
	CURLcode setopt_boolean			( CURLoption option, bool val );
	CURLcode setopt_number			( CURLoption option, int val );
	CURLcode setopt_string			( CURLoption option, const char* val );
	CURLcode pause					( int bitmask );
	CURLcode perform				( void );

	CURLSHcode share_setopt			( CURLSHoption option, bool val );
	CURLSHcode share_setopt			( CURLSHoption option, int val );
	CURLSHcode share_setopt			( CURLSHoption option, const char* val );

	void cleanup					( void );
	char *escape					( const char* url, size_t length );
	const char* strerror			( CURLcode error );
	const char*	getResult			( void );
	void clearMemp					( void );

	bool	IsAwaitingDestruction	( void ) { return m_bAwaitingDestruction; };
	void	MakeAwaitDestruction	( void ) { m_bAwaitingDestruction = true; };
	void*	GetUserData				( void ) { return m_pUserData; };

private:
	void*			m_pUserData;
	bool			m_pConnected;
	CURL*			m_pCurl;
	bool			m_bAwaitingDestruction;

	string			response;

	CURLcode		m_pLatestCode;

	CURLSH			*m_pCurlShare = NULL;
};

#endif
