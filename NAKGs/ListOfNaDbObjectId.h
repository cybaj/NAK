 
/***************************************************************************
 *            ListOfNaDbObject.h
 *
 ****************************************************************************/


#ifndef _ListOfNaDbObjectId_H
#define _ListOfNaDbObjectId_H

#ifdef NAKGS_EXPORTS
#define NAKGS_API __declspec(dllexport)
#else
#define NAKGS_API __declspec(dllimport)
#endif

#include "ListNodeOfNaDbObjectId.h"

class NaDbObject;
class CListIteratorOfListOfNaDbObjectId;

class NAKGS_API CListOfNaDbObjectId
{
	friend class CListIteratorOfListOfNaDbObjectId;
public:
	CListOfNaDbObjectId();
	virtual ~CListOfNaDbObjectId();
	void Append(unsigned long int);
	void Prepend(unsigned long int);
	unsigned long int First() const;
	unsigned long int  Last() const;
	CListNodeOfNaDbObjectId* Previous(const unsigned long int);
	unsigned long int  Remove(const unsigned long int);
	bool IsEmpty() const;
	void Clear();
private:
	CListNodeOfNaDbObjectId* firstPtr;
	CListNodeOfNaDbObjectId* lastPtr;
private:
	CListNodeOfNaDbObjectId* NewNode(unsigned long int);
};

#endif /* _ListOfNaDbObjectId_H */
