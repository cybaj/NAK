// ListOfNaGePoint3D.cpp: implementation of the CListOfPoint3D class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "ListOfPoint3D.h"
#include "ListException.h"
#include "NaGeMMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CListOfPoint3D::CListOfPoint3D() : firstPtr(0), lastPtr(0)
{
    itsCount = 0;
}


CListOfPoint3D::~CListOfPoint3D()
{


	CListNodeOfPoint3D* curPtr = firstPtr, *tmp;
	if(!IsEmpty())
	{
		while(curPtr != 0)
		{
			tmp = curPtr;
			curPtr = curPtr->nextPtr;
			delete tmp;
		}
	}
}


void CListOfPoint3D::Append(const NaGePoint3D& data)
{
	CListNodeOfPoint3D* newPtr = new CListNodeOfPoint3D(data);
	if(IsEmpty())
		firstPtr = lastPtr = newPtr;
	else
	{
		lastPtr->nextPtr = newPtr;
		lastPtr = newPtr;
	}
	++itsCount;
}


void CListOfPoint3D::Prepend(const NaGePoint3D& data)
{
	CListNodeOfPoint3D* newPtr = new CListNodeOfPoint3D(data);
	if(IsEmpty())
		firstPtr = lastPtr = newPtr;
	else
	{
		newPtr->nextPtr = firstPtr;
		firstPtr = newPtr;
	}
	++itsCount;
}

NaGePoint3D CListOfPoint3D::First() const
{
	if(IsEmpty())
		throw CListException(LIST_EMPTY);
	return firstPtr->GetData();
}

NaGePoint3D CListOfPoint3D::Last() const
{
	if(IsEmpty())
		throw CListException(LIST_EMPTY);
	return lastPtr->GetData();
}

bool CListOfPoint3D::IsEmpty() const
{
	return (firstPtr==0);
}		


void CListOfPoint3D::Clear()
{
	CListNodeOfPoint3D* curPtr = firstPtr, *tmp;
	if(!IsEmpty())
	{
		while(curPtr != 0)
		{
			tmp = curPtr;
			curPtr = curPtr->nextPtr;
			delete tmp;
		}
		
		firstPtr = lastPtr = 0;
	}
	itsCount = 0;
}

CListNodeOfPoint3D* CListOfPoint3D::NewNode(const NaGePoint3D& P)
{
	CListNodeOfPoint3D* newPtr= new CListNodeOfPoint3D(P);
	if(!newPtr)
		throw CListException(LIST_OUT_OF_MEMORY);
	newPtr->nextPtr = 0;
	return newPtr;
}
