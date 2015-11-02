/***************************************************************************
 *            NaGeCurve.h
 *
 ****************************************************************************/


#ifndef _CURVE_H
#define _CURVE_H

#ifdef NAKGE_EXPORTS
#define NAKGE_API __declspec(dllexport)
#else
#define NAKGE_API __declspec(dllimport)
#endif

#include "NaGeGeometry.h"

class NaGePoint3D;

enum CurveType { BEZIER, BSPLINE, CIRCLE, ELLIPSE, HELIX, HYPERBOLA, LINE, OFFSETCURVE, PARABOLA};

//Abstract Base Class
class NAKGE_API NaGeCurve : public NaGeGeometry  
{
public:
	NaGeCurve();
	virtual ~NaGeCurve();
	virtual void Reverse() = 0;
	virtual NaGePoint3D PointAtPara(const double& para) = 0;
	virtual double FirstParameter() const = 0;
	virtual double LastParameter() const = 0;
	virtual bool IsClosed() const = 0;
	CurveType Type() const;
	bool IsOfType(const CurveType&) const;
	virtual NaGeCurve* Copy() const = 0;
	virtual void Translate(double dx, double dy, double dz) = 0;
	virtual void Translate(const NaGeVector3D&) = 0;
	virtual void Translate(const NaGePoint3D&, const NaGePoint3D&) = 0;
	virtual void Rotate(const NaGeOneAxis&, double) = 0;
	virtual void Scale(const NaGePoint3D&, double) = 0;
	virtual void Mirror(const NaGePoint3D&) = 0;
	virtual void Mirror(const NaGeOneAxis&) = 0;
	virtual void Mirror(const NaGePlane&) = 0;
protected:
	CurveType cType;
	bool cReversed;
};

#endif /* _CURVE_H */
