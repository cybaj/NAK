 
/***************************************************************************
 *            ListIteratorOfListOfPoint3D.h
 *
 ****************************************************************************/


#ifndef _ListIteratorOfListOfPoint3D_H
#define _ListIteratorOfListOfPoint3D_H

#ifdef NAKGE_EXPORTS
#define NAKGE_API __declspec(dllexport)
#else
#define NAKGE_API __declspec(dllimport)
#endif

#include "ListNodeOfPoint3D.h"
#include "ListOfPoint3D.h"

class NAKGE_API CListIteratorOfListOfPoint3D
{
public:
	CListIteratorOfListOfPoint3D() {;}
	CListIteratorOfListOfPoint3D(CListOfPoint3D*);
	virtual ~CListIteratorOfListOfPoint3D();
	void SetList(CListOfPoint3D*);
	void Init();
	bool More() const;
	void Next();
	NaGePoint3D Current() const;
	NaGePoint3D ValueAt(const int index);
private:
	CListNodeOfPoint3D* curPtr;
	CListOfPoint3D* theList;
};

#endif /* _ListIteratorOfListOfPoint3D_H */
