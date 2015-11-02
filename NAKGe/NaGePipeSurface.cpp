// PipeSurface.cpp: implementation of the NaGePipeSurface class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "NaGePipeSurface.h"
#include "NaGePoint3D.h"
#include "NaGeCircle3D.h"
#include "NaGeEllipse3D.h"
#include "NaGeOneAxis.h"
#include "NaGeAxisSystem.h"
#include "NaGeGeomException.h"
#include "NaGeMMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

NaGePipeSurface::NaGePipeSurface()
{
	sType = PIPE;
}

NaGePipeSurface::NaGePipeSurface(const NaGeCurve* C, const double& radius) : itsRadius(radius)
{
	sType = PIPE;
	circular = true;
	baseCurve = C->Copy();
}

NaGePipeSurface::NaGePipeSurface(const NaGeCurve* C, const double& majrad, const double& minrad) : itsRadius(minrad), 
																						itsMajorRadius(majrad)
{
	sType = PIPE;
	circular = false;
	baseCurve = C->Copy();
}

NaGePipeSurface::~NaGePipeSurface()
{
	if(baseCurve)
		delete baseCurve;
}

NaGePoint3D NaGePipeSurface::PointAtPara(const double uPar, const double vPar)
{
	NaGePoint3D P;
	NaGePoint3D O = baseCurve->PointAtPara(uPar);
	NaGePoint3D D;
	NaGeVector3D Dir;
	if(uPar == 1)
	{
		D = baseCurve->PointAtPara(uPar-0.001);
		Dir = NaGeVector3D(O, D);
	}
	else
	{
		D = baseCurve->PointAtPara(uPar+0.001);
		Dir = NaGeVector3D(D, O);
	}
	NaGePoint3D fp = baseCurve->PointAtPara(baseCurve->FirstParameter());
	NaGePoint3D dfp = baseCurve->PointAtPara(baseCurve->FirstParameter()+0.001);
	NaGeVector3D Z(fp, dfp);
	NaGeAxisSystem Ax(O, Z);
		
	if(circular)
	{
		NaGeCircle3d C(Ax, itsRadius);
		if(uPar == baseCurve->FirstParameter())
			C.Reverse();
		P = C.PointAtPara(vPar);
	}
	else
	{
		NaGeEllipse3d C(Ax, itsMajorRadius, itsRadius);
		if(uPar == baseCurve->FirstParameter())
			C.Reverse();
		P = C.PointAtPara(vPar);
	}

	NaGeVector3D Ref = Dir^Z;
	double ang = Dir.Angle(Z, Ref);

	P.Translate(Ax.GetPosition(), O);
	P.Rotate(NaGeOneAxis(O, Ref), -ang);

	return P;
}

NaGeVector3D NaGePipeSurface::NormalAt(const double uPar, const double vPar)
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
double NaGePipeSurface::FirstUParameter() const
{
	return baseCurve->FirstParameter();
}

double NaGePipeSurface::LastUParameter() const
{
	return baseCurve->LastParameter();
}

double NaGePipeSurface::FirstVParameter() const
{
	return 0;
}

double NaGePipeSurface::LastVParameter() const
{
	return 2*PI;
}

bool NaGePipeSurface::IsUClosed() const
{
	return false;
}

bool NaGePipeSurface::IsVClosed() const
{
	return false;
}

NaGeSurface* NaGePipeSurface::Copy() const
{
	NaGePipeSurface* P;
	if(circular)
		P = new NaGePipeSurface(baseCurve, itsRadius);
	else
		P = new NaGePipeSurface(baseCurve, itsMajorRadius, itsRadius);
	return P;
}

void NaGePipeSurface::Translate(const NaGeOneAxis& Ax, const double& amt)
{
	NaGeGeometry::Translate(Ax, amt);
}

void NaGePipeSurface::Translate(double dx, double dy, double dz)
{
	baseCurve->Translate(dx,dy,dz);
}

void NaGePipeSurface::Translate(const NaGeVector3D& V)
{
	baseCurve->Translate(V);
}

void NaGePipeSurface::Translate(const NaGePoint3D& P1, const NaGePoint3D& P2)
{
	baseCurve->Translate(P1, P2);
}

void NaGePipeSurface::Rotate(const NaGeOneAxis& Ax, double ang)
{
	baseCurve->Rotate(Ax, ang);
}

void NaGePipeSurface::Scale(const NaGePoint3D& P, double fact)
{
	baseCurve->Scale(P, fact);
}

void NaGePipeSurface::Mirror(const NaGePoint3D& P)
{
	baseCurve->Mirror(P);
}

void NaGePipeSurface::Mirror(const NaGeOneAxis& Ax)
{
	baseCurve->Mirror(Ax);
}

void NaGePipeSurface::Mirror(const NaGePlane& Pln)
{
	baseCurve->Mirror(Pln);
}
