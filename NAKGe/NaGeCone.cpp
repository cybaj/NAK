// Cone.cpp: implementation of the NaGeCone class.
//
//////////////////////////////////////////////////////////////////////



#include "stdafx.h"

#include "NaGeCone.h"
#include "NaGeCircle3D.h"
#include "NaGeMMath.h"
#include "NaGeGeomException.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

NaGeCone::NaGeCone(const NaGeCircle3d& C, const double& ht) : itsHeight(ht)
{
    sType = CONE;
    itsLocation = C.GetLocation();
    baseRadius = C.GetRadius();
    topRadius = 0;
    itsFirstUParameter = 0;
    itsLastUParameter = 2*PI;
    itsFirstVParameter = 0;
    itsLastVParameter = itsHeight;
}

NaGeCone::NaGeCone(const NaGeAxisSystem& Ax, const double& ht, const double& rad1, const double& rad2, const double& uStart, const double& uEnd) : itsHeight(ht), baseRadius(rad1), topRadius(rad2)
{
    sType = CONE;
    itsLocation = Ax;
    itsFirstUParameter = uStart;
    itsLastUParameter = uEnd;
    itsFirstVParameter = 0;
    itsLastVParameter = itsHeight;
    if(itsFirstUParameter < 0 || itsFirstUParameter > 2*PI)
    {
	cout << "Invalid Range .... NaGeCone::NaGeCone(const NaGeAxisSystem& Ax, const double& ht, const double& rad1, const double& rad2, const double& uStart, const double& uEnd)\n";
	throw NaGeGeomException(InvalidRange);
    }
    if(itsLastUParameter < 0 || itsLastUParameter > 2*PI)
    {
	cout << "Invalid Range .... NaGeCone::NaGeCone(const NaGeAxisSystem& Ax, const double& ht, const double& rad1, const double& rad2, const double& uStart, const double& uEnd)\n";
	throw NaGeGeomException(InvalidRange);
    }
    if(itsLastUParameter <  itsFirstUParameter)
    {
	cout << "Invalid Range .... NaGeCone::NaGeCone(const NaGeAxisSystem& Ax, const double& ht, const double& rad1, const double& rad2, const double& uStart, const double& uEnd)\n";
	throw NaGeGeomException(InvalidRange);
    }
}

NaGeCone::~NaGeCone()
{

}

NaGePoint3D NaGeCone::PointAtPara(const double uPar, const double vPar)
{
    NaGeVector3D P, O, XDir, YDir, ZDir;
    double Ang = atan((baseRadius-topRadius)/itsHeight);
    O = itsLocation.GetOrigin();
    ZDir = itsLocation.GetDirection();
    XDir = itsLocation.GetXDirection();
    YDir = itsLocation.GetYDirection();
    double cu = cos(uPar);
    double su = sin(uPar);
    P = O + (((XDir*cu + YDir*su) * (baseRadius - vPar*tan(Ang))) ) + ZDir*vPar;
    return P.Point();
}

bool NaGeCone::IsUClosed() const
{
    if(itsFirstUParameter == 0 && itsLastUParameter == 2*PI)
	return true;
    return false;
}

bool NaGeCone::IsVClosed() const
{
    return false;
}

NaGeSurface* NaGeCone::Copy() const
{
    NaGeCone* R = new NaGeCone(itsLocation, itsHeight, baseRadius, topRadius, itsFirstUParameter, itsLastUParameter);;
    return R;
}

void NaGeCone::Translate(const NaGeOneAxis& Ax, const double& amt)
{
    NaGeGeometry::Translate(Ax, amt);
}

void NaGeCone::Translate(double dx, double dy, double dz)
{
    itsLocation.Translate(dx,dy,dz);
}

void NaGeCone::Translate(const NaGeVector3D& V)
{
    itsLocation.Translate(V);
}

void NaGeCone::Translate(const NaGePoint3D& P1, const NaGePoint3D& P2)
{
    itsLocation.Translate(P1, P2);
}

void NaGeCone::Rotate(const NaGeOneAxis& Ax, double ang)
{
    itsLocation.Rotate(Ax, ang);
}

void NaGeCone::Scale(const NaGePoint3D& P, double fact)
{
    itsLocation.Scale(P, fact);
}

void NaGeCone::Mirror(const NaGePoint3D& P)
{
    itsLocation.Mirror(P);
}

void NaGeCone::Mirror(const NaGeOneAxis& Ax)
{
    itsLocation.Mirror(Ax);
}

void NaGeCone::Mirror(const NaGePlane& Pln)
{
    itsLocation.Mirror(Pln);
}
