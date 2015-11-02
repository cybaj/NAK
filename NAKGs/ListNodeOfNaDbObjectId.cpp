// ListNodeOfNaDbObjectId.cpp: implementation of the CListNodeOfNaDbObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "ListNodeOfNaDbObjectId.h"
#include <NaGeMMath.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CListNodeOfNaDbObjectId::CListNodeOfNaDbObjectId(unsigned long int P) : data(P), nextPtr(0)
{

}

CListNodeOfNaDbObjectId::~CListNodeOfNaDbObjectId()
{

}

unsigned long int CListNodeOfNaDbObjectId::GetData() const
{
	return data;
}

bool CListNodeOfNaDbObjectId::operator==(CListNodeOfNaDbObjectId& rhs)
{
	if(*this==rhs)
		return true;
	return false;
}

bool CListNodeOfNaDbObjectId::operator!=(CListNodeOfNaDbObjectId& rhs)
{
	return !(*this==rhs);
}
