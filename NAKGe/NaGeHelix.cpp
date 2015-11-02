// Helix.cpp: implementation of the NaGeHelix class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "NaGeHelix.h"

#include "NaGePoint3D.h"
#include "NaGeVector3D.h"

//#ifdef _DEBUG
//#undef THIS_FILE
//static char THIS_FILE[]=__FILE__;
//#define new DEBUG_NEW
//#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

NaGeHelix::NaGeHelix(const NaGeAxisSystem& Ax, const double& radius, const double& start, const double& end, const double lead) : itsLead(lead)
{
	itsLocation = Ax;
	itsRadius = radius;
	itsFirstParameter = start;
	itsLastParameter = end;
}

NaGeHelix::~NaGeHelix()
{

}

void NaGeHelix::Reverse()
{
}

NaGePoint3D NaGeHelix::PointAtPara(const double& Par)
{
	NaGePoint3D P; NaGeVector3D V;
	double para = Par;

	double c = cos(para);
	double s = sin(para);
	double v = ((para-itsFirstParameter)/(PI*2))*itsLead;
	V = itsLocation.GetOrigin()+(itsLocation.GetXDirection()*c+itsLocation.GetYDirection()*s)
			*GetRadius()+itsLocation.GetDirection()*v;
	P.SetParam(V.GetX(), V.GetY(), V.GetZ());

	return P;
}

double NaGeHelix::FirstParameter() const
{
	return itsFirstParameter;
}

double NaGeHelix::LastParameter() const
{
	return itsLastParameter;
}

bool NaGeHelix::IsClosed() const
{
	return false;
}

CurveType NaGeHelix::Type() const
{
	return HELIX;
}

bool NaGeHelix::IsOfType(const CurveType& theType) const
{
	bool b = (theType == HELIX);
	return b;
}

NaGeCurve* NaGeHelix::Copy() const
{
	NaGeHelix* H = new NaGeHelix(itsLocation, itsRadius, itsFirstParameter, itsLastParameter, itsLead);
	return H;
}

void NaGeHelix::Translate(double dx, double dy, double dz)
{
}

void NaGeHelix::Translate(const NaGeVector3D&)
{
}

void NaGeHelix::Translate(const NaGePoint3D&, const NaGePoint3D&)
{
}

void NaGeHelix::Rotate(const NaGeOneAxis&, double)
{
}

void NaGeHelix::Scale(const NaGePoint3D&, double)
{
}

void NaGeHelix::Mirror(const NaGePoint3D&)
{
}

void NaGeHelix::Mirror(const NaGeOneAxis&)
{
}

void NaGeHelix::Mirror(const NaGePlane&)
{
}
