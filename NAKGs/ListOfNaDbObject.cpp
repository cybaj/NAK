// ListOfNaDbObject.cpp: implementation of the CListOfNaDbObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "ListOfNaDbObject.h"
#include "ListIteratorOfListOfNaDbObject.h"
#include "ListException.h"
#include <NaGeMMath.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CListOfNaDbObject::CListOfNaDbObject() : firstPtr(0), lastPtr(0)
{
}


CListOfNaDbObject::~CListOfNaDbObject()
{
	CListNodeOfNaDbObject* curPtr = firstPtr, *tmp;
	if(!IsEmpty())
	{
		while(curPtr != 0)
		{
			tmp = curPtr;
			if(tmp->data)
			{
				if(tmp->data->DelRef() == 1)
					delete tmp->data;
				tmp->data = 0;
			}
			curPtr = curPtr->nextPtr;
			delete tmp;
		}
	}
}


void CListOfNaDbObject::Append( NaDbObject* data)
{
	CListNodeOfNaDbObject* newPtr = new CListNodeOfNaDbObject(data);
	if(IsEmpty())
		firstPtr = lastPtr = newPtr;
	else
	{
		lastPtr->nextPtr = newPtr;
		lastPtr = newPtr;
	}

}


void CListOfNaDbObject::Prepend( NaDbObject* data)
{
	CListNodeOfNaDbObject* newPtr = new CListNodeOfNaDbObject(data);
	if(IsEmpty())
		firstPtr = lastPtr = newPtr;
	else
	{
		newPtr->nextPtr = firstPtr;
		firstPtr = newPtr;
	}
}

NaDbObject* CListOfNaDbObject::First() const
{
	if(IsEmpty())
		throw CListException(LIST_EMPTY);
	return firstPtr->GetData();
}

NaDbObject* CListOfNaDbObject::Last() const
{
	if(IsEmpty())
		throw CListException(LIST_EMPTY);
	return lastPtr->GetData();
}


CListNodeOfNaDbObject* CListOfNaDbObject::Previous(const NaDbObject* O)
{
	CListIteratorOfListOfNaDbObject it(this);
	for(it.Init(); it.More(); it.Next())
	{
		if(O == it.CurrentPtr()->nextPtr->data)
			break;
	}
	return it.CurrentPtr();
}

NaDbObject* CListOfNaDbObject::Remove(const NaDbObject* O)
{
	if (IsEmpty())
		return 0;
	NaDbObject* rO = 0;
	CListNodeOfNaDbObject* tmp = 0;
	if (O == First())
	{
		tmp = firstPtr;
		firstPtr = firstPtr->nextPtr;
		rO = tmp->data;
	}
	else
	{
		CListNodeOfNaDbObject* p = Previous(O);
		if (p->nextPtr != NULL)
		{
			tmp = p->nextPtr;
			p->nextPtr = p->nextPtr->nextPtr;
			rO = tmp->data;
		}
	}
	tmp->data = 0;

	//!
	if (tmp->data && tmp->data->DelRef() == 1)
	{
		delete tmp->data;
	}		
	delete tmp;

	return rO;
}

bool CListOfNaDbObject::IsEmpty() const
{
	return (firstPtr==0);
}		


void CListOfNaDbObject::Clear()
{
	CListNodeOfNaDbObject* curPtr = firstPtr, *tmp;
	if(!IsEmpty())
	{
		while(curPtr != 0)
		{
			tmp = curPtr;
			if(tmp->data )
			{
				if (tmp->data->DelRef() == 1)
					delete tmp->data;
				tmp->data = 0;
			}
			curPtr = curPtr->nextPtr;
			delete tmp;
		}
		
		firstPtr = lastPtr = 0;
	}
}

CListNodeOfNaDbObject* CListOfNaDbObject::NewNode(NaDbObject* P)
{
	CListNodeOfNaDbObject* newPtr= new CListNodeOfNaDbObject(P);
	if(!newPtr)
		throw CListException(LIST_OUT_OF_MEMORY);
	newPtr->nextPtr = 0;
	return newPtr;
}
