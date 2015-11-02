// Point3D.cpp: implementation of the NaGePoint3D class.
//
//////////////////////////////////////////////////////////////////////


#include "stdafx.h"

#include "NaGePoint3D.h"
#include "NaGeVector3D.h"
#include "NaGeOneAxis.h"
#include "NaGeLine3D.h"
#include "NaGePlane.h"
#include "NaGeMatrix33.h"
#include "NaGeMMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

NaGePoint3D::NaGePoint3D()
{
    SetParam(0,0,0);
    geomType = GEPOINT;
}

NaGePoint3D::NaGePoint3D(double x, double y, double z)
{
    SetParam(x, y, z);
    geomType = GEPOINT;
}

NaGePoint3D::~NaGePoint3D()
{

}

void NaGePoint3D::SetParam(double x, double y, double z)
{
    itsX=x;
    itsY=y;
    itsZ=z;
}

NaGePoint3D NaGePoint3D::operator+(const NaGePoint3D &newPoint)
{
    return NaGePoint3D(itsX+newPoint.GetX(),itsY+newPoint.GetY(),itsZ+newPoint.GetZ());
}

NaGePoint3D NaGePoint3D::operator+(const double & inc)
{
    return NaGePoint3D(itsX+inc,itsY+inc,itsZ+inc);
}

NaGePoint3D NaGePoint3D::operator-(const NaGePoint3D &newPoint)
{
    return NaGePoint3D(itsX-newPoint.GetX(),itsY-newPoint.GetY(),itsZ-newPoint.GetZ());
}

NaGePoint3D NaGePoint3D::operator-(const double & dec)
{
    return NaGePoint3D(itsX-dec,itsY-dec,itsZ-dec);
}

NaGePoint3D NaGePoint3D::operator*(const double scale)
{
    return NaGePoint3D(itsX*scale,itsY*scale,itsZ*scale);
}

NaGePoint3D NaGePoint3D::operator/(const double scale)
{
    return NaGePoint3D(itsX/scale,itsY/scale,itsZ/scale);
}

void NaGePoint3D::operator+=(const NaGePoint3D& P)
{
    (*this) = (*this) + P;
}

void NaGePoint3D::operator+=(const double& inc)
{
    (*this) = (*this) + inc;
}

void NaGePoint3D::operator-=(const NaGePoint3D& P)
{
    (*this) = (*this) - P;
}

void NaGePoint3D::operator-=(const double& dec)
{
    (*this) = (*this) - dec;
}

void NaGePoint3D::operator*=(const double scale)
{
    (*this) = (*this) * scale;
}

void NaGePoint3D::operator/=(const double scale)
{
    (*this) = (*this) / scale;
}

NaGePoint3D NaGePoint3D::operator = (const NaGePoint3D& p)
{
    if(this == &p)
	return *this;
    itsX = p.itsX;
    itsY = p.itsY;
    itsZ = p.itsZ;
    return *this;
}

bool NaGePoint3D::operator == (const NaGePoint3D& p) const
{
    return (itsX==p.GetX() && itsY==p.GetY() && itsZ==p.GetZ());
}

NaGePoint3D::operator NaGeVector3D()
{
    NaGeVector3D V((*this));
    return V;
}

double NaGePoint3D::Distance(const NaGePoint3D& P) const
{

    double sqad, root;
    double x,y,z,tx,ty,tz;
    x=P.GetX(); y=P.GetY(); z=P.GetZ();
    tx = fabs(this->GetX()-x);
    ty = fabs(this->GetY()-y);
    tz = fabs(this->GetZ()-z);
    sqad=((pow(tx,2))+(pow(ty,2))+(pow(tz,2)));
    root=sqrt(sqad);

    return root;
}

double NaGePoint3D::Distance(const NaGePlane& P) const
{

    NaGePoint3D p = P.GetPosition();
    NaGePoint3D dp = (*this);
    NaGeVector3D V1 = P.GetDirection();
    NaGeVector3D V2(dp);
    double D = V1.Dot(V2) + P.GetConstant();
    return D;
}

double NaGePoint3D::PolarAngle(const NaGePoint3D& P) const
{
    double x = itsX - P.GetX();
    double y = itsY - P.GetY();
    if((x == 0.0) && (y == 0.0))
	return -1;
    if(x == 0.0)
	return ((y > 0.0) ? 90 : 270);
    double theta = atan(y / x);
    theta *= 360.0 / (2 * PI);
    if(x > 0.0)
	return ((y >= 0.0) ? theta : 360 + theta);
    else
	return (180.0 + theta);
}

void NaGePoint3D::Translate(const NaGeOneAxis& Ax, const double& amt)
{
    NaGeGeometry::Translate(Ax, amt);
}

void NaGePoint3D::Translate(double dx, double dy, double dz)
{
    itsX+=dx;
    itsY+=dy;
    itsZ+=dz;
}

void NaGePoint3D::Translate(const NaGeVector3D& VDir)
{
    NaGeVector3D V = VDir;
    itsX+=V.GetX();
    itsY+=V.GetY();
    itsZ+=V.GetZ();
}

void NaGePoint3D::Translate(const NaGePoint3D& P1, const NaGePoint3D& P2)
{
    NaGeVector3D V(P1, P2);
    Translate(V);
}

void NaGePoint3D::Rotate(const NaGeOneAxis& Ax, double ang)
{
    NaGeOneAxis ax = Ax;
    NaGeVector3D P1 = ax.GetOrigin();
    NaGeVector3D V = ax.GetDirection();
    V.Normalize();
    NaGeMatrix33 M; NaGeVector3D PV(*this);
    M.SetRotation(V, ang);
    NaGeVector3D RV = M*(PV-P1);
    RV = RV + P1;
    *this = RV.Point();
}

void NaGePoint3D::Scale(const NaGePoint3D& P, double fact)
{	
    NaGePoint3D p = P;
    p = p * (1.0 - fact);
    (*this) = (*this)*(fact);
    (*this) = (*this) + p;
}

void NaGePoint3D::Mirror(const NaGePoint3D& P)
{
    NaGePoint3D p = P;
    (*this) *= -1;
    p *= (2.0);
    (*this) += p;
}

void NaGePoint3D::Mirror(const NaGeOneAxis& Ax)
{
    NaGePoint3D P1 = Ax.GetPosition();
    NaGePoint3D P = (*this);
    NaGeVector3D N = Ax.GetDirection();
    NaGeLine3D L(P1, N);
    double D = L.Distance(P);
    NaGeVector3D Q = L.NormalThrough(P) * D * (-2.0);
    NaGeVector3D PV((*this));
    NaGeVector3D R = PV + Q;
    this->SetParam(R.GetX(), R.GetY(), R.GetZ());
}

void NaGePoint3D::Mirror(const NaGePlane& Pln)
{
    NaGePlane pln = Pln;
    NaGePoint3D P = (*this);
    double D = P.Distance(pln);
    NaGeVector3D N = pln.GetDirection().Unit();
    NaGeVector3D Q = N * D * (-2.0);
    NaGePoint3D QP = Q.Point();
    (*this) = P + QP;
}

NaGePoint3D NaGePoint3D::Origin()
{
    return  NaGePoint3D(0,0,0);
}

std::istream &operator>>(std::istream& input, NaGePoint3D &p)
{
    input>>p.itsX>>p.itsY>>p.itsZ;
    return input;
}

std::ostream &operator<<(std::ostream& output, NaGePoint3D &p)
{
    output<< p.itsX << " " << p.itsY << " " << p.itsZ;
    return output;
}
