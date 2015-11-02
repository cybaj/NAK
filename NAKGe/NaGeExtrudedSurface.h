
/***************************************************************************
 *            NaGeExtrudedSurface.h
 *
 ****************************************************************************/


#ifndef _EXTRUDEDSURFACE_H
#define _EXTRUDEDSURFACE_H

#ifdef NAKGE_EXPORTS
#define NAKGE_API __declspec(dllexport)
#else
#define NAKGE_API __declspec(dllimport)
#endif

#include "NaGeSweptSurface.h"
#include "NaGeVector3D.h"

class NAKGE_API NaGeExtrudedSurface : public NaGeSweptSurface  
{
public:
	NaGeExtrudedSurface(){}
	NaGeExtrudedSurface(const NaGeCurve*, const NaGeVector3D&, const double&, const double&);
	virtual ~NaGeExtrudedSurface();
	virtual NaGePoint3D PointAtPara(const double uPar, const double vPar);
	virtual double FirstUParameter() const;
	virtual double LastUParameter() const;
	virtual double FirstVParameter() const;
	virtual double LastVParameter() const;
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
	NaGeVector3D itsDirection;
	double startLimit;
	double endLimit;

};

#endif /* _EXTRUDEDSURFACE_H */
