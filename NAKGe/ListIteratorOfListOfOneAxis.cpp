// ListIteratorOfListOfNaGeOneAxis.cpp: implementation of the CListIteratorOfListOfOneAxis class.
//
//////////////////////////////////////////////////////////////////////


#include "stdafx.h"

#include "ListIteratorOfListOfOneAxis.h"
#include "ListException.h"
#include "NaGeMMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CListIteratorOfListOfOneAxis::CListIteratorOfListOfOneAxis(CListOfOneAxis* aList) : theList(aList)
{
}

CListIteratorOfListOfOneAxis::~CListIteratorOfListOfOneAxis()
{
}

void CListIteratorOfListOfOneAxis::SetList(CListOfOneAxis* aList)
{
    theList = aList;
}

void CListIteratorOfListOfOneAxis::Init()
{
    curPtr = theList->firstPtr;
}

bool CListIteratorOfListOfOneAxis::More() const
{
    return (curPtr != 0);
}

void CListIteratorOfListOfOneAxis::Next()
{
    curPtr = (curPtr) ? curPtr->nextPtr : 0;
}

NaGeOneAxis CListIteratorOfListOfOneAxis::Current() const
{
    return (curPtr) ? curPtr->data : NaGeOneAxis();
}

NaGeOneAxis CListIteratorOfListOfOneAxis::ValueAt(const int index)
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

