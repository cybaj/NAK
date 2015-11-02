// ListIteratorOfListOfNaGeTriangle.cpp: implementation of the CListIteratorOfListOfTriangle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "ListIteratorOfListOfTriangle.h"
#include "ListException.h"
#include "NaGeMMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CListIteratorOfListOfTriangle::CListIteratorOfListOfTriangle(CListOfTriangle* aList) : theList(aList)
{
}

CListIteratorOfListOfTriangle::~CListIteratorOfListOfTriangle()
{
}

void CListIteratorOfListOfTriangle::SetList(CListOfTriangle* aList)
{
	theList = aList;
}

void CListIteratorOfListOfTriangle::Init()
{
	curPtr = theList->firstPtr;
}

bool CListIteratorOfListOfTriangle::More() const
{
	return (curPtr != 0);
}

void CListIteratorOfListOfTriangle::Next()
{
	curPtr = (curPtr) ? curPtr->nextPtr : 0;
}

NaGeTriangle CListIteratorOfListOfTriangle::Current() const
{
	return (curPtr) ? curPtr->data : NaGeTriangle();
}

NaGeTriangle CListIteratorOfListOfTriangle::ValueAt(const int index)
{
	int cnt =0;
	Init();
	while(curPtr != 0)
	{
		Next();
		cnt++;
	}
	
	if(cnt < index)
		throw CListException(LIST_BOUND_UPPER);
		
	else if(index<1)
		throw CListException(LIST_BOUND_LOWER);
		
	/*else*/ if(index ==1 )
		return theList->firstPtr->data;
	else
	{
		Init();
		for(int i=1; i < index; i++)
		{
			if(curPtr->nextPtr == 0)
				break;
			Next();
		}
		
		return curPtr->data;
	}
		
}
 
