// RevolvedSurface.cpp: implementation of the NaGeRevolvedSurface class.
//
//////////////////////////////////////////////////////////////////////


#include "stdafx.h"

#include "NaGeRevolvedSurface.h"
#include "NaGePoint3D.h"
#include "NaGeVector3D.h"
#include "NaGeLine3D.h"
#include "NaGeAxisSystem.h"
#include "NaGeMMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

NaGeRevolvedSurface::NaGeRevolvedSurface(const NaGeCurve* C, const NaGeOneAxis& Ax, const double& st, const double& en) : itsAxisOfRevol(Ax), startAngle(st), endAngle(en)
{
	sType = REVOLVED;
	baseCurve = C->Copy();
}

NaGeRevolvedSurface::~NaGeRevolvedSurface()
{
	if(baseCurve)
		delete baseCurve;
}

NaGePoint3D NaGeRevolvedSurface::PointAtPara(const double uPar, const double vPar)
{
	NaGePoint3D P;
	NaGePoint3D CP = baseCurve->PointAtPara(uPar);
	NaGeOneAxis ax = itsAxisOfRevol;
	CP.Rotate(ax, vPar);
	P = CP;
	return P;
}

NaGeVector3D NaGeRevolvedSurface::NormalAt(const double uPar, const double vPar)
{
	NaGePoint3D Po, Pu, Pv;
	NaGeVector3D N;

	if(uPar == LastUParameter() && vPar == LastVParameter())
	{
		Po = PointAtPara(uPar, vPar);
		Pu = PointAtPara(uPar-0.001, vPar);
		Pv = PointAtPara(uPar, vPar-0.001);
		NaGeVector3D Vu(Po, Pu), Vv(Po, Pv);
		N = Vu^Vv;
		return N;
	}
	else if(uPar == LastUParameter() && vPar != LastVParameter())
	{
		Po = PointAtPara(uPar, vPar);
		Pu = PointAtPara(uPar-0.001, vPar);
		Pv = PointAtPara(uPar, vPar+0.001);
		NaGeVector3D Vu(Po, Pu), Vv(Po, Pv);
		N = Vv^Vu;
		return N;
	}
	else if(uPar != LastUParameter() && vPar == LastVParameter())
	{
		Po = PointAtPara(uPar, vPar);
		Pu = PointAtPara(uPar+0.001, vPar);
		Pv = PointAtPara(uPar, vPar-0.001);
		NaGeVector3D Vu(Po, Pu), Vv(Po, Pv);
		N = Vv^Vu;
		return N;
	}
	else
	{
		Po = PointAtPara(uPar, vPar);
		Pu = PointAtPara(uPar+0.001, vPar);
		Pv = PointAtPara(uPar, vPar+0.001);
		NaGeVector3D Vu(Po, Pu), Vv(Po, Pv);
		N = Vu^Vv;
		return N;
	}
}

double NaGeRevolvedSurface::FirstUParameter() const
{
	return baseCurve->FirstParameter();
}

double NaGeRevolvedSurface::LastUParameter() const
{
	return baseCurve->LastParameter();
}

double NaGeRevolvedSurface::FirstVParameter() const
{
	return startAngle;
}

double NaGeRevolvedSurface::LastVParameter() const
{
	return endAngle;
}

bool NaGeRevolvedSurface::IsUClosed() const
{
	return false;
}

bool NaGeRevolvedSurface::IsVClosed() const
{
	bool b = ((endAngle - startAngle) - (2 * PI) == 0.0);
	return b;
}

NaGeSurface* NaGeRevolvedSurface::Copy() const
{
	NaGeRevolvedSurface* R = new NaGeRevolvedSurface(baseCurve, itsAxisOfRevol, startAngle, endAngle);
	return R;
}

void NaGeRevolvedSurface::Translate(const NaGeOneAxis& Ax, const double& amt)
{
	NaGeGeometry::Translate(Ax, amt);
}

void NaGeRevolvedSurface::Translate(double dx, double dy, double dz)
{
	baseCurve->Translate(dx,dy,dz);
	itsAxisOfRevol.Translate(dx,dy,dz);
}

void NaGeRevolvedSurface::Translate(const NaGeVector3D& V)
{
	baseCurve->Translate(V);
	itsAxisOfRevol.Translate(V);
}

void NaGeRevolvedSurface::Translate(const NaGePoint3D& P1, const NaGePoint3D& P2)
{
	baseCurve->Translate(P1, P2);
	itsAxisOfRevol.Translate(P1, P2);
}

void NaGeRevolvedSurface::Rotate(const NaGeOneAxis& Ax, double ang)
{
	baseCurve->Rotate(Ax, ang);
	itsAxisOfRevol.Rotate(Ax, ang);
}

void NaGeRevolvedSurface::Scale(const NaGePoint3D& P, double fact)
{
	baseCurve->Scale(P, fact);
	itsAxisOfRevol.Scale(P, fact);
}

void NaGeRevolvedSurface::Mirror(const NaGePoint3D& P)
{
	baseCurve->Mirror(P);
	itsAxisOfRevol.Mirror(P);
}

void NaGeRevolvedSurface::Mirror(const NaGeOneAxis& Ax)
{
	baseCurve->Mirror(Ax);
	itsAxisOfRevol.Mirror(Ax);
}

void NaGeRevolvedSurface::Mirror(const NaGePlane& Pln)
{
	baseCurve->Mirror(Pln);
	itsAxisOfRevol.Mirror(Pln);
}
