 
/***************************************************************************
 *            NaGeBSplineCurve.h
 *
 ****************************************************************************/


#ifndef _BSPLINECURVE_H
#define _BSPLINECURVE_H

#ifdef NAKGE_EXPORTS
#define NAKGE_API __declspec(dllexport)
#else
#define NAKGE_API __declspec(dllimport)
#endif

#include "NaGePCurve.h"
#include "ListOfPoint3D.h"
#include "ListIteratorOfListOfPoint3D.h"

class NAKGE_API NaGeBSplineCurve : public NaGePCurve
{
public:
	NaGeBSplineCurve();
	NaGeBSplineCurve(CListOfPoint3D*, const int& = 3);
	virtual ~NaGeBSplineCurve();
	virtual void Reverse();
	virtual NaGePoint3D PointAtPara(const double& para);
	virtual double FirstParameter() const;
	virtual double LastParameter() const;
	virtual bool IsClosed() const;
	virtual NaGeCurve* Copy() const;
	virtual void Translate(const NaGeOneAxis&, const double&);
	virtual void Translate(double dx, double dy, double dz);
	virtual void Translate(const NaGeVector3D&);
	virtual void Translate(const NaGePoint3D&, const NaGePoint3D&);
	virtual void Rotate(const NaGeOneAxis&, double);
	virtual void Scale(const NaGePoint3D&, double);
	virtual void Mirror(const NaGePoint3D&);
	virtual void Mirror(const NaGeOneAxis&);
	virtual void Mirror(const NaGePlane&);
private:
	CListOfPoint3D *cpList;
	int cpCount;
	int itsDegree;
};

#endif /* _BSPLINECURVE_H */
