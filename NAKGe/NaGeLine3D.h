 
/***************************************************************************
 *            NaGeLine3D.h
 *
 ****************************************************************************/


#ifndef _LINE3D_H
#define _LINE3D_H

#ifdef NAKGE_EXPORTS
#define NAKGE_API __declspec(dllexport)
#else
#define NAKGE_API __declspec(dllimport)
#endif

#include "NaGeCurve.h"
#include "NaGePoint3D.h"
#include "NaGeVector3D.h"
#include "NaGeOneAxis.h"

class NaGePoint3D;
class NaGeVector3D;
class NaGeOneAxis;

class NAKGE_API NaGeLine3D : public NaGeCurve  
{
public:
	NaGeLine3D();
	NaGeLine3D(const NaGePoint3D&, const NaGePoint3D&);
	NaGeLine3D(const NaGePoint3D&, const NaGeVector3D&);
	virtual ~NaGeLine3D();
	virtual void Reverse();
	virtual NaGePoint3D PointAtPara(const double& par);
	inline virtual double FirstParameter() const { return 0; }
	inline virtual double LastParameter() const { 	return 1; }
	virtual bool IsClosed() const;
	bool operator == (const NaGeLine3D& L) const;
	void operator = (const NaGeLine3D& L);
	NaGeVector3D Direction() const;
	inline NaGeOneAxis GetLocation() const { return itsLocation; }
	NaGeVector3D NormalThrough(const NaGePoint3D&);
	double Distance(const NaGePoint3D&) const;
	inline double SegmentLength() const { return startPoint.Distance(endPoint); }
	inline NaGePoint3D StartPoint() const { return startPoint; }
	inline NaGePoint3D EndPoint() const { return endPoint; }
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
	NaGePoint3D startPoint;
	NaGePoint3D endPoint;
	NaGeOneAxis itsLocation;
};

#endif /* _LINE3D_H */
