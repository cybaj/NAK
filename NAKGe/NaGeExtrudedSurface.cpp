// ExtrudedSurface.cpp: implementation of the NaGeExtrudedSurface class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "NaGeExtrudedSurface.h"
#include "NaGeMMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

NaGeExtrudedSurface::NaGeExtrudedSurface(const NaGeCurve* C, const NaGeVector3D& Dir, const double& s, const double& e) : startLimit(s), endLimit(e)
{
	sType = EXTRUDED;
	baseCurve = C->Copy();
	itsDirection = Dir;
}

NaGeExtrudedSurface::~NaGeExtrudedSurface()
{
	if(baseCurve)
		delete baseCurve;
}

NaGePoint3D NaGeExtrudedSurface::PointAtPara(const double uPar, const double vPar)
{
	NaGeVector3D P;
	NaGeVector3D G(baseCurve->PointAtPara(uPar));
	NaGeVector3D Dir = itsDirection*vPar;
	P = G+Dir;
	return P.Point();
}

double NaGeExtrudedSurface::FirstUParameter() const
{
	return baseCurve->FirstParameter();
}

double NaGeExtrudedSurface::LastUParameter() const
{
	return baseCurve->LastParameter();
}

double NaGeExtrudedSurface::FirstVParameter() const
{
	return startLimit;
}

double NaGeExtrudedSurface::LastVParameter() const
{
	return endLimit;
}

bool NaGeExtrudedSurface::IsUClosed() const
{
	return false;
}

bool NaGeExtrudedSurface::IsVClosed() const
{
	return false;
}

NaGeSurface* NaGeExtrudedSurface::Copy() const
{
	NaGeExtrudedSurface* R = new NaGeExtrudedSurface(baseCurve, itsDirection, startLimit, endLimit);
	return R;
}

void NaGeExtrudedSurface::Translate(const NaGeOneAxis& Ax, const double& amt)
{
	NaGeGeometry::Translate(Ax, amt);
}

void NaGeExtrudedSurface::Translate(double dx, double dy, double dz)
{
	baseCurve->Translate(dx,dy,dz);
}

void NaGeExtrudedSurface::Translate(const NaGeVector3D& V)
{
	baseCurve->Translate(V);
}

void NaGeExtrudedSurface::Translate(const NaGePoint3D& P1, const NaGePoint3D& P2)
{
	baseCurve->Translate(P1, P2);
}

void NaGeExtrudedSurface::Rotate(const NaGeOneAxis& Ax, double ang)
{
	baseCurve->Rotate(Ax, ang);
}

void NaGeExtrudedSurface::Scale(const NaGePoint3D& P, double fact)
{
	baseCurve->Scale(P, fact);
}

void NaGeExtrudedSurface::Mirror(const NaGePoint3D& P)
{
	baseCurve->Mirror(P);
}

void NaGeExtrudedSurface::Mirror(const NaGeOneAxis& Ax)
{
	baseCurve->Mirror(Ax);
}

void NaGeExtrudedSurface::Mirror(const NaGePlane& Pln)
{
	baseCurve->Mirror(Pln);
}
