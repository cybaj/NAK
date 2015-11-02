/***************************************************************************
 *            NaGeSweptSurface.h
 *
 ****************************************************************************/


#ifndef _SWEPTSURFACE_H
#define _SWEPTSURFACE_H

#ifdef NAKGE_EXPORTS
#define NAKGE_API __declspec(dllexport)
#else
#define NAKGE_API __declspec(dllimport)
#endif

#include "NaGeSurface.h"
#include "NaGeCurve.h"

class NaGePoint3D;
class NaGeCurve;

//Abstract Base Class For Extruded, Revolved, Ruled and Pipe Surfaces
class NAKGE_API NaGeSweptSurface : public NaGeSurface  
{
public:
	NaGeSweptSurface();
	virtual ~NaGeSweptSurface();
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
	NaGeCurve* baseCurve; //Acts as: 1) base curve for Extruded Surface
					   //		  2) profile for Revolved Surface
					   //		  3) spine for Pipe Surface
					   //		  4) rails for Ruled Surface
};

#endif /* _SWEPTSURFACE_H */
