/*********************************************************
*
*  Multi Theft Auto: San Andreas
*
*  Curl module for mta.
*
*  Developers:
*  Alexander de Jong <alexander.t.dejong@gmail.com>
*
*********************************************************/
#include <stdlib.h>
#include "CFunctions.h"
#include "extra/CLuaArguments.h"

lua_State* gLuaVM;
extern Mtacurls* mtacurls;
extern CCurlCollection* curlCollection;


int CFunctions::curl_init( lua_State *luaVM )
{
	if(luaVM)
	{
		CCurlEasy* pointer = curlCollection->CreateEasy();

		if (!pointer)
		{
			lua_pushnil(luaVM);
			return 1;
		}

		if( lua_type( luaVM, 1 ) == LUA_TSTRING )
		{
			curl_easy_setopt(pointer->getPointer(), CURLOPT_URL, lua_tostring(luaVM, 1));
		}

		lua_pushlightuserdata(luaVM, pointer->GetUserData());
		return 1;
	}

	lua_pushboolean( luaVM, false );
	return 1;
}

int CFunctions::curl_close( lua_State* luaVM )
{
	if(luaVM)
	{
		if( lua_type( luaVM, 1 ) == LUA_TLIGHTUSERDATA )
		{
			Mtacurl* pMtacurl = mtacurls->Get( lua_touserdata( luaVM, 1 ) );
			if( pMtacurl != NULL )
			{
				pMtacurl->MakeAwaitDestruction();

				lua_pushboolean( luaVM, true );
				return 1;
			}
		}
	}

	lua_pushboolean( luaVM, false );
	return 1;
}

int CFunctions::curl_setopt( lua_State* luaVM )
{
	if(luaVM)
	{
		if( lua_type( luaVM, 1 ) == LUA_TLIGHTUSERDATA &&
			lua_type( luaVM, 2 ) == LUA_TLIGHTUSERDATA )
		{
			Mtacurl* pMtacurl = mtacurls->Get( lua_touserdata( luaVM, 1 ) );

			if( pMtacurl != NULL )
			{				
				CURLoption* option = (CURLoption*)lua_touserdata( luaVM, 2); // options_opt[(int)lua_tonumber( luaVM, 2 )];
				CURLcode code;

				switch(lua_type( luaVM, 3))
				{
					case LUA_TBOOLEAN:
						// call boolean setopt
						code = pMtacurl->setopt_boolean((CURLoption&)option, lua_toboolean(luaVM, 3));
					break;

					case LUA_TNUMBER:
						// call number setopt
						code = pMtacurl->setopt_number((CURLoption&)option, lua_tonumber(luaVM, 3));
					break;

					case LUA_TSTRING:
						// call string setopt
						code = pMtacurl->setopt_string((CURLoption&)option, lua_tostring(luaVM, 3));
					break;

				}

				if( code )
				{
					// lua_pushnumber( luaVM, code_str[code] );
					lua_pushlightuserdata( luaVM, (void*)code);
					return 1;
				}
			}
		}
	}
	lua_pushboolean(luaVM, false);
	return 1;
}

int CFunctions::curl_cleanup( lua_State* luaVM )
{
	if( luaVM )
	{
		if( lua_type( luaVM, 1 ) == LUA_TLIGHTUSERDATA )
		{
			Mtacurl* pMtacurl = mtacurls->Get( lua_touserdata( luaVM, 1 ) );

			if(pMtacurl != NULL)
			{
				pMtacurl->cleanup();
				lua_pushboolean( luaVM, true );
				return 1;
			}
		}
	}

	lua_pushboolean( luaVM, false );
	return 1;
}

int CFunctions::curl_escape( lua_State* luaVM )
{
	if( luaVM )
	{
		if( lua_type( luaVM, 1 ) == LUA_TLIGHTUSERDATA &&
			lua_type( luaVM, 2 ) == LUA_TSTRING )
		{
			Mtacurl* pMtacurl = mtacurls->Get( lua_touserdata( luaVM, 1) );

			if( pMtacurl != NULL )
			{
				size_t length = 0;
				// const char* url = lua_tostring( luaVM, 2 );
				const char* url = luaL_checklstring( luaVM, 2, &length );
				char* escape_url = pMtacurl->escape( url, length );

				lua_pushstring( luaVM, escape_url );
				// curl_free(escape_url);
				return 1;
			}
		}
	}

	lua_pushnil( luaVM );
	return 1;
}

