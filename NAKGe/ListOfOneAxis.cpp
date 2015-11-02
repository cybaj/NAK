// ListOfNaGeOneAxis.cpp: implementation of the CListOfOneAxis class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "ListOfOneAxis.h"
#include "ListException.h"
#include "NaGeMMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CListOfOneAxis::CListOfOneAxis() : firstPtr(0), lastPtr(0)
{
}


CListOfOneAxis::~CListOfOneAxis()
{


	CListNodeOfOneAxis* curPtr = firstPtr, *tmp;
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


void CListOfOneAxis::Append(const NaGeOneAxis& data)
{
	CListNodeOfOneAxis* newPtr = new CListNodeOfOneAxis(data);
	if(IsEmpty())
		firstPtr = lastPtr = newPtr;
	else
	{
		lastPtr->nextPtr = newPtr;
		lastPtr = newPtr;
	}
}


void CListOfOneAxis::Prepend(const NaGeOneAxis& data)
{
	CListNodeOfOneAxis* newPtr = new CListNodeOfOneAxis(data);
	if(IsEmpty())
		firstPtr = lastPtr = newPtr;
	else
	{
		newPtr->nextPtr = firstPtr;
		firstPtr = newPtr;
	}
}

NaGeOneAxis CListOfOneAxis::First() const
{
	if(IsEmpty())
		throw CListException(LIST_EMPTY);
	return firstPtr->GetData();
}

NaGeOneAxis CListOfOneAxis::Last() const
{
	if(IsEmpty())
		throw CListException(LIST_EMPTY);
	return lastPtr->GetData();
}

bool CListOfOneAxis::IsEmpty() const
{
	return (firstPtr==0);
}		


void CListOfOneAxis::Clear()
{
	CListNodeOfOneAxis* curPtr = firstPtr, *tmp;
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
}

CListNodeOfOneAxis* CListOfOneAxis::NewNode(const NaGeOneAxis& P)
{
	CListNodeOfOneAxis* newPtr= new CListNodeOfOneAxis(P);
	if(!newPtr)
		throw CListException(LIST_OUT_OF_MEMORY);
	newPtr->nextPtr = 0;
	return newPtr;
}
