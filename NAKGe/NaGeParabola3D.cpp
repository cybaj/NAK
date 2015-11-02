// Parabola3D.cpp: implementation of the NaGeParabola3D class.
//
//////////////////////////////////////////////////////////////////////


#include "stdafx.h"

#include "NaGeParabola3D.h"
#include "NaGeMMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

NaGeParabola3D::NaGeParabola3D()

{
	cType = PARABOLA;
}

NaGeParabola3D::NaGeParabola3D(const NaGeAxisSystem& Ax, const double fLen)
{

	itsLocation = Ax;
	focalLength = fLen;
	cType = PARABOLA;
	rangeSet = false;
}

NaGeParabola3D::~NaGeParabola3D()
{

}

void NaGeParabola3D::Reverse()
{
	cReversed = !cReversed;
}

NaGeParabola3D NaGeParabola3D::Reversed() const
{
	NaGeParabola3D P = (*this);
	P.Reverse();
	return P;
}

double NaGeParabola3D::Eccentricity() const
{
	return 1;
}

NaGePoint3D NaGeParabola3D::PointAtPara(const double& Par)
{

	NaGeVector3D V;
	double par = Par;

	if(cReversed)
		par = -par;

	V = itsLocation.GetOrigin() + itsLocation.GetXDirection()*par*par/(4.*focalLength) + itsLocation.GetYDirection()*par;
	return V.Point();
}

double NaGeParabola3D::FirstParameter() const
{
	if(!rangeSet)
	{
		return -INFINITY;
	}
	else
		return lowerRange/2*focalLength;
}

double NaGeParabola3D::LastParameter() const
{
	if(!rangeSet)
	{
		return INFINITY;
	}
	else
		return upperRange/2*focalLength;
}

bool NaGeParabola3D::IsClosed() const
{
	return false;
}

bool NaGeParabola3D::operator == (const NaGeParabola3D& L) const
{
	bool b = (itsLocation == L.GetLocation() && focalLength == L.GetFocalLength() 
		&& lowerRange == L.GetLowerRange() && upperRange == L.GetUpperRange());
	return b;
}

void NaGeParabola3D::operator = (const NaGeParabola3D& L)
{
	itsLocation = L.GetLocation();
	focalLength = L.GetFocalLength();
	lowerRange = L.GetLowerRange();
	upperRange = L.GetUpperRange();
}

void NaGeParabola3D::SetLocation(const NaGeAxisSystem& Ax)
{
	itsLocation = Ax;
}

NaGeAxisSystem NaGeParabola3D::GetLocation() const
{
	return itsLocation;
}

void NaGeParabola3D::SetFocalLength(const double& fLen)
{
	focalLength = fLen;
}

double NaGeParabola3D::GetFocalLength() const
{
	return focalLength;
}

void NaGeParabola3D::SetYRange(const double& lower, const double& upper)
{
	lowerRange = lower;
	upperRange = upper;
	rangeSet = true;
}

double NaGeParabola3D::GetLowerRange() const
{
	return lowerRange;
}

double NaGeParabola3D::GetUpperRange() const
{
	return upperRange;
}

NaGeCurve* NaGeParabola3D::Copy() const
{
	NaGeParabola3D* P = new NaGeParabola3D(itsLocation, focalLength);
	P->SetYRange(lowerRange, upperRange);
	return P;
}

void NaGeParabola3D::Translate(const NaGeOneAxis& Ax, const double& amt)
{
	NaGeGeometry::Translate(Ax, amt);
}

void NaGeParabola3D::Translate(double dx, double dy, double dz)
{
	itsLocation.Translate(dx,dy,dz);
}

void NaGeParabola3D::Translate(const NaGeVector3D& V)
{
	itsLocation.Translate(V);
}

void NaGeParabola3D::Translate(const NaGePoint3D& P1, const NaGePoint3D& P2)
{
	itsLocation.Translate(P1, P2);
}

void NaGeParabola3D::Rotate(const NaGeOneAxis& Ax, double fact)
{
	itsLocation.Rotate(Ax, fact);
}

void NaGeParabola3D::Scale(const NaGePoint3D& P, double fact)
{
	itsLocation.Scale(P, fact);
	focalLength *= fact;
	lowerRange *= fact;
	upperRange *= fact;
	if(focalLength < 0)
		focalLength = -focalLength;
}

void NaGeParabola3D::Mirror(const NaGePoint3D& P)
{
	itsLocation.Mirror(P);
}

void NaGeParabola3D::Mirror(const NaGeOneAxis& Ax)
{
	itsLocation.Mirror(Ax);
}

void NaGeParabola3D::Mirror(const NaGePlane& Pln)
{
	itsLocation.Mirror(Pln);
}
