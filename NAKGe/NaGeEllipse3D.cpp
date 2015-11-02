// Ellipse3D.cpp: implementation of the NaGeEllipse3d class.
//
//////////////////////////////////////////////////////////////////////


#include "stdafx.h"

#include "NaGeEllipse3d.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

NaGeEllipse3d::NaGeEllipse3d()
{
	cType = ELLIPSE;
}

NaGeEllipse3d::NaGeEllipse3d(const NaGePoint3D& cp, const double min, const double maj) : minorRadius(min)
, majorRadius(maj)
{
	NaGeAxisSystem ax(cp, NaGeVector3D(0,0,1), NaGeVector3D(1,0,0));
	itsLocation = ax;
	cType = ELLIPSE;
}

NaGeEllipse3d::NaGeEllipse3d(const NaGeAxisSystem& Ax, double min, double maj) : minorRadius(min), majorRadius(maj)
{
	itsLocation = Ax;
	cType = ELLIPSE;
}

NaGeEllipse3d::~NaGeEllipse3d()
{
}

void NaGeEllipse3d::Reverse()
{
	cReversed = !cReversed;
}

NaGeEllipse3d NaGeEllipse3d::Reversed() const
{
	NaGeEllipse3d E = (*this);
	E.Reverse();
	return E;
}

double NaGeEllipse3d::Eccentricity() const
{
	if(majorRadius == 0.0)
		return 0.0;
	else
		return sqrt(majorRadius * majorRadius - 
		minorRadius * minorRadius) / majorRadius;
}

NaGePoint3D NaGeEllipse3d::PointAtPara(const double& Par)
{
	NaGeVector3D V;
	double para = Par;

	if(cReversed)
		para = 2*PI - para;

	double c = cos(para);
	double s = sin(para);
	V = itsLocation.GetOrigin() + itsLocation.GetXDirection()*majorRadius*c
		+ itsLocation.GetYDirection()*minorRadius*s;

	return V.Point();
}

bool NaGeEllipse3d::IsClosed() const
{
	return true;
}

bool NaGeEllipse3d::operator == (const NaGeEllipse3d& E) const
{
	bool eq = (itsLocation == E.GetLocation() && majorRadius == E.GetMajorRadius()
				&& minorRadius == E.GetMinorRadius());
	return eq;
}

void NaGeEllipse3d::operator = (const NaGeEllipse3d& E)
{
	itsLocation = E.GetLocation();
	majorRadius = E.GetMajorRadius();
	minorRadius = E.GetMinorRadius();
}

NaGeCurve* NaGeEllipse3d::Copy() const
{
	NaGeEllipse3d* E = new NaGeEllipse3d(itsLocation, majorRadius, minorRadius);
	return E;
}

void NaGeEllipse3d::Translate(const NaGeOneAxis& Ax, const double& amt)
{
	NaGeGeometry::Translate(Ax, amt);
}

void NaGeEllipse3d::Translate(double dx, double dy, double dz)
{
	itsLocation.Translate(dx,dy,dz);
}

void NaGeEllipse3d::Translate(const NaGeVector3D& V)
{
	itsLocation.Translate(V);
}

void NaGeEllipse3d::Translate(const NaGePoint3D& P1, const NaGePoint3D& P2)
{
	itsLocation.Translate(P1, P2);
}

void NaGeEllipse3d::Rotate(const NaGeOneAxis& Ax, double fact)
{
	itsLocation.Rotate(Ax, fact);
}

void NaGeEllipse3d::Scale(const NaGePoint3D& P, double fact)
{
	itsLocation.Scale(P, fact);
	majorRadius *= fact;
	minorRadius *= fact;
	if(majorRadius < 0)
		majorRadius = -majorRadius;
	if(minorRadius < 0)
		minorRadius = -minorRadius;
}

void NaGeEllipse3d::Mirror(const NaGePoint3D& P)
{
	itsLocation.Mirror(P);
}

void NaGeEllipse3d::Mirror(const NaGeOneAxis& Ax)
{
	itsLocation.Mirror(Ax);
}

void NaGeEllipse3d::Mirror(const NaGePlane& Pln)
{
	itsLocation.Mirror(Pln);
}
