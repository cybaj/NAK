 
/***************************************************************************
 *            ListIteratorOfListOfNaDbObjectId.h
 *
 ****************************************************************************/

#ifndef _ListIteratorOfListOfNaDbObjectId_H
#define _ListIteratorOfListOfNaDbObjectId_H

#ifdef NAKGS_EXPORTS
#define NAKGS_API __declspec(dllexport)
#else
#define NAKGS_API __declspec(dllimport)
#endif

#include "ListNodeOfNaDbObjectId.h"
#include "ListOfNaDbObjectId.h"

class NAKGS_API CListIteratorOfListOfNaDbObjectId
{
public:
	CListIteratorOfListOfNaDbObjectId(){}
	CListIteratorOfListOfNaDbObjectId(CListOfNaDbObjectId*);
	virtual ~CListIteratorOfListOfNaDbObjectId();
	void SetList(CListOfNaDbObjectId*);
	void Init();
	bool More() const;
	bool IsFound(const unsigned long int) const;
	void Next();
	unsigned long int Current() const;
	CListNodeOfNaDbObjectId* CurrentPtr() const;
	void SetCurrent(unsigned long int);
	unsigned long int ValueAt(const int index);
private:
	CListNodeOfNaDbObjectId* curPtr;
	CListOfNaDbObjectId* theList;
};

#endif /* _ListIteratorOfListOfNaDbObjectId_H */
