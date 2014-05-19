#include "CurlCollection.h"


CCurlCollection::CCurlCollection(void)
{
}


CCurlCollection::~CCurlCollection(void)
{
}

CCurlEasy* CCurlCollection::CreateEasy(void)
{
	CCurlEasy* easy = new CCurlEasy();

	m_pCurlEasy.push_back(easy);

	return NULL;
}

CCurlShare* CCurlCollection::CreateShare(void)
{
	return NULL;
}

void CCurlCollection::DeleteEasy(CCurlEasy* pointer)
{
	return;
}

void CCurlCollection::DeleteShare(CCurlShare* pointer)
{
	return;
}

void CCurlCollection::DeleteAll()
{

}

void CCurlCollection::DoPulse()
{

}