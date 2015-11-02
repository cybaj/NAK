/***************************************************************************
 *            ListNodeOfNaDbObject.h
 *
 ****************************************************************************/


#ifndef _ListNodeOfNaDbObjectId_H
#define _ListNodeOfNaDbObjectId_H

#include "NaDbObject.h"

#ifdef NAKGS_EXPORTS
#define NAKGS_API __declspec(dllexport)
#else
#define NAKGS_API __declspec(dllimport)
#endif

//class NaDbObject;
class CListOfNaDbObject;

class NAKGS_API CListNodeOfNaDbObjectId
{
	friend class CListOfNaDbObjectId;
	friend class CListIteratorOfListOfNaDbObjectId;
public:
	CListNodeOfNaDbObjectId(unsigned long int id);
	unsigned long int GetData() const;
	virtual ~CListNodeOfNaDbObjectId();
	bool operator==(CListNodeOfNaDbObjectId& rhs);
	bool operator!=(CListNodeOfNaDbObjectId& rhs);
private:
	unsigned long int data;
	CListNodeOfNaDbObjectId* nextPtr;

};

#endif /* _ListNodeOfNaDbObjectId_H */
