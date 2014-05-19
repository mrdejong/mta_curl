#include "Mtacurls.h"
#include <curl\curl.h>

/**
	Initialize the class.

	This function initializes the global curl.
*/
Mtacurls::Mtacurls( void )
{
	curl_global_init(CURL_GLOBAL_ALL);
}

/**
	Destruct this class, and cleanup curl.
*/
Mtacurls::~Mtacurls( void )
{
	DeleteAll();
	curl_global_cleanup();
}

/**
	Mtacurl* Mtacurls::Create( lua_State* luaVM, const char* url, size_t length )

	Create a new Mtacurl object.
	Push it into the list.

	Returns an Mtacurl object on success, null otherwise.
*/
Mtacurl* Mtacurls::Create( lua_State* luaVM, const char* url )
{
	Mtacurl* pMtacurl;

	if(url == NULL) {
		pMtacurl = new Mtacurl(luaVM);
	}
	else {
		pMtacurl = new Mtacurl(luaVM, url);
	}

	if(pMtacurl)
	{
		mtacurls.push_back(pMtacurl);
		return pMtacurl;
	}
	return NULL;
}

/**
	Mtacurl* Mtacurls::Get( void* pUserData )

	Find the Mtacurl object in the list.

	Returns an Mtacurl object on success, null otherwise
*/
Mtacurl* Mtacurls::Get( void* pUserData )
{
	for ( vector < Mtacurl* >::iterator iter = mtacurls.begin( ); iter != mtacurls.end( ); ++ iter )
		if( (*iter)->GetUserData( ) == pUserData )
			return *iter;
	return NULL;
}

/**
	void Mtacurls::Delete( Mtacurl* pMtaculr )
	
	Delete a Mtacurl pointer.
*/
void Mtacurls::Delete( Mtacurl* pMtacurl )
{
	pMtacurl->MakeAwaitDestruction( );
}

void Mtacurls::DeleteAll( void )
{
	unsigned int i = 0;
	while( i < mtacurls.size() )
	{
		Mtacurl* pMtacurl = mtacurls[i];
		if(!pMtacurl->IsAwaitingDestruction())
		{
			pMtacurl->MakeAwaitDestruction();
		}
	}

}

/**
	Mtacurls::DoPulse

	This function is called on each server pulse.
	
	Checks if an Mtacurl object is waiting for destruction.
	If so, destruct the object and erase it from the list.
	If not, call DoPulse on the Mtacurl object.
*/
void Mtacurls::DoPulse( )
{
	unsigned int i = 0;
	while( i < mtacurls.size() )
	{
		Mtacurl* pMtacurl = mtacurls[i];
		if ( pMtacurl )
		{
			if(pMtacurl->IsAwaitingDestruction())
			{
				mtacurls.erase( mtacurls.begin() + i );
				SAFE_DELETE(pMtacurl)
			}
		}
		else
		{
			mtacurls.erase(mtacurls.begin() + i );
		}
	}
}