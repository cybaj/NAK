 
/***************************************************************************
 *            NaGeCylinder.h
 *
 ****************************************************************************/


#ifndef _CYLINDER_H
#define _CYLINDER_H

#ifdef NAKGE_EXPORTS
#define NAKGE_API __declspec(dllexport)
#else
#define NAKGE_API __declspec(dllimport)
#endif

#include "NaGeBasicSurface.h"
#include "NaGeMMath.h"

class NaGeCircle3d;
class NaGeAxisSystem;

class NAKGE_API NaGeCylinder : public NaGeBasicSurface  
{
    public:
	NaGeCylinder(){}
	NaGeCylinder(const NaGeCircle3d&, const double& ht);
	NaGeCylinder(const NaGeAxisSystem&, const double& ht, const double& rad, const double& uStart = 0, const double& uEnd = 2*PI);
	virtual ~NaGeCylinder();
	inline void SetRadius(const double& r) { itsRadius = r; }
	inline void SetHeight(const double& h) { itsHeight = h; }
	inline double GetRadius() const { return itsRadius; }
	inline double GetHeight() const { return itsHeight; }
	virtual NaGePoint3D PointAtPara(const double uPar, const double vPar);
	inline virtual double FirstUParameter() const { return itsFirstUParameter; }
	inline virtual double LastUParameter() const  { return itsLastUParameter; }
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
	double itsHeight;	
	double itsRadius;
};

#endif /* _CYLINDER_H */
