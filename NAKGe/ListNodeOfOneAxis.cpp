// ListNodeOfNaGeOneAxis.cpp: implementation of the CListNodeOfOneAxis class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "ListNodeOfOneAxis.h"
#include "NaGeMMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CListNodeOfOneAxis::CListNodeOfOneAxis( const NaGeOneAxis& P) : data(P), nextPtr(0)
{

}

CListNodeOfOneAxis::~CListNodeOfOneAxis()
{

}

NaGeOneAxis CListNodeOfOneAxis::GetData() const
{
	return data;
}

bool CListNodeOfOneAxis::operator==(CListNodeOfOneAxis& rhs)
{
	if(*this==rhs)
		return true;
	return false;
}

bool CListNodeOfOneAxis::operator!=(CListNodeOfOneAxis& rhs)
{
	return !(*this==rhs);
}
