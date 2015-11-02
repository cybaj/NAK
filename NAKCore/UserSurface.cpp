// UserSurface.cpp: implementation of the CUserSurface class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UserSurface.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUserSurface::CUserSurface()
{

}

CUserSurface::~CUserSurface()
{

}

NaGePoint3D CUserSurface::PointAtPara(const double uPar, const double vPar)
{
	NaGePoint3D P;
	double u = uPar, v = vPar;
	double x, y, z;
	double pi = PI;
	x = (2 + cos(v/2)* sin(u) - sin(v/2)* sin(2 *u))* cos(v) ;
	y = (2 + cos(v/2)* sin(u) - sin(v/2)* sin(2 *u))* sin(v) ;
	z = sin(v/2)* sin(u) + cos(v/2) *sin(2* u) ;
	P.SetParam(x,y,z);
	return P;
}

double CUserSurface::FirstUParameter() const
{
	return 0;
}

double CUserSurface::LastUParameter() const
{
	return 2*PI;
}

double CUserSurface::FirstVParameter() const
{
	return 0;
}

double CUserSurface::LastVParameter() const
{
	return 2*PI;
}

bool CUserSurface::IsUClosed() const
{
	return true;
}

bool CUserSurface::IsVClosed() const
{
	return false;
}

NaGeSurface* CUserSurface::Copy() const
{
	CUserSurface* K = new CUserSurface();
	return K;
}

void CUserSurface::Translate(double dx, double dy, double dz)
{}

void CUserSurface::Translate(const NaGeVector3D&)
{}

void CUserSurface::Translate(const NaGePoint3D&, const NaGePoint3D&)
{}

void CUserSurface::Rotate(const NaGeOneAxis&, double)
{}

void CUserSurface::Scale(const NaGePoint3D&, double)
{}

void CUserSurface::Mirror(const NaGePoint3D&)
{}

void CUserSurface::Mirror(const NaGeOneAxis&)
{}

void CUserSurface::Mirror(const NaGePlane&)
{}
