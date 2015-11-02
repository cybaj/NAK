// RuledSurface.cpp: implementation of the NaGeRuledSurface class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NaGeLine3D.h"
#include "NaGeRuledSurface.h"
#include "NaGeMMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

NaGeRuledSurface::NaGeRuledSurface(const NaGeCurve* C1, const NaGeCurve* C2)
{
	sType = RULED;
	baseCurve = C1->Copy();
	secondRail = C2->Copy();
}

NaGeRuledSurface::~NaGeRuledSurface()
{
	if(baseCurve)
		delete baseCurve;
	if(secondRail)
		delete secondRail;
}

NaGeCurve* NaGeRuledSurface::RailCurve1() const
{
	return baseCurve;
}

NaGeCurve* NaGeRuledSurface::RailCurve2() const
{
	return secondRail;
}


NaGePoint3D NaGeRuledSurface::PointAtPara(const double uPar, const double vPar)
{
	double uParR1 = baseCurve->FirstParameter() + 
		((baseCurve->LastParameter() - baseCurve->FirstParameter())*uPar);
	double uParR2 = secondRail->FirstParameter() +
		((secondRail->LastParameter() - secondRail->FirstParameter())*uPar);

	NaGePoint3D P1 = baseCurve->PointAtPara(uParR1);
	NaGePoint3D P2 = secondRail->PointAtPara(uParR2);
	NaGeLine3D L(P1, P2);
	NaGePoint3D P = L.PointAtPara(vPar);
	return P;
}

NaGeVector3D NaGeRuledSurface::NormalAt(const double uPar, const double vPar)
{
	NaGePoint3D Po, Pu, Pv;
	NaGeVector3D N;

	if(uPar == 1 && vPar == 1)
	{
		Po = PointAtPara(uPar, vPar);
		Pu = PointAtPara(uPar-0.001, vPar);
		Pv = PointAtPara(uPar, vPar-0.001);
		NaGeVector3D Vu(Po, Pu), Vv(Po, Pv);
		N = Vu^Vv;
		return N;
	}
	else if(uPar == 1 && vPar != 1)
	{
		Po = PointAtPara(uPar, vPar);
		Pu = PointAtPara(uPar-0.001, vPar);
		Pv = PointAtPara(uPar, vPar+0.001);
		NaGeVector3D Vu(Po, Pu), Vv(Po, Pv);
		N = Vv^Vu;
		return N;
	}
	else if(uPar != 1 && vPar == 1)
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

double NaGeRuledSurface::FirstUParameter() const
{
	return 0;
}

double NaGeRuledSurface::LastUParameter() const
{
	return 1;
}

double NaGeRuledSurface::FirstVParameter() const
{
	return 0;
}

double NaGeRuledSurface::LastVParameter() const
{
	return 1;
}

bool NaGeRuledSurface::IsUClosed() const
{
	return false;
}

bool NaGeRuledSurface::IsVClosed() const
{
	return false;
}

NaGeSurface* NaGeRuledSurface::Copy() const
{
	NaGeRuledSurface* R = new NaGeRuledSurface(baseCurve, secondRail);
	return R;
}

void NaGeRuledSurface::Translate(const NaGeOneAxis& Ax, const double& amt)
{
	NaGeGeometry::Translate(Ax, amt);
}

void NaGeRuledSurface::Translate(double dx, double dy, double dz)
{
	baseCurve->Translate(dx,dy,dz);
	secondRail->Translate(dx,dy,dz);
}

void NaGeRuledSurface::Translate(const NaGeVector3D& V)
{
	baseCurve->Translate(V);
	secondRail->Translate(V);
}

void NaGeRuledSurface::Translate(const NaGePoint3D& P1, const NaGePoint3D& P2)
{
	baseCurve->Translate(P1, P2);
	secondRail->Translate(P1, P2);
}

void NaGeRuledSurface::Rotate(const NaGeOneAxis& Ax, double ang)
{
	baseCurve->Rotate(Ax, ang);
	secondRail->Rotate(Ax, ang);
}

void NaGeRuledSurface::Scale(const NaGePoint3D& P, double fact)
{
	baseCurve->Scale(P, fact);
	secondRail->Scale(P, fact);
}

void NaGeRuledSurface::Mirror(const NaGePoint3D& P)
{
	baseCurve->Mirror(P);
	secondRail->Mirror(P);
}

void NaGeRuledSurface::Mirror(const NaGeOneAxis& Ax)
{
	baseCurve->Mirror(Ax);
	secondRail->Mirror(Ax);
}

void NaGeRuledSurface::Mirror(const NaGePlane& Pln)
{
	baseCurve->Mirror(Pln);
	secondRail->Mirror(Pln);
}

