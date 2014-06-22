#include "CurlCollection.h"


CCurlCollection::CCurlCollection(lua_State *L)
{
	lua = L;
	curl_global_init(CURL_GLOBAL_ALL);
}


CCurlCollection::~CCurlCollection(void)
{
	DeleteAll();
	curl_global_cleanup();
}

CCurlEasy* CCurlCollection::CreateEasy(void)
{
	CCurlEasy* easy = new CCurlEasy(lua);

	m_pCurlEasy.push_back(easy);

	return easy;
}

CCurlShare* CCurlCollection::CreateShare(void)
{
	return NULL;
}

CCurlEasy* CCurlCollection::GetEasy(void* udata)
{
	for (vector<CCurlEasy*>::iterator iter = m_pCurlEasy.begin(); iter != m_pCurlEasy.end(); ++iter)
		if ((*iter)->GetUserData() == udata)
			return *iter;
	return NULL;
}

void CCurlCollection::DeleteEasy(CCurlEasy* pointer)
{
	pointer->MakeAwaitDestruction();
}

void CCurlCollection::DeleteShare(CCurlShare* pointer)
{
	return;
}

void CCurlCollection::DeleteAll()
{
	DeleteAllEasy();
}

void CCurlCollection::DeleteAllEasy()
{
	unsigned int i = 0;
	while (i < m_pCurlEasy.size())
	{
		CCurlEasy* pointer = m_pCurlEasy[i];
		if (!pointer->IsAwaitingDestruction())
		{
			pointer->MakeAwaitDestruction();
		}

		i++;
	}
}

void CCurlCollection::OnPulseDeleteEasy()
{
	unsigned int i = 0;
	while (i < m_pCurlEasy.size())
	{
		CCurlEasy* pointer = m_pCurlEasy[i];
		if (pointer)
		{
			if (pointer->IsAwaitingDestruction())
			{
				m_pCurlEasy.erase(m_pCurlEasy.begin() + i);
				SAFE_DELETE(pointer);
			}
		}
		else
		{
			m_pCurlEasy.erase(m_pCurlEasy.begin() + i);
		}

		i++;
	}
}

void CCurlCollection::DoPulse()
{
	DoPulseEasy();

	OnPulseDeleteEasy();
}

void CCurlCollection::DoPulseEasy()
{
	unsigned int i = 0;
	while (i < m_pCurlEasy.size())
	{
		CCurlEasy* pointer = m_pCurlEasy[i];
		if (!pointer->IsAwaitingDestruction())
		{
			pointer->DoPulse();
		}

		i++;
	}
}