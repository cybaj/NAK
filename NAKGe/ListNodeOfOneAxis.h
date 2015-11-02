/***************************************************************************
 *            ListNodeOfOneAxis.h
 *
 ****************************************************************************/


#ifndef _ListNodeOfOneAxis_H
#define _ListNodeOfOneAxis_H

#ifdef NAKGE_EXPORTS
#define NAKGE_API __declspec(dllexport)
#else
#define NAKGE_API __declspec(dllimport)
#endif

#include "NaGeOneAxis.h"

//class NaGeOneAxis;
class CListOfOneAxis;

class NAKGE_API CListNodeOfOneAxis  
{
	friend class CListOfOneAxis;
	friend class CListIteratorOfListOfOneAxis;
public:
	CListNodeOfOneAxis(const NaGeOneAxis&);
	NaGeOneAxis GetData() const;
	virtual ~CListNodeOfOneAxis();
	bool operator==(CListNodeOfOneAxis& rhs);
	bool operator!=(CListNodeOfOneAxis& rhs);
private:
	NaGeOneAxis data;
	CListNodeOfOneAxis* nextPtr;

};

#endif /* _ListNodeOfOneAxis_H */
