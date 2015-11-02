
/***************************************************************************
 *            NaGePCurve.h
 *
 ****************************************************************************/


#ifndef _PCURVE_H
#define _PCURVE_H

#ifdef NAKGE_EXPORTS
#define NAKGE_API __declspec(dllexport)
#else
#define NAKGE_API __declspec(dllimport)
#endif

#include "NaGeCurve.h"

#define MAXDEGREE 25

class NaGePoint3D;

//Abstract Base Class For Bezier and B-Spline Curves
class NAKGE_API NaGePCurve : public NaGeCurve  
{
public:
	NaGePCurve();
	virtual ~NaGePCurve();
	virtual void Reverse() = 0;
	virtual NaGePoint3D PointAtPara(const double& para) = 0;
	virtual double FirstParameter() const = 0;
	virtual double LastParameter() const = 0;
	virtual bool IsClosed() const = 0;
	virtual NaGeCurve* Copy() const = 0;
	virtual void Translate(double dx, double dy, double dz) = 0;
	virtual void Translate(const NaGeVector3D&) = 0;
	virtual void Translate(const NaGePoint3D&, const NaGePoint3D&) = 0;
	virtual void Rotate(const NaGeOneAxis&, double) = 0;
	virtual void Scale(const NaGePoint3D&, double) = 0;
	virtual void Mirror(const NaGePoint3D&) = 0;
	virtual void Mirror(const NaGeOneAxis&) = 0;
	virtual void Mirror(const NaGePlane&) = 0;
	int GetMaxDegree() const;
};

#endif /* _PCURVE_H */
