
// Torus.cpp: implementation of the NaGeTorus class.
//
//////////////////////////////////////////////////////////////////////


#include "stdafx.h"

#include "NaGeTorus.h"
#include "NaGeCircle3D.h"
#include "NaGeGeomException.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

NaGeTorus::NaGeTorus()
{
    sType = TORUS;
    itsLocation = NaGeAxisSystem(NaGePoint3D(0,0,0), NaGeVector3D(0,0,1));
    majorRadius = 10.0;
    minorRadius = 5.0;
    itsFirstUParameter = 0;
    itsLastUParameter = 2*PI;
    itsFirstVParameter = 0;
    itsLastVParameter = 2*PI;
}

NaGeTorus::NaGeTorus(const NaGeAxisSystem& Ax, const double& maj, const double& min, const double& uStart, const double& uEnd, const double& vStart, const double& vEnd) : majorRadius(maj), minorRadius(min)
{

    sType = TORUS;
    itsLocation = Ax;
    itsFirstUParameter = uStart;
    itsLastUParameter = uEnd;
    itsFirstVParameter = vStart;
    itsLastVParameter = vEnd;
    if(itsFirstUParameter < 0 || itsFirstUParameter > 2*PI)
    {
	cout << "Invalid U Range .... NaGeTorus::NaGeTorus(const NaGeAxisSystem& Ax, const double& maj, const double& min, const double& uStart, const double& uEnd, const double& vStart, const double& vEnd)\n";
	throw NaGeGeomException(InvalidRange);
    }
    if(itsLastUParameter < 0 || itsLastUParameter > 2*PI)
    {
	cout << "Invalid U Range .... NaGeTorus::NaGeTorus(const NaGeAxisSystem& Ax, const double& maj, const double& min, const double& uStart, const double& uEnd, const double& vStart, const double& vEnd)\n";
	throw NaGeGeomException(InvalidRange);
    }
    if(itsFirstVParameter < 0 || itsFirstVParameter > 2*PI)
    {
	cout << "Invalid V Range .... NaGeTorus::NaGeTorus(const NaGeAxisSystem& Ax, const double& maj, const double& min, const double& uStart, const double& uEnd, const double& vStart, const double& vEnd)\n";
	throw NaGeGeomException(InvalidRange);
    }
    if(itsLastVParameter < 0 || itsLastVParameter > 2*PI)
    {
	cout << "Invalid V Range .... NaGeTorus::NaGeTorus(const NaGeAxisSystem& Ax, const double& maj, const double& min, const double& uStart, const double& uEnd, const double& vStart, const double& vEnd)\n";
	throw NaGeGeomException(InvalidRange);
    }
    if(itsLastUParameter <  itsFirstUParameter)
    {
	cout << "Invalid Range .... NaGeTorus::NaGeTorus(const NaGeAxisSystem& Ax, const double& maj, const double& min, const double& uStart, const double& uEnd, const double& vStart, const double& vEnd)\n";
	throw NaGeGeomException(InvalidRange);
    }
    if(itsLastVParameter <  itsFirstVParameter)
    {
	cout << "Invalid Range .... NaGeTorus::NaGeTorus(const NaGeAxisSystem& Ax, const double& maj, const double& min, const double& uStart, const double& uEnd, const double& vStart, const double& vEnd)\n";
	throw NaGeGeomException(InvalidRange);
    }
}

NaGeTorus::~NaGeTorus()
{

}

NaGePoint3D NaGeTorus::PointAtPara(const double uPar, const double vPar)
{
    NaGeVector3D P, O, XDir, YDir, ZDir;
    double r = minorRadius, R = majorRadius;
    O = itsLocation.GetOrigin();
    ZDir = itsLocation.GetDirection();
    XDir = itsLocation.GetXDirection();
    YDir = itsLocation.GetYDirection();
    double cu = cos(uPar);
    double su = sin(uPar);
    double cv = cos(vPar);
    double sv = sin(vPar);
    P = O + (((XDir*cu + YDir*su) * (R + r*cv)) ) + ZDir*r*sv;
    return P.Point();
}

NaGeVector3D NaGeTorus::NormalAt(const double uPar, const double vPar)
{
    NaGeCircle3d C(itsLocation, majorRadius);
    NaGePoint3D O = C.PointAtPara(uPar);
    NaGePoint3D P = PointAtPara(uPar, vPar);
    NaGeVector3D N(O, P);
    return N;
}

bool NaGeTorus::IsUClosed() const
{
    if(itsFirstUParameter == 0 && itsLastUParameter == 2*PI)
	return true;
    return false;
}

bool NaGeTorus::IsVClosed() const
{
    if(itsFirstVParameter == 0 && itsLastVParameter == 2*PI)
	return true;
    return false;
}

NaGeSurface* NaGeTorus::Copy() const
{
    NaGeTorus* T = new NaGeTorus(itsLocation, majorRadius, minorRadius, itsFirstUParameter, itsLastUParameter, itsFirstVParameter, itsLastVParameter);
    return T;
}

void NaGeTorus::Translate(const NaGeOneAxis& Ax, const double& amt)
{
    NaGeGeometry::Translate(Ax, amt);
}

void NaGeTorus::Translate(double dx, double dy, double dz)
{
    itsLocation.Translate(dx,dy,dz);
}

void NaGeTorus::Translate(const NaGeVector3D& V)
{
    itsLocation.Translate(V);
}

void NaGeTorus::Translate(const NaGePoint3D& P1, const NaGePoint3D& P2)
{
    itsLocation.Translate(P1, P2);
}

void NaGeTorus::Rotate(const NaGeOneAxis& Ax, double ang)
{
    itsLocation.Rotate(Ax, ang);
}

void NaGeTorus::Scale(const NaGePoint3D& P, double fact)
{
    itsLocation.Scale(P, fact);
}

void NaGeTorus::Mirror(const NaGePoint3D& P)
{
    itsLocation.Mirror(P);
}

void NaGeTorus::Mirror(const NaGeOneAxis& Ax)
{
    itsLocation.Mirror(Ax);
}

void NaGeTorus::Mirror(const NaGePlane& Pln)
{
    itsLocation.Mirror(Pln);
}
