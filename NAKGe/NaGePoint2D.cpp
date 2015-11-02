// Point2D.cpp: implementation of the NaGePoint2D class.
//
//////////////////////////////////////////////////////////////////////


#include "stdafx.h"

#include "NaGePoint2D.h"
#include "NaGeVector2D.h"
#include "NaGeOneAxis2D.h"
#include "NaGeLine2D.h"
#include "NaGeMatrix22.h"
#include "NaGeMMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

NaGePoint2D::NaGePoint2D()
{
    SetParam(0,0);
    geomType = GEPOINT2D;
}

NaGePoint2D::NaGePoint2D(double x, double y)
{
    SetParam(x, y);
    geomType = GEPOINT2D;
}

NaGePoint2D::~NaGePoint2D()
{

}

void NaGePoint2D::SetParam(double x, double y)
{
    itsX=x;
    itsY=y;
}

NaGePoint2D NaGePoint2D::operator+(const NaGePoint2D &newPoint)
{
    return NaGePoint2D(itsX+newPoint.GetX(),itsY+newPoint.GetY());
}

NaGePoint2D NaGePoint2D::operator+(const double & inc)
{
    return NaGePoint2D(itsX+inc,itsY+inc);
}

NaGePoint2D NaGePoint2D::operator-(const NaGePoint2D &newPoint)
{
    return NaGePoint2D(itsX-newPoint.GetX(),itsY-newPoint.GetY());
}

NaGePoint2D NaGePoint2D::operator-(const double & dec)
{
    return NaGePoint2D(itsX-dec,itsY-dec);
}

NaGePoint2D NaGePoint2D::operator*(const double scale)
{
    return NaGePoint2D(itsX*scale,itsY*scale);
}

NaGePoint2D NaGePoint2D::operator/(const double scale)
{
    return NaGePoint2D(itsX/scale,itsY/scale);
}

void NaGePoint2D::operator+=(const NaGePoint2D& P)
{
    (*this) = (*this) + P;
}

void NaGePoint2D::operator+=(const double& inc)
{
    (*this) = (*this) + inc;
}

void NaGePoint2D::operator-=(const NaGePoint2D& P)
{
    (*this) = (*this) - P;
}

void NaGePoint2D::operator-=(const double& dec)
{
    (*this) = (*this) - dec;
}

void NaGePoint2D::operator*=(const double scale)
{
    (*this) = (*this) * scale;
}

void NaGePoint2D::operator/=(const double scale)
{
    (*this) = (*this) / scale;
}

NaGePoint2D NaGePoint2D::operator = (const NaGePoint2D& p)
{
    if(this == &p)
	return *this;
    itsX = p.itsX;
    itsY = p.itsY;
    return *this;
}

bool NaGePoint2D::operator == (const NaGePoint2D& p) const
{
    return (itsX==p.GetX() && itsY==p.GetY());
}

ORIENTATION NaGePoint2D::Orientation(const NaGePoint2D& P1, const NaGePoint2D& P2)
{
    NaGePoint2D tmp1 = P1, tmp2 = P2;
    NaGePoint2D a = tmp2 - *this;
    NaGePoint2D b = tmp1 - *this;
    double sa = a.GetX() * b.GetY() - b.GetX() * a.GetY();
    if(sa > 0.0)
	return ORIENTED_CCW;
    if(sa < 0.0)
	return ORIENTED_CW;
    
    return ORIENTED_COLLINEAR;
}

CLASSIFICATION NaGePoint2D::Classification(const NaGePoint2D& P1, const NaGePoint2D& P2)
{
    NaGePoint2D p0 = P1, p1 = P2;
    NaGePoint2D p2 = *this;
    NaGePoint2D a = p1 - p0;
    NaGePoint2D b = p2 - p0;
    double sa = a.GetX() * b.GetY() - b.GetX() * a.GetY();
    if(sa > 0.0)
	return CLASSIFIED_LEFT;
    if(sa < 0.0)
	return CLASSIFIED_RIGHT;
    if((a.GetX() * b.GetX() < 0.0) || (a.GetY() * b.GetY() < 0.0))
	return CLASSIFIED_BEHIND;
    if(a.Distance(NaGePoint2D(0,0)) < b.Distance(NaGePoint2D(0,0)))
	return CLASSIFIED_BEYOND;
    if(p0 == p2)
	return CLASSIFIED_ORIGIN;
    if(p1 == p2)
	return CLASSIFIED_DESTINATION;
    return CLASSIFIED_BETWEEN;
}

NaGePoint2D::operator NaGeVector2D()
{
    NaGeVector2D V((*this));
    return V;
}


double NaGePoint2D::Distance(const NaGePoint2D& P)
{

    double sqad, root;
    double x,y,tx,ty;
    x=P.GetX(); y=P.GetY();
    tx = fabs(this->GetX()-x);
    ty = fabs(this->GetY()-y);
    sqad=((pow(tx,2))+(pow(ty,2)));
    root=sqrt(sqad);

    return root;
}

double NaGePoint2D::PolarAngle(const NaGePoint2D& P) const
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

void NaGePoint2D::Translate(const NaGeOneAxis2D& Ax, const double& amt)
{
    NaGeGeometry2D::Translate(Ax, amt);
}

void NaGePoint2D::Translate(double dx, double dy)
{
    itsX+=dx;
    itsY+=dy;
}

void NaGePoint2D::Translate(const NaGeVector2D& VDir)
{
    NaGeVector2D V = VDir;
    itsX+=V.GetX();
    itsY+=V.GetY();
}

void NaGePoint2D::Translate(const NaGePoint2D& P1, const NaGePoint2D& P2)
{
    NaGeVector2D V(P1, P2);
    Translate(V);
}

void NaGePoint2D::Rotate(const NaGePoint2D& Pt, double ang)
{
    NaGePoint2D P1 = Pt;
    NaGeMatrix22 M;
    M.SetRotation(ang);
    NaGePoint2D tp = *this - P1;
    NaGeVector2D V = M * NaGeVector2D(tp);
    V += NaGeVector2D(P1);
    *this = V.Point();
}

void NaGePoint2D::Scale(const NaGePoint2D& P, double fact)
{	
    NaGePoint2D p = P;
    p = p * (1.0 - fact);
    (*this) = (*this)*(fact);
    (*this) = (*this) + p;
}

void NaGePoint2D::Mirror(const NaGePoint2D& P)
{
    NaGePoint2D p = P;
    (*this) *= -1;
    p *= (2.0);
    (*this) += p;
}

void NaGePoint2D::Mirror(const NaGeOneAxis2D& Ax)
{
    NaGePoint2D P1 = Ax.GetPosition();
    NaGePoint2D P = (*this);
    NaGeVector2D N = Ax.GetDirection();
    NaGeLine2D L(P1, N);
    double D = L.Distance(P);
    NaGeVector2D Q = L.NormalThrough(P) * D * (-2.0);
    NaGeVector2D PV((*this));
    NaGeVector2D R = PV + Q;
    this->SetParam(R.GetX(), R.GetY());
}

NaGePoint2D NaGePoint2D::Origin()
{
    return  NaGePoint2D(0,0);
}

std::istream &operator>>(std::istream& input, NaGePoint2D &p)
{
    input>>p.itsX>>p.itsY;
    return input;
}

std::ostream &operator<<(std::ostream& output, NaGePoint2D &p)
{
    output<<p.itsX<<p.itsY;
    return output;
}
