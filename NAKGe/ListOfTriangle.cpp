// ListOfNaGeTriangle.cpp: implementation of the CListOfTriangle class.
//
//////////////////////////////////////////////////////////////////////


#include "stdafx.h"

#include "ListOfTriangle.h"
#include "ListException.h"
#include "NaGeMMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CListOfTriangle::CListOfTriangle() : firstPtr(0), lastPtr(0)
{
}


CListOfTriangle::~CListOfTriangle()
{


	CListNodeOfTriangle* curPtr = firstPtr, *tmp;
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


void CListOfTriangle::Append(const NaGeTriangle& data)
{
	CListNodeOfTriangle* newPtr = new CListNodeOfTriangle(data);
	if(IsEmpty())
		firstPtr = lastPtr = newPtr;
	else
	{
		lastPtr->nextPtr = newPtr;
		lastPtr = newPtr;
	}
}


void CListOfTriangle::Prepend(const NaGeTriangle& data)
{
	CListNodeOfTriangle* newPtr = new CListNodeOfTriangle(data);
	if(IsEmpty())
		firstPtr = lastPtr = newPtr;
	else
	{
		newPtr->nextPtr = firstPtr;
		firstPtr = newPtr;
	}
}

NaGeTriangle CListOfTriangle::First() const
{
	if(IsEmpty())
		throw CListException(LIST_EMPTY);
	return firstPtr->GetData();
}

NaGeTriangle CListOfTriangle::Last() const
{
	if(IsEmpty())
		throw CListException(LIST_EMPTY);
	return lastPtr->GetData();
}

bool CListOfTriangle::IsEmpty() const
{
	return (firstPtr==0);
}		


void CListOfTriangle::Clear()
{
	CListNodeOfTriangle* curPtr = firstPtr, *tmp;
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

CListNodeOfTriangle* CListOfTriangle::NewNode(const NaGeTriangle& P)
{
	CListNodeOfTriangle* newPtr= new CListNodeOfTriangle(P);
	if(!newPtr)
		throw CListException(LIST_OUT_OF_MEMORY);
	newPtr->nextPtr = 0;
	return newPtr;
}
