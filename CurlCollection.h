#ifndef __CCURLCOLLECTION_H
#define __CCURLCOLLECTION_H

#include <string>
#include "ml_system.h"
#include "CurlEasy.h"
#include "CurlShare.h"

class CCurlEasy;
class CCurlShare;
class CCurlCollection
{
public:
						CCurlCollection(void);
						~CCurlCollection(void);

	CCurlEasy*			CreateEasy( void );
	CCurlShare*			CreateShare( void );

	void				DeleteEasy(CCurlEasy *pointer);
	void				DeleteShare(CCurlShare *pointer);

	void				DeleteAll();

	void				DoPulse();


private:
	vector<CCurlEasy*> m_pCurlEasy;
	vector<CCurlShare*> m_pCurlShare;
};

#endif