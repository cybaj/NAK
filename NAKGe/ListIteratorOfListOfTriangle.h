/***************************************************************************
 *            ListIteratorOfListOfTriangle.h
 *
 ****************************************************************************/


#ifndef _ListIteratorOfListOfTriangle_H
#define _ListIteratorOfListOfTriangle_H

#ifdef NAKGE_EXPORTS
#define NAKGE_API __declspec(dllexport)
#else
#define NAKGE_API __declspec(dllimport)
#endif

#include "ListNodeOfTriangle.h"
#include "ListOfTriangle.h"

class NAKGE_API CListIteratorOfListOfTriangle
{
public:
	CListIteratorOfListOfTriangle() {;}
	CListIteratorOfListOfTriangle(CListOfTriangle*);
	virtual ~CListIteratorOfListOfTriangle();
	void SetList(CListOfTriangle*);
	void Init();
	bool More() const;
	void Next();
	NaGeTriangle Current() const;
	NaGeTriangle ValueAt(const int index);
private:
	CListNodeOfTriangle* curPtr;
	CListOfTriangle* theList;
};

#endif /* _ListIteratorOfListOfTriangle_H */
