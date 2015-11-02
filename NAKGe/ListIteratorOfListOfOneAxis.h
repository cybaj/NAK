
/***************************************************************************
 *            ListIteratorOfListOfNaGeOneAxis.h
 *
 ****************************************************************************/


#ifndef _ListIteratorOfListOfOneAxis_H
#define _ListIteratorOfListOfOneAxis_H

#ifdef NAKGE_EXPORTS
#define NAKGE_API __declspec(dllexport)
#else
#define NAKGE_API __declspec(dllimport)
#endif

#include "ListNodeOfOneAxis.h"
#include "ListOfOneAxis.h"

class NAKGE_API CListIteratorOfListOfOneAxis
{
	public:
	    CListIteratorOfListOfOneAxis() {;}
	    CListIteratorOfListOfOneAxis(CListOfOneAxis*);
	    virtual ~CListIteratorOfListOfOneAxis();
	    void SetList(CListOfOneAxis*);
	    void Init();
	    bool More() const;
	    void Next();
	    NaGeOneAxis Current() const;
	    NaGeOneAxis ValueAt(const int index);
	private:
	    CListNodeOfOneAxis* curPtr;
	    CListOfOneAxis* theList;
};

#endif /* _ListIteratorOfListOfOneAxis_H */