int CFunctions::curl_perform( lua_State* luaVM )
{
	if( luaVM )
	{
		if( lua_type( luaVM, 1 ) == LUA_TLIGHTUSERDATA )
		{
			Mtacurl* pMtacurl = mtacurls->Get( lua_touserdata( luaVM, 1) );

			if( pMtacurl != NULL )
			{
				CURLcode code = pMtacurl->perform();

				// What if the call went wrong? FIX
				lua_pushlightuserdata(luaVM, (void*)code);
				lua_pushstring(luaVM, pMtacurl->getResult());

				pMtacurl->clearMemp();

				return 2;
			}
		}
	}

	lua_pushboolean( luaVM, false );
	return 1;
}

/**
	CFunctions curl_strerror(lua_State luaVM)

	This will output the error string and not the number

	@lua curlStrerror( CURL handler, CURLcode code );
*/
int CFunctions::curl_strerror( lua_State* luaVM )
{
	if( luaVM )
	{
		if( lua_type( luaVM, 1 ) == LUA_TLIGHTUSERDATA &&
			lua_type( luaVM, 2 ) == LUA_TLIGHTUSERDATA )
		{
			Mtacurl* pMtacurl = mtacurls->Get( lua_touserdata( luaVM, 1 ) );

			if( pMtacurl != NULL )
			{
				CURLcode* code = (CURLcode*)lua_touserdata(luaVM, 2);
				lua_pushstring(luaVM, pMtacurl->strerror( (CURLcode&)code ) );
				return 1;
			}
		}
	}

	lua_pushnil( luaVM );
	return 1;
}

/**
	CFunctions curl_pause(lua_State luaVM)

	This will pause curl, you can use as the second argument:
		CURLPAUSE_RECV 		- Pause recieving
		CURLPAUSE_SEND		- Pause sending
		CURLPAUSE_ALL		- Pause all
		CURLPAUSE_CONT		- Start all

	The first argument is the curl handler.

	@lua curlPause( CURL handler, int bitmask );
*/
int CFunctions::curl_pause(lua_State* luaVM)
{
	if(luaVM)
	{
		if( lua_type(luaVM, 1) == LUA_TLIGHTUSERDATA &&
			lua_type(luaVM, 2) == LUA_TNUMBER)
		{
			Mtacurl* pMtacurl = mtacurls->Get( lua_touserdata(luaVM, 1));

			if( pMtacurl != NULL) 
			{
				CURLcode code = pMtacurl->pause(lua_tonumber(luaVM, 2));
				lua_pushlightuserdata(luaVM, (void*)code);
				return 1;
			}
		}
	}
	lua_pushnil(luaVM);
	return 1;
}

/**
	CFunctions lua_curl_version ( lua_State luaVM )
	Push out a version string of libcurl

	@lua string curlVersion( void );
*/
int CFunctions::lua_curl_version( lua_State* luaVM )
{
	if(luaVM)
	{
		lua_pushstring( luaVM, curl_version() );
		return 1;
	}

	return 0;
}

/**
	Register a lua global.

	This is used internal.
*/
void CFunctions::registerLuaGlobal( lua_State* luaVM, const char* name, void* value )
{
	lua_pushlightuserdata(luaVM, value);
	lua_setglobal(luaVM, name);
}

void CFunctions::registerIntLuaGlobal ( lua_State* luaVM, const char* name, int value )
{
	lua_pushnumber( luaVM, value );
	lua_setglobal(luaVM, name);
}

void CFunctions::saveLuaData( lua_State *luaVM )
{
	gLuaVM = luaVM;
}

void CFunctions::addEvent(lua_State* luaVM, const char* szEventName)
{
	CLuaArguments args;
	args.PushString(szEventName);
	args.PushBoolean(true);
	args.Call(luaVM, "addEvent");
}

void CFunctions::triggerEvent(const string& eventName, void* userdata, const string& arg1)
{
	CLuaArguments args;
	args.PushString(eventName.c_str());

	lua_getglobal(gLuaVM, "root");
	CLuaArgument RootElement(gLuaVM, -1);

	args.PushUserData(RootElement.GetLightUserData());
	args.PushUserData(userdata);

	if (arg1.length() > 0)
		args.PushString(arg1.c_str());

	args.Call(gLuaVM, "triggerEvent");
}

void CFunctions::pr( const char* output )
{
	if(MODULE_DEV == 1)
		pModuleManager->DebugPrintf(gLuaVM, output);
}