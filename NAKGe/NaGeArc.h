/***************************************************************************
 *            NaGeArc.h
 *
 ****************************************************************************/


#ifndef _ARC_H
#define _ARC_H

#ifdef NAKGE_EXPORTS
#define NAKGE_API __declspec(dllexport)
#else
#define NAKGE_API __declspec(dllimport)
#endif

#include "NaGeCircle3D.h"
#include "NaGePoint3D.h"

#include "ListOfPoint3D.h"
#include "ListIteratorOfListOfPoint3D.h"

class NAKGE_API NaGeArc : public NaGeCircle3d  
{
public:
	NaGeArc(int plane, const NaGePoint3D& P1, const NaGePoint3D& P2, const NaGePoint3D& Cen, double step, bool clock);
	virtual ~NaGeArc();
public:

	CListOfPoint3D* ArcPoints;
};

#endif /* _ARC_H */
