 
/***************************************************************************
 *            NaGeEllipse3D.h
 *

 ****************************************************************************/


#ifndef _ELLIPSE3D_H
#define _ELLIPSE3D_H

#ifdef NAKGE_EXPORTS
#define NAKGE_API __declspec(dllexport)
#else
#define NAKGE_API __declspec(dllimport)
#endif

#include "NaGeConic.h"
#include "NaGeMMath.h"

class NAKGE_API NaGeEllipse3d : public NaGeConic  
{
public:
	NaGeEllipse3d();
	NaGeEllipse3d(const NaGePoint3D& cp, const double min, const double maj);
	NaGeEllipse3d(const NaGeAxisSystem& Ax, double min, double maj);
	virtual ~NaGeEllipse3d();
	virtual void Reverse();
	NaGeEllipse3d Reversed() const;
	virtual NaGePoint3D PointAtPara(const double& para);
	inline virtual double FirstParameter() const { return 0; }
	inline virtual double LastParameter() const { return 2 * PI; }
	virtual double Eccentricity() const;
	virtual bool IsClosed() const;
	bool operator == (const NaGeEllipse3d& L) const;
	void operator = (const NaGeEllipse3d& L);
	inline void SetMinorRadius(const double& rad) { minorRadius = rad; }
	inline void SetMajorRadius(const double& rad) { majorRadius = rad; }
	inline double GetMinorRadius() const { return minorRadius; }
	inline double GetMajorRadius() const { return majorRadius; }
	inline void SetLocation(const NaGeAxisSystem& ax) { itsLocation = ax; }
	inline NaGeAxisSystem GetLocation() const { return itsLocation; }
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
private:
	double minorRadius;
	double majorRadius;
};

#endif /* _ELLIPSE3D_H */
