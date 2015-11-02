
 
/***************************************************************************
 *            NaGeListOfNaGeTriangle.h
 *
 ****************************************************************************/


#ifndef _LISTOFNaGeTriangle_H
#define _LISTOFNaGeTriangle_H

#ifdef NAKGE_EXPORTS
#define NAKGE_API __declspec(dllexport)
#else
#define NAKGE_API __declspec(dllimport)
#endif

#include "ListNodeOfTriangle.h"

class NaGeTriangle;
class CListIteratorOfListOfTriangle;

class NAKGE_API CListOfTriangle
{
	friend class CListIteratorOfListOfTriangle;
public:
	CListOfTriangle();
	virtual ~CListOfTriangle();
	void Append(const NaGeTriangle& data);
	void Prepend(const NaGeTriangle& data);
	NaGeTriangle First() const;
	NaGeTriangle Last() const;
	bool IsEmpty() const;
	void Clear();
private:
	CListNodeOfTriangle* firstPtr;
	CListNodeOfTriangle* lastPtr;
private:
	CListNodeOfTriangle* NewNode(const NaGeTriangle&);
};

#endif /* _LISTOFNaGeTriangle_H */
