/***************************************************************************
 *            NaGeRevolvedSurface.h
 *
 ****************************************************************************/


#ifndef _REVOLVEDSURFACE_H
#define _REVOLVEDSURFACE_H

#ifdef NAKGE_EXPORTS
#define NAKGE_API __declspec(dllexport)
#else
#define NAKGE_API __declspec(dllimport)
#endif

#include "NaGeSweptSurface.h"
#include "NaGeOneAxis.h"

class NAKGE_API NaGeRevolvedSurface : public NaGeSweptSurface  
{
public:
	NaGeRevolvedSurface();
	NaGeRevolvedSurface(const NaGeCurve*, const NaGeOneAxis&, const double&, const double&);
	virtual ~NaGeRevolvedSurface();
	virtual NaGePoint3D PointAtPara(const double uPar, const double vPar);
	virtual NaGeVector3D NormalAt(const double uPar, const double vPar);
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
	NaGeOneAxis itsAxisOfRevol;
	double startAngle;
	double endAngle;

};

#endif /* _REVOLVEDSURFACE_H */
