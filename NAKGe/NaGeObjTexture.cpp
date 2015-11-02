// ObjTexture.cpp: implementation of the NaGeObjTexture class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NaGeMMath.h"
#include "NaGeObjTexture.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

NaGeObjTexture::NaGeObjTexture()
{
}

NaGeObjTexture::~NaGeObjTexture()
{
}

NaGePoint3D NaGeObjTexture::PointAtPara(const double uPar, const double vPar)
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

double NaGeObjTexture::FirstUParameter() const
{
	return 0;
}

double NaGeObjTexture::LastUParameter() const
{
	return 2*PI;
}

double NaGeObjTexture::FirstVParameter() const
{
	return 0;
}

double NaGeObjTexture::LastVParameter() const
{
	return 2*PI;
}

bool NaGeObjTexture::IsUClosed() const
{
	return true;
}

bool NaGeObjTexture::IsVClosed() const
{
	return false;
}

NaGeSurface* NaGeObjTexture::Copy() const
{
	NaGeObjTexture* K = new NaGeObjTexture();
	return K;
}

void NaGeObjTexture::Translate(double dx, double dy, double dz)
{}

void NaGeObjTexture::Translate(const NaGeVector3D&)
{}

void NaGeObjTexture::Translate(const NaGePoint3D&, const NaGePoint3D&)
{}

void NaGeObjTexture::Rotate(const NaGeOneAxis&, double)
{}

void NaGeObjTexture::Scale(const NaGePoint3D&, double)
{}

void NaGeObjTexture::Mirror(const NaGePoint3D&)
{}

void NaGeObjTexture::Mirror(const NaGeOneAxis&)
{}

void NaGeObjTexture::Mirror(const NaGePlane&)
{}
