/***************************************************************************
 *           NaGeTorus.h
 *
 ****************************************************************************/


#ifndef _TORUS_H
#define _TORUS_H

#ifdef NAKGE_EXPORTS
#define NAKGE_API __declspec(dllexport)
#else
#define NAKGE_API __declspec(dllimport)
#endif

#include "NaGeBasicSurface.h"
#include "NaGeMMath.h"

class NAKGE_API NaGeTorus : public NaGeBasicSurface  
{
public:
	NaGeTorus();
	NaGeTorus(const NaGeAxisSystem&, const double& maj, const double& min, const double& uStart = 0, const double& uEnd = 2*PI, const double& vStart = 0, const double& vEnd = 2*PI);
	virtual ~NaGeTorus();
	inline void SetMinorRadius(const double& rad) { minorRadius = rad; }
	inline void SetMajorRadius(const double& rad) { majorRadius = rad; }
	inline double GetMinorRadius() const { return minorRadius; }
	inline double GetMajorRadius() const { return majorRadius; }
	virtual NaGePoint3D PointAtPara(const double uPar, const double vPar);
	virtual NaGeVector3D NormalAt(const double uPar, const double vPar);
	inline virtual double FirstUParameter() const { return itsFirstUParameter; }
	inline virtual double LastUParameter() const  { return itsLastUParameter; }
	inline virtual double FirstVParameter() const { return itsFirstVParameter; }
	inline virtual double LastVParameter() const  { return itsLastVParameter; }
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
	double majorRadius;
	double minorRadius;	
};

#endif /* _TORUS_H */
