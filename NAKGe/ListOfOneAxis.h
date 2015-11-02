/***************************************************************************
 *            ListOfNaGeOneAxis.h
 *
 ****************************************************************************/

#ifndef _LISTOFNaGeOneAxis_H
#define _LISTOFNaGeOneAxis_H

#ifdef NAKGE_EXPORTS
#define NAKGE_API __declspec(dllexport)
#else
#define NAKGE_API __declspec(dllimport)
#endif

#include "ListNodeOfOneAxis.h"

class NaGeOneAxis;
class CListIteratorOfListOfOneAxis;

class NAKGE_API CListOfOneAxis
{
	friend class CListIteratorOfListOfOneAxis;
public:
	CListOfOneAxis();
	virtual ~CListOfOneAxis();
	void Append(const NaGeOneAxis& data);
	void Prepend(const NaGeOneAxis& data);
	NaGeOneAxis First() const;
	NaGeOneAxis Last() const;
	bool IsEmpty() const;
	void Clear();
private:
	CListNodeOfOneAxis* firstPtr;
	CListNodeOfOneAxis* lastPtr;
private:
	CListNodeOfOneAxis* NewNode(const NaGeOneAxis&);
};

#endif /* _LISTOFNaGeOneAxis_H */
