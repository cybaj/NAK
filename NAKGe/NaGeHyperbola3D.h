/***************************************************************************
 *            NaGeHyperbola3D.h
 *
 ****************************************************************************/


#ifndef _HYPERBOLA3D_H
#define _HYPERBOLA3D_H

#ifdef NAKGE_EXPORTS
#define NAKGE_API __declspec(dllexport)
#else
#define NAKGE_API __declspec(dllimport)
#endif

#include "NaGeConic.h"

class NAKGE_API NaGeHyperbola3D : public NaGeConic  
{
public:
	NaGeHyperbola3D();
	NaGeHyperbola3D(const NaGeAxisSystem&, const double&, const double&);
	virtual ~NaGeHyperbola3D();
	virtual void Reverse();
	NaGeHyperbola3D Reversed() const;
	virtual double Eccentricity() const;
	virtual NaGePoint3D PointAtPara(const double& para);
	virtual double FirstParameter() const;
	virtual double LastParameter() const;
	virtual bool IsClosed() const;
	bool operator == (const NaGeHyperbola3D& L) const;

	void operator = (const NaGeHyperbola3D& L);
	void SetMinorRadius(const double&);
	void SetMajorRadius(const double&);
	double GetMinorRadius() const;
	double GetMajorRadius() const;
	NaGeHyperbola3D GetConjugateBranch1() const;
	NaGeHyperbola3D GetConjugateBranch2() const;
	NaGeHyperbola3D GetOtherBranch() const;
	void SetLocation(const NaGeAxisSystem& ax);
	NaGeAxisSystem GetLocation() const;
	double FocalLength() const;
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
	double majorRadius;
	double minorRadius;
};

#endif /* _HYPERBOLA3D_H */
