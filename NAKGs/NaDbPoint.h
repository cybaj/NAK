 
/***************************************************************************
 *            NaDbPoint.h
 *
 ****************************************************************************/


#ifndef _GLPOINT_H
#define _GLPOINT_H

#ifdef NAKGS_EXPORTS
#define NAKGS_API __declspec(dllexport)
#else
#define NAKGS_API __declspec(dllimport)
#endif

#include "NaDbObject.h"
#include <NaGePoint3D.h>

class NaGePoint3D;

class NAKGS_API NaDbPoint : public NaDbObject
{
public:
	NaDbPoint(const NaGePoint3D&, const GsPointMarker& = MARKER_POINT);
	virtual ~NaDbPoint();
	virtual NaDbObject* Copy();
	virtual void DefineDisplay();
	virtual void Display(const GsDisplayMode& = GLWIREFRAME);
	virtual void Hilight(const GsDisplayMode&);
	virtual NaGeGeometry* Geometry() const;
private:
	void ComputeBoundLimits();
	void DrawMarker();
private:
	NaGePoint3D itsPoint;
	GLuint base;        /* Display list number of Marker */
    int    fwidths[256]; /* Width of each Marker in pixels */
    int    fheight;      /* Height of Marker */
	GsPointMarker itsMarker;
};

#endif /* _GLPOINT_H */
