// OffsetSurface.cpp: implementation of the NaGeOffsetSurface class.
//
//////////////////////////////////////////////////////////////////////


#include "stdafx.h"

#include "NaGeOffsetSurface.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

NaGeOffsetSurface::NaGeOffsetSurface(const NaGeSurface& pSurf, const double& Offset, bool Sense) : itsOffset(Offset), dirSense(Sense)
{
	pSurface = pSurf.Copy();
}

NaGeOffsetSurface::~NaGeOffsetSurface()
{
	if(pSurface)
		delete pSurface;
}

NaGePoint3D NaGeOffsetSurface::PointAtPara(const double uPar, const double vPar)
{
	NaGeVector3D V = pSurface->NormalAt(uPar, vPar);
	V.Normalize();
	if(!dirSense)
		V = V * -1.0;
	NaGePoint3D P = pSurface->PointAtPara(uPar, vPar);
	P = P+V*itsOffset;
	return P;
}

NaGeVector3D NaGeOffsetSurface::NormalAt(const double uPar, const double vPar)
{
	NaGeVector3D V = pSurface->NormalAt(uPar, vPar);
	return V;
}

double NaGeOffsetSurface::FirstUParameter() const
{
	return pSurface->FirstUParameter();
}

double NaGeOffsetSurface::LastUParameter() const
{
	return pSurface->LastUParameter();
}

double NaGeOffsetSurface::FirstVParameter() const
{
	return pSurface->FirstVParameter();
}

double NaGeOffsetSurface::LastVParameter() const
{
	return pSurface->LastVParameter();
}

bool NaGeOffsetSurface::IsUClosed() const
{
	return pSurface->IsUClosed();
}

bool NaGeOffsetSurface::IsVClosed() const
{
	return pSurface->IsVClosed();
}

SurfaceType NaGeOffsetSurface::Type() const
{
	return OFFSET;
}

bool NaGeOffsetSurface::IsOfType(const SurfaceType& O) const
{
	bool b = (O == OFFSET);
	return b;
}

NaGeSurface* NaGeOffsetSurface::Copy() const
{
	NaGeOffsetSurface* S = new NaGeOffsetSurface(*pSurface, itsOffset, dirSense);
	return S;
}

void NaGeOffsetSurface::Translate(double dx, double dy, double dz)
{
    pSurface->Translate(dx, dy, dz);
}

void NaGeOffsetSurface::Translate(const NaGeVector3D& V)
{
    pSurface->Translate(V);
}

void NaGeOffsetSurface::Translate(const NaGePoint3D& fro, const NaGePoint3D& to)
{
    pSurface->Translate(fro, to);
}

void NaGeOffsetSurface::Rotate(const NaGeOneAxis& axis, double angle)
{
    pSurface->Rotate(axis, angle);
}

void NaGeOffsetSurface::Scale(const NaGePoint3D& P, double fact)
{
    pSurface->Scale(P, fact);
}

void NaGeOffsetSurface::Mirror(const NaGePoint3D& point)
{
    pSurface->Mirror(point);
}

void NaGeOffsetSurface::Mirror(const NaGeOneAxis& axis)
{
    pSurface->Mirror(axis);
}

void NaGeOffsetSurface::Mirror(const NaGePlane& plane)
{
    pSurface->Mirror(plane);
}

