/***************************************************************************
 *            ListNodeOfNaDbObject.h
 *
 ****************************************************************************/


#ifndef _LISTNODEOFNaDbObject_H
#define _LISTNODEOFNaDbObject_H

#include "NaDbObject.h"

#ifdef NAKGS_EXPORTS
#define NAKGS_API __declspec(dllexport)
#else
#define NAKGS_API __declspec(dllimport)
#endif

//class NaDbObject;
class CListOfNaDbObject;

class NAKGS_API CListNodeOfNaDbObject  
{
	friend class CListOfNaDbObject;
	friend class CListIteratorOfListOfNaDbObject;
public:
	CListNodeOfNaDbObject(NaDbObject*);
	NaDbObject* GetData() const;
	virtual ~CListNodeOfNaDbObject();
	bool operator==(CListNodeOfNaDbObject& rhs);
	bool operator!=(CListNodeOfNaDbObject& rhs);
private:
	NaDbObject* data;
	CListNodeOfNaDbObject* nextPtr;

};

#endif /* _LISTNODEOFNaDbObject_H */
