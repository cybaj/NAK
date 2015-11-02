
 
/***************************************************************************
 *            NaGeOffsetCurve.h
 *
 ****************************************************************************/


#ifndef _OFFSETCURVE_H
#define _OFFSETCURVE_H

#ifdef NAKGE_EXPORTS
#define NAKGE_API __declspec(dllexport)
#else
#define NAKGE_API __declspec(dllimport)
#endif

#include "NaGeCurve.h"
#include "NaGePoint3D.h"
#include "NaGeVector3D.h"
#include "NaGePlane.h"

class NAKGE_API NaGeOffsetCurve : public NaGeCurve  
{
public:
	NaGeOffsetCurve(const NaGeCurve& aCurve, const double& offset, const NaGePlane& refPlane, const bool& sense = true);
	virtual ~NaGeOffsetCurve();
	virtual void Reverse();
	virtual NaGePoint3D PointAtPara(const double& para);
	virtual double FirstParameter() const;
	virtual double LastParameter() const;
	virtual bool IsClosed() const;
	CurveType Type() const;
	bool IsOfType(const CurveType&) const;
	virtual NaGeCurve* Copy() const;
	virtual void Translate(double dx, double dy, double dz);
	virtual void Translate(const NaGeVector3D&);
	virtual void Translate(const NaGePoint3D&, const NaGePoint3D&);
	virtual void Rotate(const NaGeOneAxis&, double);
	virtual void Scale(const NaGePoint3D&, double);
	virtual void Mirror(const NaGePoint3D&);
	virtual void Mirror(const NaGeOneAxis&);
	virtual void Mirror(const NaGePlane&);
private:
	NaGeCurve* itsCurve;
	double itsOffset;
	NaGePlane itsPlane;
	bool itsSense;
};

#endif /* _OFFSETCURVE_H */
