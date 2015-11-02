 
/***************************************************************************
 *            ListNodeOfNaGePoint3D.h
 *
 ****************************************************************************/


#ifndef _LISTNODEOFNaGePoint3D_H
#define _LISTNODEOFNaGePoint3D_H

#ifdef NAKGE_EXPORTS
#define NAKGE_API __declspec(dllexport)
#else
#define NAKGE_API __declspec(dllimport)
#endif

#include "NaGePoint3D.h"

//class NaGePoint3D;
class CListOfPoint3D;

class NAKGE_API CListNodeOfPoint3D  
{
	friend class CListOfPoint3D;
	friend class CListIteratorOfListOfPoint3D;
public:
	CListNodeOfPoint3D(const NaGePoint3D&);
	NaGePoint3D GetData() const;
	virtual ~CListNodeOfPoint3D();
	bool operator==(CListNodeOfPoint3D& rhs);
	bool operator!=(CListNodeOfPoint3D& rhs);
private:
	NaGePoint3D data;
	CListNodeOfPoint3D* nextPtr;

};

#endif /* _LISTNODEOFNaGePoint3D_H */
