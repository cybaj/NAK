// ListNodeOfNaDbObject.cpp: implementation of the CListNodeOfNaDbObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "ListNodeOfNaDbObject.h"
#include <NaGeMMath.h>


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CListNodeOfNaDbObject::CListNodeOfNaDbObject( NaDbObject* P) : data(P), nextPtr(0)
{

}

CListNodeOfNaDbObject::~CListNodeOfNaDbObject()
{
	if(data && data->DelRef() == 1)
		delete data;
}

NaDbObject* CListNodeOfNaDbObject::GetData() const
{
	return data;
}

bool CListNodeOfNaDbObject::operator==(CListNodeOfNaDbObject& rhs)
{
	if(*this==rhs)
		return true;
	return false;
}

bool CListNodeOfNaDbObject::operator!=(CListNodeOfNaDbObject& rhs)
{
	return !(*this==rhs);
}
