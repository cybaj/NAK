 
/***************************************************************************
 *            ListIteratorOfListOfNaDbObject.h
 *
 ****************************************************************************/

#ifndef _LISTITERATOROFLISTOFNaDbObject_H
#define _LISTITERATOROFLISTOFNaDbObject_H

#ifdef NAKGS_EXPORTS
#define NAKGS_API __declspec(dllexport)
#else
#define NAKGS_API __declspec(dllimport)
#endif

#include "ListNodeOfNaDbObject.h"
#include "ListOfNaDbObject.h"

class NAKGS_API CListIteratorOfListOfNaDbObject
{
public:
	CListIteratorOfListOfNaDbObject(){}
	CListIteratorOfListOfNaDbObject(CListOfNaDbObject*);
	virtual ~CListIteratorOfListOfNaDbObject();
	void SetList(CListOfNaDbObject*);
	void Init();
	bool More() const;
	bool IsFound(const NaDbObject*) const;
	void Next();
	NaDbObject* Current() const;
	CListNodeOfNaDbObject* CurrentPtr() const;
	void SetCurrent(NaDbObject*);
	NaDbObject* ValueAt(const int index);
private:
	CListNodeOfNaDbObject* curPtr;
	CListOfNaDbObject* theList;
};

#endif /* _LISTITERATOROFLISTOFNaDbObject_H */
