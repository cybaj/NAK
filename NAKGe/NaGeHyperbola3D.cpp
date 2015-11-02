// Hyperbola3D.cpp: implementation of the NaGeHyperbola3D class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "NaGeHyperbola3D.h"
#include "NaGeMMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

NaGeHyperbola3D::NaGeHyperbola3D()
{
	cType = HYPERBOLA;
}

NaGeHyperbola3D::NaGeHyperbola3D(const NaGeAxisSystem& Ax, const double& maj, const double& min) : majorRadius(maj), minorRadius(min)
{
	itsLocation = Ax;
	cType = HYPERBOLA;
}

NaGeHyperbola3D::~NaGeHyperbola3D()
{

}

void NaGeHyperbola3D::Reverse()
{
	cReversed = !cReversed;
}

NaGeHyperbola3D NaGeHyperbola3D::Reversed() const
{
	NaGeHyperbola3D H = (*this);
	H.Reverse();
	return H;
}

double NaGeHyperbola3D::Eccentricity() const
{
	return (sqrt(majorRadius*majorRadius + minorRadius*minorRadius))/majorRadius;
}

NaGePoint3D NaGeHyperbola3D::PointAtPara(const double& Par)
{
	NaGeVector3D V;
	double par = Par;

	if(cReversed)
		par = -par;

	double ch = cosh(par);
	double sh = sinh(par);
	V = itsLocation.GetOrigin() + itsLocation.GetXDirection()*majorRadius*ch + itsLocation.GetYDirection()*minorRadius*sh;
	return V.Point();
}

double NaGeHyperbola3D::FirstParameter() const
{
	return -2*PI;
}

double NaGeHyperbola3D::LastParameter() const
{
	return 2*PI;
}

bool NaGeHyperbola3D::IsClosed() const
{
	return false;
}

bool NaGeHyperbola3D::operator == (const NaGeHyperbola3D& L) const
{
	bool b = (itsLocation == L.GetLocation() &&	majorRadius == L.GetMajorRadius()
			&& minorRadius == L.GetMinorRadius());
	return b;
}

void NaGeHyperbola3D::operator = (const NaGeHyperbola3D& L)
{
	itsLocation = L.GetLocation();
	majorRadius = L.GetMajorRadius();
	minorRadius = L.GetMinorRadius();
}

void NaGeHyperbola3D::SetMinorRadius(const double& rad)
{
	minorRadius = rad;
}

void NaGeHyperbola3D::SetMajorRadius(const double& rad)
{
	majorRadius = rad;
}

double NaGeHyperbola3D::GetMinorRadius() const
{
	return minorRadius;
}

double NaGeHyperbola3D::GetMajorRadius() const
{
	return majorRadius;
}

NaGeHyperbola3D NaGeHyperbola3D::GetConjugateBranch1() const
{
	NaGeVector3D Dir = itsLocation.GetYDirection();
	NaGeAxisSystem Ax(itsLocation.GetPosition(), itsLocation.GetDirection(), Dir);
	NaGeHyperbola3D H(Ax, minorRadius, majorRadius);
	return H;
}

NaGeHyperbola3D NaGeHyperbola3D::GetConjugateBranch2() const
{
	NaGeVector3D Dir = itsLocation.GetYDirection();
	Dir.Reverse();
	NaGeAxisSystem Ax(itsLocation.GetPosition(), itsLocation.GetDirection(), Dir);
	NaGeHyperbola3D H(Ax, minorRadius, majorRadius);
	return H;
}

NaGeHyperbola3D NaGeHyperbola3D::GetOtherBranch() const
{
	NaGeVector3D Dir = itsLocation.GetXDirection();
	Dir.Reverse();
	NaGeAxisSystem Ax(itsLocation.GetPosition(), itsLocation.GetDirection(), Dir);
	NaGeHyperbola3D H(Ax, majorRadius, minorRadius);
	return H;
}

void NaGeHyperbola3D::SetLocation(const NaGeAxisSystem& ax)
{
	itsLocation = ax;
}

NaGeAxisSystem NaGeHyperbola3D::GetLocation() const
{
	return itsLocation;
}

double NaGeHyperbola3D::FocalLength() const
{
	return 2.0 * sqrt(majorRadius * majorRadius + minorRadius * minorRadius);
}

NaGeCurve* NaGeHyperbola3D::Copy() const
{
	NaGeHyperbola3D* H = new NaGeHyperbola3D(itsLocation, majorRadius, minorRadius);
	return H;
}

void NaGeHyperbola3D::Translate(const NaGeOneAxis& Ax, const double& amt)
{
	NaGeGeometry::Translate(Ax, amt);
}

void NaGeHyperbola3D::Translate(double dx, double dy, double dz)
{
	itsLocation.Translate(dx,dy,dz);
}

void NaGeHyperbola3D::Translate(const NaGeVector3D& V)
{
	itsLocation.Translate(V);
}

void NaGeHyperbola3D::Translate(const NaGePoint3D& P1, const NaGePoint3D& P2)
{
	itsLocation.Translate(P1, P2);
}

void NaGeHyperbola3D::Rotate(const NaGeOneAxis& Ax, double fact)
{
	itsLocation.Rotate(Ax, fact);
}

void NaGeHyperbola3D::Scale(const NaGePoint3D& P, double fact)
{
	itsLocation.Scale(P, fact);
	majorRadius *= fact;
	minorRadius *= fact;
	if(majorRadius < 0)
		majorRadius = -majorRadius;
	if(minorRadius < 0)
		minorRadius = -minorRadius;
}

void NaGeHyperbola3D::Mirror(const NaGePoint3D& P)
{
	itsLocation.Mirror(P);
}

void NaGeHyperbola3D::Mirror(const NaGeOneAxis& Ax)
{
	itsLocation.Mirror(Ax);
}

void NaGeHyperbola3D::Mirror(const NaGePlane& Pln)
{
	itsLocation.Mirror(Pln);
}
