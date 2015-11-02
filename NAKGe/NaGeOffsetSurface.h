
 
/***************************************************************************
 *            NaGeOffsetSurface.h
 *
 ****************************************************************************/


#ifndef _OFFSETSURFACE_H
#define _OFFSETSURFACE_H

#ifdef NAKGE_EXPORTS
#define NAKGE_API __declspec(dllexport)
#else
#define NAKGE_API __declspec(dllimport)
#endif

#include "NaGeSurface.h"

class NAKGE_API NaGeOffsetSurface : public NaGeSurface  
{
public:
	NaGeOffsetSurface(const NaGeSurface& pSurf, const double& Offset, bool Sense = true);
	virtual ~NaGeOffsetSurface();
	virtual NaGePoint3D PointAtPara(const double uPar, const double vPar);
	virtual NaGeVector3D NormalAt(const double uPar, const double vPar);
	virtual double FirstUParameter() const;
	virtual double LastUParameter() const;
	virtual double FirstVParameter() const;
	virtual double LastVParameter() const;
	virtual bool IsUClosed() const;
	virtual bool IsVClosed() const;
	SurfaceType Type() const;
	bool IsOfType(const SurfaceType&) const;
	virtual NaGeSurface* Copy() const;
	virtual void Translate(double dx, double dy, double dz);
	virtual void Translate(const NaGeVector3D&);
	virtual void Translate(const NaGePoint3D&, const NaGePoint3D&);
	virtual void Rotate(const NaGeOneAxis&, double);
	virtual void Scale(const NaGePoint3D&, double);
	virtual void Mirror(const NaGePoint3D&);
	virtual void Mirror(const NaGeOneAxis&);
	virtual void Mirror(const NaGePlane&);
private:
	NaGeSurface* pSurface;
	double itsOffset;
	bool dirSense;
};

#endif /* _OFFSETSURFACE_H */
