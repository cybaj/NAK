
/***************************************************************************
 *            NaDbCurve.h
 *
 ****************************************************************************/


#ifndef _GLCURVE_H
#define _GLCURVE_H

#ifdef NAKGS_EXPORTS
#define NAKGS_API __declspec(dllexport)
#else
#define NAKGS_API __declspec(dllimport)
#endif

#include "NaDbObject.h"

#include <NaGeGeometry.h>
#include <NaGeGeomException.h>
#include <NaGePoint3D.h>
#include <NaGeVector3D.h>
#include <NaGeOneAxis.h>
#include <NaGeAxisSystem.h>
#include <NaGeLine3D.h>
#include <NaGeCircle3D.h>
#include <NaGeEllipse3D.h>
#include <NaGeHyperbola3D.h>
#include <NaGeParabola3D.h>
#include <NaGeBezierCurve.h>
#include <NaGeBSplineCurve.h>

#include <ListOfPoint3D.h>
#include <ListIteratorOfListOfPoint3D.h>

class NaGeCurve;

class NAKGS_API NaDbCurve : public NaDbObject  
{
    public:
	NaDbCurve(const NaGeCurve*, const GsLineStyle& = LINE_SOLID);
	virtual ~NaDbCurve();
	virtual NaDbObject* Copy();
	virtual void DefineDisplay();
	virtual void Display(const GsDisplayMode& = GLWIREFRAME);
	virtual void Hilight(const GsDisplayMode&);
	void SetLineStyle(const GsLineStyle& st) { lineStyle = st; }
	GsLineStyle GetLineStyle() const { return lineStyle; }
	void SetSmooth(const double&);
	void SetCurve(const NaGeCurve*);
	virtual NaGeGeometry* Geometry() const;
    private:
	void ComputePoints();
	void ComputeBoundLimits();

    private:
	GLdouble SMOOTH;
	CListOfPoint3D* pointList;
	NaGeCurve* pCurve;
	GsLineStyle lineStyle;
};

#endif /* _GLCURVE_H */
