 
/***************************************************************************
 *            NaGeCurve2D.h
 *
 ****************************************************************************/


#ifndef _CURVE2D_H
#define _CURVE2D_H

#ifdef NAKGE_EXPORTS
#define NAKGE_API __declspec(dllexport)
#else
#define NAKGE_API __declspec(dllimport)
#endif

#include "NaGeGeometry2D.h"

class NaGePoint2D;

enum Curve2DType { BEZIER2D, BSPLINE2D, CIRCLE2D, ELLIPSE2D, HYPERBOLA2D, LINE2D, OFFSETCURVE2D, PARABOLA2D };

//Abstract Base Class
class NAKGE_API NaGeCurve2D : public NaGeGeometry2D  
{
public:
	NaGeCurve2D();
	virtual ~NaGeCurve2D();
	virtual void Reverse() = 0;
	virtual NaGePoint2D PointAtPara(const double& para) = 0;
	virtual double FirstParameter() const = 0;
	virtual double LastParameter() const = 0;
	virtual bool IsClosed() const = 0;
	Curve2DType Type() const;
	bool IsOfType(const Curve2DType&) const;
	virtual NaGeCurve2D* Copy() const = 0;
	virtual void Translate(double dx, double dy) = 0;
	virtual void Translate(const NaGeVector2D&) = 0;
	virtual void Translate(const NaGePoint2D&, const NaGePoint2D&) = 0;
	virtual void Rotate(const NaGePoint2D&, double) = 0;
	virtual void Scale(const NaGePoint2D&, double) = 0;
	virtual void Mirror(const NaGePoint2D&) = 0;
	virtual void Mirror(const NaGeOneAxis2D&) = 0;
protected:
	Curve2DType cType;
	bool cReversed;
};

#endif /* _CURVE2D_H */
