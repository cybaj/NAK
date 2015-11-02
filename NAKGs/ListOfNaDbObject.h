 
/***************************************************************************
 *            ListOfNaDbObject.h
 *
 ****************************************************************************/


#ifndef _LISTOFNaDbObject_H
#define _LISTOFNaDbObject_H

#ifdef NAKGS_EXPORTS
#define NAKGS_API __declspec(dllexport)
#else
#define NAKGS_API __declspec(dllimport)
#endif

#include "ListNodeOfNaDbObject.h"

class NaDbObject;
class CListIteratorOfListOfNaDbObject;

class NAKGS_API CListOfNaDbObject
{
	friend class CListIteratorOfListOfNaDbObject;
public:
	CListOfNaDbObject();
	virtual ~CListOfNaDbObject();
	void Append(NaDbObject*);
	void Prepend(NaDbObject*);
	NaDbObject* First() const;
	NaDbObject* Last() const;
	CListNodeOfNaDbObject* Previous(const NaDbObject*);
	NaDbObject* Remove(const NaDbObject*);
	bool IsEmpty() const;
	void Clear();
private:
	CListNodeOfNaDbObject* firstPtr;
	CListNodeOfNaDbObject* lastPtr;
private:
	CListNodeOfNaDbObject* NewNode(NaDbObject*);
};

#endif /* _LISTOFNaDbObject_H */
