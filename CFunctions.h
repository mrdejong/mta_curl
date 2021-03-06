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

class CFunctions;

#ifndef __CFUNCTIONS_H
#define __CFUNCTIONS_H

#include "ml_curl.h"

#include "include/ILuaModuleManager.h"
extern ILuaModuleManager10 *pModuleManager;

#include <curl/curl.h>

#define luaL_checktable(L, n) luaL_checktype(L, n, LUA_TTABLE)

#define LUACURL_OPTIONP_UPVALUE(L, INDEX) ((CURLoption *) lua_touserdata(L, lua_upvalueindex(INDEX)))
#define LUACURL_CODEP_UPVALUE(L, INDEX) ((CURLcode *) lua_touserdata(L, lua_upvalueindex(INDEX)))

#define TRANSLATE_STRING_CURLOPTION(S) #S

class CFunctions
{
public:
	static int curl_init			( lua_State* luaVM );
	static int curl_close			( lua_State* luaVM );
	static int curl_setopt			( lua_State* luaVM );
	static int curl_cleanup			( lua_State* luaVM );
	static int curl_perform			( lua_State* luaVM );
	static int curl_escape			( lua_State* luaVM );
	static int curl_strerror		( lua_State* luaVM );
	static int curl_pause			( lua_State* luaVM );

	static int lua_curl_version			( lua_State* luaVM );

	static void registerLuaGlobal	( lua_State* luaVM, const char* name, void* value );
	static void registerIntLuaGlobal ( lua_State* luaVM, const char* name, int value );
	static void saveLuaData			( lua_State* luaVM );
	static void addEvent			( lua_State* luaVM, const char* szEventName );
	static void triggerEvent		( const string& eventName, void* userdata, const string& arg1 = "" );
	static void pr 					( const char* output );
};
#endif
