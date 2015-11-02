// Cylinder.cpp: implementation of the NaGeCylinder class.
//
//////////////////////////////////////////////////////////////////////


#include "stdafx.h"

#include "NaGeCylinder.h"
#include "NaGeCircle3D.h"
#include "NaGeAxisSystem.h"
#include "NaGeMMath.h"
#include "NaGeGeomException.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

NaGeCylinder::NaGeCylinder(const NaGeCircle3d& C, const double& ht) : itsHeight(ht)
{
    sType = CYLINDER;
    itsLocation = C.GetLocation();
    itsRadius = C.GetRadius();
    itsFirstUParameter = 0;
    itsLastUParameter = 2*PI;
    itsFirstVParameter = 0;
    itsLastVParameter = itsHeight;
}

NaGeCylinder::NaGeCylinder(const NaGeAxisSystem& Ax, const double& ht, const double& rad, const double& uStart, const double& uEnd) : itsHeight(ht), itsRadius(rad)
{
    itsLocation = Ax;
    itsFirstUParameter = uStart;
    itsLastUParameter = uEnd;
    itsFirstVParameter = 0;
    itsLastVParameter = itsHeight;
    if(itsFirstUParameter < 0 || itsFirstUParameter > 2*PI)
    {
	cout << "Invalid Range .... NaGeCylinder::NaGeCylinder(const NaGeAxisSystem& Ax, const double& ht, const double& rad, const double& uStart, const double& uEnd)\n";
	throw NaGeGeomException(InvalidRange);
    }
    if(itsLastUParameter < 0 || itsLastUParameter > 2*PI)
    {
	cout << "Invalid Range .... NaGeCylinder::NaGeCylinder(const NaGeAxisSystem& Ax, const double& ht, const double& rad, const double& uStart, const double& uEnd)\n";
	throw NaGeGeomException(InvalidRange);
    }
    if(itsLastUParameter <  itsFirstUParameter)
    {
	cout << "Invalid Range .... NaGeCylinder::NaGeCylinder(const NaGeAxisSystem& Ax, const double& ht, const double& rad, const double& uStart, const double& uEnd)\n";
	throw NaGeGeomException(InvalidRange);
    }
}

NaGeCylinder::~NaGeCylinder()
{

}

NaGePoint3D NaGeCylinder::PointAtPara(const double uPar, const double vPar)
{
    NaGeVector3D P, O, XDir, YDir, ZDir;
    O = itsLocation.GetOrigin();
    ZDir = itsLocation.GetDirection();
    XDir = itsLocation.GetXDirection();
    YDir = itsLocation.GetYDirection();
    double cu = cos(uPar);
    double su = sin(uPar);
    P = O + (XDir*cu + YDir*su)*itsRadius + ZDir*vPar;
    return P.Point();
}

bool NaGeCylinder::IsUClosed() const
{
    if(itsFirstUParameter == 0 && itsLastUParameter == 2*PI)
	return true;
    return false;
}

bool NaGeCylinder::IsVClosed() const
{
    return false;
}

NaGeSurface* NaGeCylinder::Copy() const
{
    NaGeCylinder* R = new NaGeCylinder(itsLocation, itsHeight, itsRadius, itsFirstUParameter, itsLastUParameter);
    return R;
}

void NaGeCylinder::Translate(const NaGeOneAxis& Ax, const double& amt)
{
    NaGeGeometry::Translate(Ax, amt);
}

void NaGeCylinder::Translate(double dx, double dy, double dz)
{
    itsLocation.Translate(dx,dy,dz);
}

void NaGeCylinder::Translate(const NaGeVector3D& V)
{
    itsLocation.Translate(V);
}

void NaGeCylinder::Translate(const NaGePoint3D& P1, const NaGePoint3D& P2)
{
    itsLocation.Translate(P1, P2);
}

void NaGeCylinder::Rotate(const NaGeOneAxis& Ax, double ang)
{
    itsLocation.Rotate(Ax, ang);
}

void NaGeCylinder::Scale(const NaGePoint3D& P, double fact)
{
    itsLocation.Scale(P, fact);
}

void NaGeCylinder::Mirror(const NaGePoint3D& P)
{
    itsLocation.Mirror(P);
}

void NaGeCylinder::Mirror(const NaGeOneAxis& Ax)
{
    itsLocation.Mirror(Ax);
}

void NaGeCylinder::Mirror(const NaGePlane& Pln)
{
    itsLocation.Mirror(Pln);
}
