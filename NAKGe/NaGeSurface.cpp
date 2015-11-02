// Surface.cpp: implementation of the NaGeSurface class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "NaGeSurface.h"
#include "NaGeMMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

NaGeSurface::NaGeSurface()
{
	geomType = GESURFACE;
}

NaGeSurface::~NaGeSurface()
{

}

SurfaceType NaGeSurface::Type() const
{
	return sType;
}

NaGeVector3D NaGeSurface::NormalAt(const double uPar, const double vPar)
{
	NaGePoint3D Po = PointAtPara(uPar, vPar);
	NaGePoint3D Pu = PointAtPara(uPar+0.000001, vPar);
	NaGePoint3D Pv = PointAtPara(uPar+0.000001, vPar+0.000001);
	NaGeVector3D Vu(Po, Pu);
	NaGeVector3D Vv(Po, Pv);
	NaGeVector3D N = Vu^Vv;
	N.Normalize();
	return N;
}

bool NaGeSurface::IsOfType(const SurfaceType& type) const
{
	SurfaceType typ = type;
	bool b = (sType == typ);
	return b;
}
