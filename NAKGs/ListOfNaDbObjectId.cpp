// ListOfNaDbObject.cpp: implementation of the CListOfNaDbObjectId class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "ListOfNaDbObjectId.h"
#include "ListIteratorOfListOfNaDbObjectId.h"
#include "ListException.h"
#include <NaGeMMath.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CListOfNaDbObjectId::CListOfNaDbObjectId() : firstPtr(0), lastPtr(0)
{
}


CListOfNaDbObjectId::~CListOfNaDbObjectId()
{
	CListNodeOfNaDbObjectId* curPtr = firstPtr, *tmp;
	if(!IsEmpty())
	{
		while(curPtr != 0)
		{
			tmp = curPtr;
			if(tmp->data!=0)//
			{
				tmp->data = 0;
			}
			curPtr = curPtr->nextPtr;
			delete tmp;
		}
	}
}


void CListOfNaDbObjectId::Append(unsigned long int data)
{
	CListNodeOfNaDbObjectId* newPtr = new CListNodeOfNaDbObjectId(data);
	if(IsEmpty())
		firstPtr = lastPtr = newPtr;
	else
	{
		lastPtr->nextPtr = newPtr;
		lastPtr = newPtr;
	}

}


void CListOfNaDbObjectId::Prepend(unsigned long int data)
{
	CListNodeOfNaDbObjectId* newPtr = new CListNodeOfNaDbObjectId(data);
	if(IsEmpty())
		firstPtr = lastPtr = newPtr;
	else
	{
		newPtr->nextPtr = firstPtr;
		firstPtr = newPtr;
	}
}

unsigned long int CListOfNaDbObjectId::First() const
{
	if(IsEmpty())
		throw CListException(LIST_EMPTY);
	return firstPtr->GetData();
}

unsigned long int CListOfNaDbObjectId::Last() const
{
	if(IsEmpty())
		throw CListException(LIST_EMPTY);
	return lastPtr->GetData();
}


CListNodeOfNaDbObjectId* CListOfNaDbObjectId::Previous(const unsigned long int O)
{
	CListIteratorOfListOfNaDbObjectId it(this);
	for(it.Init(); it.More(); it.Next())
	{
		if(O == it.CurrentPtr()->nextPtr->data)
			break;
	}
	return it.CurrentPtr();
}

unsigned long int CListOfNaDbObjectId::Remove(const unsigned long int O)
{
	if(IsEmpty())
		return 0;
	unsigned long int rO = 0;
	CListNodeOfNaDbObjectId* tmp = 0;
	if(O == First())
	{
		tmp = firstPtr;
		firstPtr = firstPtr->nextPtr;
		rO = tmp->data;
	}
	else
	{
		CListNodeOfNaDbObjectId* p = Previous(O);
		if(p->nextPtr != NULL)
		{
			tmp = p->nextPtr;
			p->nextPtr = p->nextPtr->nextPtr;
			rO = tmp->data;
		}
	}
	tmp->data = 0;
	delete tmp;
	return rO;
}

bool CListOfNaDbObjectId::IsEmpty() const
{
	return (firstPtr==0);
}		


void CListOfNaDbObjectId::Clear()
{
	CListNodeOfNaDbObjectId* curPtr = firstPtr, *tmp;
	if(!IsEmpty())
	{
		while(curPtr != 0)
		{
			tmp = curPtr;
			if(tmp->data)
			{
				tmp->data = 0;
			}
			curPtr = curPtr->nextPtr;
			delete tmp;
		}
		
		firstPtr = lastPtr = 0;
	}
}

CListNodeOfNaDbObjectId* CListOfNaDbObjectId::NewNode(unsigned long int P)
{
	CListNodeOfNaDbObjectId* newPtr= new CListNodeOfNaDbObjectId(P);
	if(!newPtr)
		throw CListException(LIST_OUT_OF_MEMORY);
	newPtr->nextPtr = 0;
	return newPtr;
}
