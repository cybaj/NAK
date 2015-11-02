
/***************************************************************************
 *            NaGeSurface.h
 *
 ****************************************************************************/


#ifndef _SURFACE_H
#define _SURFACE_H

#ifdef NAKGE_EXPORTS
#define NAKGE_API __declspec(dllexport)
#else
#define NAKGE_API __declspec(dllimport)
#endif

#include "NaGeGeometry.h"
#include "NaGePoint3D.h"
#include "NaGeAxisSystem.h"

enum SurfaceType { CONE, CYLINDER, EXTRUDED, OFFSET, PIPE, PLANE, REVOLVED, RULED, SPHERE, TORUS };

class NaGePoint3D;
class NaGeAxisSystem;

//Abstract Base Class For All Surfaces
class NAKGE_API NaGeSurface : public NaGeGeometry  
{
public:
	NaGeSurface();
	virtual ~NaGeSurface();
	virtual NaGePoint3D PointAtPara(const double uPar, const double vPar) = 0;
	virtual NaGeVector3D NormalAt(const double uPar, const double vPar);
	virtual double FirstUParameter() const = 0;
	virtual double LastUParameter() const = 0;
	virtual double FirstVParameter() const = 0;
	virtual double LastVParameter() const = 0;
	virtual bool IsUClosed() const = 0;
	virtual bool IsVClosed() const = 0;
	SurfaceType Type() const;
	bool IsOfType(const SurfaceType&) const;
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
	SurfaceType sType;
};

#endif /* _SURFACE_H */
