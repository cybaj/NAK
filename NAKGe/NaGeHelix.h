
// NaGeHelix.h: interface for the NaGeHelix class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HELIX_H__8195CAF2_E922_4631_8E35_AD84A07EE6A1__INCLUDED_)
#define AFX_HELIX_H__8195CAF2_E922_4631_8E35_AD84A07EE6A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef NAKGE_EXPORTS
#define NAKGE_API __declspec(dllexport)
#else
#define NAKGE_API __declspec(dllimport)
#endif

#include "NaGeCircle3D.h"
#include "NaGeAxisSystem.h"

class NAKGE_API NaGeHelix : public NaGeCircle3d 
{
public:
	NaGeHelix(const NaGeAxisSystem& Ax, const double& radius, const double& start, const double& end, const double lead);
	virtual ~NaGeHelix();
	virtual void Reverse();
	virtual NaGePoint3D PointAtPara(const double& para);
	virtual double FirstParameter() const;
	virtual double LastParameter() const;
	virtual bool IsClosed() const;
	CurveType Type() const;
	bool IsOfType(const CurveType&) const;
	virtual NaGeCurve* Copy() const;
	virtual void Translate(double dx, double dy, double dz);
	virtual void Translate(const NaGeVector3D&);
	virtual void Translate(const NaGePoint3D&, const NaGePoint3D&);
	virtual void Rotate(const NaGeOneAxis&, double);
	virtual void Scale(const NaGePoint3D&, double);
	virtual void Mirror(const NaGePoint3D&);
	virtual void Mirror(const NaGeOneAxis&);
	virtual void Mirror(const NaGePlane&);
	double Lead() const { return itsLead;}
private:
	//NaGeAxisSystem itsLocation;
	//double itsRadius;
	double itsFirstParameter;
	double itsLastParameter;
	double itsLead;
};

#endif // !defined(AFX_HELIX_H__8195CAF2_E922_4631_8E35_AD84A07EE6A1__INCLUDED_)
