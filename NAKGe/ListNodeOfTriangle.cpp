// ListNodeOfNaGeTriangle.cpp: implementation of the CListNodeOfTriangle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "ListNodeOfTriangle.h"
#include "NaGeMMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CListNodeOfTriangle::CListNodeOfTriangle( const NaGeTriangle& P) : data(P), nextPtr(0)
{

}

CListNodeOfTriangle::~CListNodeOfTriangle()
{

}

NaGeTriangle CListNodeOfTriangle::GetData() const
{
	return data;
}

bool CListNodeOfTriangle::operator==(CListNodeOfTriangle& rhs)
{
	if(*this==rhs)
		return true;
	return false;
}

bool CListNodeOfTriangle::operator!=(CListNodeOfTriangle& rhs)
{
	return !(*this==rhs);
}
