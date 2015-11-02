// ListIteratorOfListOfNaGePoint3D.cpp: implementation of the CListIteratorOfListOfPoint3D class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "ListIteratorOfListOfPoint3D.h"
#include "ListException.h"
#include "NaGeMMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CListIteratorOfListOfPoint3D::CListIteratorOfListOfPoint3D(CListOfPoint3D* aList) : theList(aList)
{
}

CListIteratorOfListOfPoint3D::~CListIteratorOfListOfPoint3D()
{
}

void CListIteratorOfListOfPoint3D::SetList(CListOfPoint3D* aList)
{
	theList = aList;
}

void CListIteratorOfListOfPoint3D::Init()
{
	curPtr = theList->firstPtr;
}

bool CListIteratorOfListOfPoint3D::More() const
{
	return (curPtr != 0);
}

void CListIteratorOfListOfPoint3D::Next()
{
	curPtr = (curPtr) ? curPtr->nextPtr : 0;
}

NaGePoint3D CListIteratorOfListOfPoint3D::Current() const
{
	return (curPtr) ? curPtr->data : NaGePoint3D();
}

NaGePoint3D CListIteratorOfListOfPoint3D::ValueAt(const int index)
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
 
