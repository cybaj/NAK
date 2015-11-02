
/***************************************************************************
 *            NaGeBasicSurface.h
 *
 ****************************************************************************/


#ifndef _BASINaGeSurface_H
#define _BASINaGeSurface_H

#ifdef NAKGE_EXPORTS
#define NAKGE_API __declspec(dllexport)
#else
#define NAKGE_API __declspec(dllimport)
#endif

#include "NaGeSurface.h"

class NaGePoint3D;

//Abstract Base Class For Plane, Cylinder, Cone, Sphere and Torus
class NAKGE_API NaGeBasicSurface : public NaGeSurface
{
public:
	NaGeBasicSurface();
	virtual ~NaGeBasicSurface();
	inline NaGeAxisSystem GetLocation() const { return itsLocation; }
	virtual NaGePoint3D PointAtPara(const double uPar, const double vPar) = 0;
	virtual double FirstUParameter() const = 0;
	virtual double LastUParameter() const = 0;
	virtual double FirstVParameter() const = 0;
	virtual double LastVParameter() const = 0;
	virtual bool IsUClosed() const = 0;
	virtual bool IsVClosed() const = 0;
	virtual NaGeSurface* Copy() const = 0;
	virtual void Translate(double dx, double dy, double dz) = 0;
	virtual void Translate(const NaGeVector3D&) = 0;
	virtual void Translate(const NaGePoint3D&, const NaGePoint3D&) = 0;
	virtual void Rotate(const NaGeOneAxis&, double) = 0;
	virtual void Scale(const NaGePoint3D&, double) = 0;
	virtual void Mirror(const NaGePoint3D&) = 0;
	virtual void Mirror(const NaGeOneAxis&) = 0;
	virtual void Mirror(const NaGePlane&) = 0;
protected:
	NaGeAxisSystem itsLocation;
	double itsFirstUParameter;
	double itsLastUParameter;
	double itsFirstVParameter;
	double itsLastVParameter;
};

#endif /* _BASINaGeSurface_H */
