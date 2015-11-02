
 
/***************************************************************************
 *            NaGeParabola3D.h
 *
 ****************************************************************************/


#ifndef _PARABOLA3D_H
#define _PARABOLA3D_H

#ifdef NAKGE_EXPORTS
#define NAKGE_API __declspec(dllexport)
#else
#define NAKGE_API __declspec(dllimport)
#endif

#include "NaGeConic.h"

class NAKGE_API NaGeParabola3D : public NaGeConic  
{
public:
	NaGeParabola3D();
	NaGeParabola3D(const NaGeAxisSystem& Ax, const double fLen);
	virtual ~NaGeParabola3D();
	virtual void Reverse();
	NaGeParabola3D Reversed() const;
	virtual double Eccentricity() const;
	virtual NaGePoint3D PointAtPara(const double& para);
	virtual double FirstParameter() const;
	virtual double LastParameter() const;
	virtual bool IsClosed() const;
	bool operator == (const NaGeParabola3D& L) const;
	void operator = (const NaGeParabola3D& L);
	void SetLocation(const NaGeAxisSystem&);
	NaGeAxisSystem GetLocation() const;
	void SetFocalLength(const double&);
	double GetFocalLength() const;
	void SetYRange(const double& lower, const double& upper);
	double GetLowerRange() const;
	double GetUpperRange() const;
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
	double focalLength;
	double lowerRange;
	double upperRange;
	bool rangeSet;
};

#endif /* _PARABOLA3D_H */
