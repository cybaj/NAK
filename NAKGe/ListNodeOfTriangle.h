
/***************************************************************************
 *            ListNodeOfNaGeTriangle.h
 *
 ****************************************************************************/


#ifndef _LISTNODEOFNaGeTriangle_H
#define _LISTNODEOFNaGeTriangle_H

#ifdef NAKGE_EXPORTS
#define NAKGE_API __declspec(dllexport)
#else
#define NAKGE_API __declspec(dllimport)
#endif

#include "NaGeTriangle.h"

class CListOfTriangle;

class NAKGE_API CListNodeOfTriangle  
{
	friend class CListOfTriangle;
	friend class CListIteratorOfListOfTriangle;
public:
	CListNodeOfTriangle(const NaGeTriangle&);
	NaGeTriangle GetData() const;
	virtual ~CListNodeOfTriangle();
	bool operator==(CListNodeOfTriangle& rhs);
	bool operator!=(CListNodeOfTriangle& rhs);
private:
	NaGeTriangle data;
	CListNodeOfTriangle* nextPtr;

};

#endif /* _LISTNODEOFNaGeTriangle_H */
