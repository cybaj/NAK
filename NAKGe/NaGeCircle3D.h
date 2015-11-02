 
/***************************************************************************
 *            NaGeCircle3D.h
 *
 ****************************************************************************/


#ifndef _CIRCLE3D_H
#define _CIRCLE3D_H

#ifdef NAKGE_EXPORTS
#define NAKGE_API __declspec(dllexport)
#else
#define NAKGE_API __declspec(dllimport)
#endif

#include "NaGeConic.h"
#include "NaGeAxisSystem.h"
#include "NaGeMatrix33.h"
#include "NaGeMMath.h"

class NaGePoint3D;
class NaGeAxisSystem;

class NAKGE_API NaGeCircle3d : public NaGeConic  
{
    public:
	NaGeCircle3d();
	NaGeCircle3d(const NaGePoint3D&, const double);
	NaGeCircle3d(const NaGeAxisSystem& ax, const double rad);
	NaGeCircle3d(const NaGePoint3D&, const NaGePoint3D&, const NaGePoint3D&);
	NaGeCircle3d(const NaGeCircle3d& C);
	virtual ~NaGeCircle3d();
	virtual void Reverse();
	NaGeCircle3d Reversed() const;
	virtual NaGePoint3D PointAtPara(const double& para);
	inline virtual double FirstParameter() const { return 0; }
	inline virtual double LastParameter() const { return 2*PI; }
	inline virtual double Eccentricity() const { return 0.0; }
	virtual bool IsClosed() const;
	bool operator == (const NaGeCircle3d& L) const;
	NaGeCircle3d operator = (const NaGeCircle3d& C);
	inline void SetRadius(const double& r) { itsRadius = r; }
	inline void SetLocation(const NaGeAxisSystem& ax) { itsLocation = ax; }
	inline NaGeAxisSystem GetLocation() const { return itsLocation; }
	inline double GetRadius() const { return itsRadius; }
	inline NaGePoint3D Center() const { return itsLocation.GetPosition(); }
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
    protected:
	double itsRadius;
};

#endif /* _CIRCLE3D_H */
