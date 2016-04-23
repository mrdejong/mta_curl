#ifndef __CCURLCOLLECTION_H
#define __CCURLCOLLECTION_H

#include <string>
#include "ml_curl.h"
#include "CurlEasy.h"
#include "CurlShare.h"

class CCurlEasy;
class CCurlShare;
class CCurlCollection
{
public:
						CCurlCollection(lua_State *L);
						~CCurlCollection(void);

	CCurlEasy*			CreateEasy( void );
	CCurlShare*			CreateShare( void );

	CCurlEasy*			GetEasy(void* udata);

	void				DeleteEasy(CCurlEasy *pointer);
	void				DeleteShare(CCurlShare *pointer);

	void				DeleteAll();
	void				DeleteAllEasy();

	void				DoPulse();
	void				DoPulseEasy();

private:
	void				OnPulseDeleteEasy();

private:
	vector<CCurlEasy*> m_pCurlEasy;
	vector<CCurlShare*> m_pCurlShare;

	lua_State *lua;
};

#endif
