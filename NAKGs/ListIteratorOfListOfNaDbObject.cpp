// ListIteratorOfListOfNaDbObject.cpp: implementation of the CListIteratorOfListOfNaDbObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "ListIteratorOfListOfNaDbObject.h"
#include "ListException.h"
#include <NaGeMMath.h>


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CListIteratorOfListOfNaDbObject::CListIteratorOfListOfNaDbObject(CListOfNaDbObject* aList) : theList(aList)
{
}

CListIteratorOfListOfNaDbObject::~CListIteratorOfListOfNaDbObject()
{
}

void CListIteratorOfListOfNaDbObject::SetList(CListOfNaDbObject* aList)
{
	theList = aList;
}

void CListIteratorOfListOfNaDbObject::Init()
{
	curPtr = theList->firstPtr;
}

bool CListIteratorOfListOfNaDbObject::More() const
{
	return (curPtr != 0);
}

bool CListIteratorOfListOfNaDbObject::IsFound(const NaDbObject* O) const
{
	bool b = false;
	CListIteratorOfListOfNaDbObject li(theList);
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

void CListIteratorOfListOfNaDbObject::Next()
{
	curPtr = (curPtr) ? curPtr->nextPtr : 0;
}

NaDbObject* CListIteratorOfListOfNaDbObject::Current() const
{
	return (curPtr) ? curPtr->data : 0;
}

CListNodeOfNaDbObject* CListIteratorOfListOfNaDbObject::CurrentPtr() const
{
	return curPtr;
}

void CListIteratorOfListOfNaDbObject::SetCurrent(NaDbObject* Obj)
{
	curPtr->data = Obj;
}

NaDbObject* CListIteratorOfListOfNaDbObject::ValueAt(const int index)
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
 
