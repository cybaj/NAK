
/***************************************************************************
 *            ListOfNaGePoint3D.h
 *
 ****************************************************************************/

#ifndef _ListOfPoint3D_H
#define _ListOfPoint3D_H

#ifdef NAKGE_EXPORTS
#define NAKGE_API __declspec(dllexport)
#else
#define NAKGE_API __declspec(dllimport)
#endif

#include "ListNodeOfPoint3D.h"

class NaGePoint3D;
class CListIteratorOfListOfPoint3D;

class NAKGE_API CListOfPoint3D
{
	friend class CListIteratorOfListOfPoint3D;
public:
	CListOfPoint3D();
	virtual ~CListOfPoint3D();
	void Append(const NaGePoint3D& data);
	void Prepend(const NaGePoint3D& data);
	NaGePoint3D First() const;
	NaGePoint3D Last() const;
	bool IsEmpty() const;
	void Clear();
	inline unsigned long Count() const { return itsCount; }
private:
	CListNodeOfPoint3D* firstPtr;
	CListNodeOfPoint3D* lastPtr;
	unsigned long itsCount; 
private:
	CListNodeOfPoint3D* NewNode(const NaGePoint3D&);
};

#endif /* _ListOfPoint3D_H */
