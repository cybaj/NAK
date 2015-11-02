// Sphere.cpp: implementation of the NaGeSphere class.
//
//////////////////////////////////////////////////////////////////////


#include "stdafx.h"

#include "NaGeSphere.h"
#include "NaGeGeomException.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//
NaGeSphere::NaGeSphere()
{
    sType = SPHERE;
    itsLocation = NaGeAxisSystem(NaGePoint3D(0,0,0), NaGeVector3D(0,0,1));
    itsRadius = 10.0;
    itsFirstUParameter = 0;
    itsLastUParameter = 2*PI;
    itsFirstVParameter = -PI/2;
    itsLastVParameter = PI/2;
}

NaGeSphere::NaGeSphere(const NaGeAxisSystem& Ax, const double& rad, const double& uStart, const double& uEnd, const double& vStart, const double& vEnd) : itsRadius(rad)
{
    sType = SPHERE;
    itsLocation = Ax;
    itsFirstUParameter = uStart;
    itsLastUParameter = uEnd;
    itsFirstVParameter = vStart;
    itsLastVParameter = vEnd;
    if(itsFirstUParameter < 0 || itsFirstUParameter > 2*PI)
    {
	cout << "Invalid U Range .... NaGeSphere::NaGeSphere(const NaGeAxisSystem& Ax, const double& rad, const double& uStart, const double& uEnd, const double& vStart, const double& vEnd)\n";
	throw NaGeGeomException(InvalidRange);
    }
    if(itsLastUParameter < 0 || itsLastUParameter > 2*PI)
    {
	cout << "Invalid U Range .... NaGeSphere::NaGeSphere(const NaGeAxisSystem& Ax, const double& rad, const double& uStart, const double& uEnd, const double& vStart, const double& vEnd)\n";
	throw NaGeGeomException(InvalidRange);
    }
    if(itsFirstVParameter < -PI/2 || itsFirstVParameter > PI/2)
    {
	cout << "Invalid V Range .... NaGeSphere::NaGeSphere(const NaGeAxisSystem& Ax, const double& rad, const double& uStart, const double& uEnd, const double& vStart, const double& vEnd)\n";
	throw NaGeGeomException(InvalidRange);
    }
    if(itsLastVParameter < -PI/2 || itsLastVParameter > PI/2)
    {
	cout << "Invalid V Range .... NaGeSphere::NaGeSphere(const NaGeAxisSystem& Ax, const double& rad, const double& uStart, const double& uEnd, const double& vStart, const double& vEnd)\n";
	throw NaGeGeomException(InvalidRange);
    }
    if(itsLastUParameter <  itsFirstUParameter)
    {
	cout << "Invalid Range .... NaGeSphere::NaGeSphere(const NaGeAxisSystem& Ax, const double& rad, const double& uStart, const double& uEnd, const double& vStart, const double& vEnd)\n";
	throw NaGeGeomException(InvalidRange);
    }
    if(itsLastVParameter <  itsFirstVParameter)
    {
	cout << "Invalid Range .... NaGeSphere::NaGeSphere(const NaGeAxisSystem& Ax, const double& rad, const double& uStart, const double& uEnd, const double& vStart, const double& vEnd)\n";
	throw NaGeGeomException(InvalidRange);
    }
}

NaGeSphere::~NaGeSphere()
{

}

NaGePoint3D NaGeSphere::PointAtPara(const double uPar, const double vPar)
{
    NaGeVector3D P, O, XDir, YDir, ZDir;
    O = itsLocation.GetOrigin();
    ZDir = itsLocation.GetDirection();
    XDir = itsLocation.GetXDirection();
    YDir = itsLocation.GetYDirection();
    double cu = cos(uPar);
    double su = sin(uPar);
    double cv = cos(vPar);
    double sv = sin(vPar);
    P = O + (XDir*cu + YDir*su)*itsRadius*cv + ZDir*itsRadius*sv;
    return P.Point();
}

NaGeVector3D NaGeSphere::NormalAt(const double uPar, const double vPar)
{
    NaGePoint3D O = itsLocation.GetPosition();
    NaGePoint3D P = PointAtPara(uPar, vPar);
    NaGeVector3D N(O, P);
    N.Normalize();
    return N;
}

bool NaGeSphere::IsUClosed() const
{
    if(itsFirstUParameter == 0 && itsLastUParameter == 2*PI)
	return true;
    return false;
}

bool NaGeSphere::IsVClosed() const
{
    if(itsFirstVParameter == -PI/2 && itsLastVParameter == PI/2)
	return true;
    return false;
}

NaGeSurface* NaGeSphere::Copy() const
{
    NaGeSphere* S = new NaGeSphere(itsLocation, itsRadius, itsFirstUParameter, itsLastUParameter, itsFirstVParameter, itsLastVParameter);
    return S;
}

void NaGeSphere::Translate(const NaGeOneAxis& Ax, const double& amt)
{
    NaGeGeometry::Translate(Ax, amt);
}

void NaGeSphere::Translate(double dx, double dy, double dz)
{
    itsLocation.Translate(dx,dy,dz);
}

void NaGeSphere::Translate(const NaGeVector3D& V)
{
    itsLocation.Translate(V);
}

void NaGeSphere::Translate(const NaGePoint3D& P1, const NaGePoint3D& P2)
{
    itsLocation.Translate(P1, P2);
}

void NaGeSphere::Rotate(const NaGeOneAxis& Ax, double ang)
{
    itsLocation.Rotate(Ax, ang);
}

void NaGeSphere::Scale(const NaGePoint3D& P, double fact)
{
    itsLocation.Scale(P, fact);
}

void NaGeSphere::Mirror(const NaGePoint3D& P)
{
    itsLocation.Mirror(P);
}

void NaGeSphere::Mirror(const NaGeOneAxis& Ax)
{
    itsLocation.Mirror(Ax);
}

void NaGeSphere::Mirror(const NaGePlane& Pln)
{
    itsLocation.Mirror(Pln);
}

