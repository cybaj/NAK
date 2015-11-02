// Circle3D.cpp: implementation of the NaGeCircle3d class.
//
//////////////////////////////////////////////////////////////////////


#include "stdafx.h"

#include "NaGeCircle3D.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

NaGeCircle3d::NaGeCircle3d()
{
    cType = CIRCLE;
}

NaGeCircle3d::NaGeCircle3d(const NaGePoint3D& cp, const double rad) : itsRadius(rad)
{
    NaGeAxisSystem ax(cp, NaGeVector3D(0,0,1), NaGeVector3D(1,0,0));
    itsLocation = ax;
    cType = CIRCLE;
}

NaGeCircle3d::NaGeCircle3d(const NaGeAxisSystem& ax, const double rad) : itsRadius(rad)
{
    itsLocation = ax;
    cType = CIRCLE;
}

NaGeCircle3d::NaGeCircle3d(const NaGePoint3D& P1, const NaGePoint3D& P2, const NaGePoint3D& P3)
{
    NaGePoint3D p1=P1, p2=P2, p3=P3;
    double x1, x2, x3, y1, y2, y3, z1, z2, z3;
    x1 = p1.GetX(); y1 = p1.GetY(); z1 = p1.GetZ();
    x2 = p2.GetX(); y2 = p2.GetY(); z2 = p2.GetZ();
    x3 = p3.GetX(); y3 = p3.GetY(); z3 = p3.GetZ();

    NaGeVector3D pv1(p1);
    NaGeVector3D pv2(p2);
    NaGeVector3D pv3(p3);

    NaGeVector3D n1(pv1, pv2); 
    NaGeVector3D n2(pv2, pv3);
    NaGeVector3D n3(pv3, pv1);

    double Row1[3]={n1.GetX(), n1.GetY(), n1.GetZ()};
    double Row2[3]={n2.GetX(), n2.GetY(), n2.GetZ()};
    double Row3[3]={n3.GetX(), n3.GetY(), n3.GetZ()};

    double b1, b2, b3;
    b1 = ((p1.Distance(p2))/2) + (x1*n1.GetX() + y1*n1.GetY() + z1*n1.GetZ());
    b2 = ((p2.Distance(p3))/2) + (x2*n2.GetX() + y2*n2.GetY() + z2*n2.GetZ());
    b3 = ((p3.Distance(p1))/2) + (x3*n3.GetX() + y3*n3.GetY() + z3*n3.GetZ());

    NaGeVector3D b(b1, b2, b3);
    NaGeMatrix33 M(Row1, Row2, Row3);

    M.Invert();

    NaGeVector3D cen = M*b;
    NaGeVector3D dir = n1.Crossed(n2);
    NaGeVector3D xdir = dir.Crossed(n1);

    NaGeAxisSystem ax(NaGePoint3D(cen.GetX(), cen.GetY(), cen.GetZ()), 
	    dir, xdir);
    itsLocation = ax;

    itsRadius = p1.Distance(cen.Point());

    cType = CIRCLE;
}

NaGeCircle3d::NaGeCircle3d(const NaGeCircle3d& C) : NaGeConic()
{
    cType = CIRCLE;
    itsLocation = C.itsLocation;
    itsRadius = C.itsRadius;
}

NaGeCircle3d::~NaGeCircle3d()
{

}

void NaGeCircle3d::Reverse()
{
    cReversed = !cReversed;
}

NaGeCircle3d NaGeCircle3d::Reversed() const
{
    NaGeCircle3d C = (*this);
    C.Reverse();
    return C;
}

NaGePoint3D NaGeCircle3d::PointAtPara(const double& Par)
{
    NaGePoint3D P; NaGeVector3D V;
    double para = Par;

    if(cReversed)
	para = 2*PI - para;

    double c = cos(para);
    double s = sin(para);
    V = itsLocation.GetOrigin()+(itsLocation.GetXDirection()*c+itsLocation.GetYDirection()*s)
	*GetRadius();
    P.SetParam(V.GetX(), V.GetY(), V.GetZ());

    return P;
}

bool NaGeCircle3d::IsClosed() const
{
    return true;
}

bool NaGeCircle3d::operator == (const NaGeCircle3d& C) const
{
    bool eq = (itsLocation == C.GetLocation() && itsRadius == C.GetRadius());
    return eq;
}

NaGeCircle3d NaGeCircle3d::operator = (const NaGeCircle3d& C)
{
    if(this == &C)
	return *this;
    cType = CIRCLE;
    itsLocation = C.GetLocation();
    itsRadius = C.GetRadius();
    return *this;
}

void NaGeCircle3d::Translate(double dx, double dy, double dz)
{
    itsLocation.Translate(dx,dy,dz);
}

NaGeCurve* NaGeCircle3d::Copy() const
{
    NaGeCircle3d* C = new NaGeCircle3d(itsLocation, itsRadius);
    return C;
}

void NaGeCircle3d::Translate(const NaGeOneAxis& Ax, const double& amt)
{
    NaGeGeometry::Translate(Ax, amt);
}

void NaGeCircle3d::Translate(const NaGeVector3D& V)
{
    itsLocation.Translate(V);
}

void NaGeCircle3d::Translate(const NaGePoint3D& P1, const NaGePoint3D& P2)
{
    itsLocation.Translate(P1, P2);
}

void NaGeCircle3d::Rotate(const NaGeOneAxis& Ax, double fact)
{
    itsLocation.Rotate(Ax, fact);
}

void NaGeCircle3d::Scale(const NaGePoint3D& P, double fact)
{
    itsLocation.Scale(P, fact);
    itsRadius *= fact;
    if(itsRadius < 0)
	itsRadius = -itsRadius;
}

void NaGeCircle3d::Mirror(const NaGePoint3D& P)
{
    itsLocation.Mirror(P);
}

void NaGeCircle3d::Mirror(const NaGeOneAxis& Ax)
{
    itsLocation.Mirror(Ax);
}

void NaGeCircle3d::Mirror(const NaGePlane& Pln)
{
    itsLocation.Mirror(Pln);
}
