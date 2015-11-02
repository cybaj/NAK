/***************************************************************************
 *            NaGeSphere.h
 *
 ****************************************************************************/


#ifndef _SPHERE_H
#define _SPHERE_H

#ifdef NAKGE_EXPORTS
#define NAKGE_API __declspec(dllexport)
#else
#define NAKGE_API __declspec(dllimport)
#endif

#include "NaGeBasicSurface.h"
#include "NaGeMMath.h"

class NAKGE_API NaGeSphere : public NaGeBasicSurface  
{
    public:
	NaGeSphere();
	NaGeSphere(const NaGeAxisSystem&, const double& rad, const double& uStart = 0, const double& uEnd = 2*PI, const double& vStart = -PI/2, const double& vEnd = PI/2);
	virtual ~NaGeSphere();
	inline void SetRadius(const double& r) { itsRadius = r; }
	inline double GetRadius() const { return itsRadius; }
	virtual NaGePoint3D PointAtPara(const double uPar, const double vPar);
	virtual NaGeVector3D NormalAt(const double uPar, const double vPar);
	inline virtual double FirstUParameter() const { return itsFirstUParameter; }
	inline virtual double LastUParameter() const { return itsLastUParameter; }
	inline virtual double FirstVParameter() const { return itsFirstVParameter; }
	inline virtual double LastVParameter() const { return itsLastVParameter; }
	virtual bool IsUClosed() const;
	virtual bool IsVClosed() const;
	virtual NaGeSurface* Copy() const;
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
	double itsRadius;
};

#endif /* _SPHERE_H */
