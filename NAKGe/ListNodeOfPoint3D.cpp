// ListNodeOfNaGePoint3D.cpp: implementation of the CListNodeOfPoint3D class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "ListNodeOfPoint3D.h"
#include "NaGeMMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CListNodeOfPoint3D::CListNodeOfPoint3D( const NaGePoint3D& P) : data(P), nextPtr(0)
{

}

CListNodeOfPoint3D::~CListNodeOfPoint3D()
{

}

NaGePoint3D CListNodeOfPoint3D::GetData() const
{
	return data;
}

bool CListNodeOfPoint3D::operator==(CListNodeOfPoint3D& rhs)
{
	if(*this==rhs)
		return true;
	return false;
}

bool CListNodeOfPoint3D::operator!=(CListNodeOfPoint3D& rhs)
{
	return !(*this==rhs);
}
