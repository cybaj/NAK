// ListIteratorOfListOfNaDbObjectId.cpp: implementation of the CListIteratorOfListOfNaDbObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "ListIteratorOfListOfNaDbObjectId.h"
#include "ListException.h"
#include <NaGeMMath.h>


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CListIteratorOfListOfNaDbObjectId::CListIteratorOfListOfNaDbObjectId(CListOfNaDbObjectId* aList) : theList(aList)
{
}

CListIteratorOfListOfNaDbObjectId::~CListIteratorOfListOfNaDbObjectId()
{
}

void CListIteratorOfListOfNaDbObjectId::SetList(CListOfNaDbObjectId* aList)
{
	theList = aList;
}

void CListIteratorOfListOfNaDbObjectId::Init()
{
	curPtr = theList->firstPtr;
}

bool CListIteratorOfListOfNaDbObjectId::More() const
{
	return (curPtr != 0);
}

bool CListIteratorOfListOfNaDbObjectId::IsFound(const unsigned long int O) const
{
	bool b = false;
	CListIteratorOfListOfNaDbObjectId li(theList);
	for(li.Init(); li.More(); li.Next())
	{
		if(li.Current() == O)
		{
			b = true;
			break;
		}
	}
	return b;
}

void CListIteratorOfListOfNaDbObjectId::Next()
{
	curPtr = (curPtr) ? curPtr->nextPtr : 0;
}

unsigned long int CListIteratorOfListOfNaDbObjectId::Current() const
{
	return (curPtr) ? curPtr->data : 0;
}

CListNodeOfNaDbObjectId* CListIteratorOfListOfNaDbObjectId::CurrentPtr() const
{
	return curPtr;
}

void CListIteratorOfListOfNaDbObjectId::SetCurrent(unsigned long int Obj)
{
	curPtr->data = Obj;
}

unsigned long int CListIteratorOfListOfNaDbObjectId::ValueAt(const int index)
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
 
