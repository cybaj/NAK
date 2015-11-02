// Vector2D.cpp: implementation of the NaGeVector2D class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "NaGeVector2D.h"
#include "NaGePoint2D.h"
#include "NaGeMatrix22.h"
#include "NaGeOneAxis2D.h"
#include "NaGeMMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//Implementation of class vector
NaGeVector2D::NaGeVector2D()
{
    itsX = 0;
    itsY = 0;
}

NaGeVector2D::NaGeVector2D(double x, double y)
{
    itsX = x;
    itsY = y;
}

NaGeVector2D::NaGeVector2D(const NaGePoint2D& P)
{
    itsX = P.GetX();
    itsY = P.GetY();
}

NaGeVector2D::NaGeVector2D(const NaGeVector2D &V1, const NaGeVector2D &V2)
{
    NaGeVector2D VC1, VC2, VC3;
    VC1 = V1;
    VC2 = V2;
    VC3 = VC2-VC1;
    itsX = VC3.GetX();
    itsY = VC3.GetY();
}

NaGeVector2D::NaGeVector2D(const NaGePoint2D &V1, const NaGePoint2D &V2)
{
    NaGePoint2D VC1, VC2;
    VC1 = V1;
    VC2 = V2;
    itsX = VC2.GetX()-VC1.GetX();
    itsY = VC2.GetY()-VC1.GetY();
}

NaGeVector2D::~NaGeVector2D()
{
}

double NaGeVector2D::Dot(const NaGeVector2D &V1) const
{
    double result;
    result = V1.GetX()*GetX()+V1.GetY()*GetY();
    return result;
}

double NaGeVector2D::DotCross(const NaGeVector2D &V1, const NaGeVector2D &V2)
{
    NaGeVector2D A = (*this), B = V1, C = V2;
    NaGeVector2D cross = B.Crossed(C);
    double Res = A.Dot(cross);
    return Res;
}

void NaGeVector2D::Cross(const NaGeVector2D& V1)
{
    SetX(GetY()-V1.GetY());
    SetY(V1.GetX()-GetX());
}

NaGeVector2D NaGeVector2D::Crossed(const NaGeVector2D& V1) const
{
    NaGeVector2D result;
    result.SetX(GetY()-V1.GetY());
    result.SetY(V1.GetX()-GetX());
    return result;
}

void NaGeVector2D::CrossCross(const NaGeVector2D &V1, const NaGeVector2D &V2)
{
    NaGeVector2D A = (*this), B = V1, C = V2;
    NaGeVector2D Res = B*((C.Dot(A))) - C*(A.Dot(B));
    (*this) = Res;
}

NaGeVector2D NaGeVector2D::CrossCrossed(const NaGeVector2D &V1, const NaGeVector2D &V2)
{
    NaGeVector2D V = (*this);
    V.CrossCross(V1, V2);
    return V;
}

void NaGeVector2D::Reverse()
{
    this->SetX(-GetX());
    this->SetY(-GetY());
}

NaGeVector2D NaGeVector2D::Reversed()
{
    NaGeVector2D result;
    result.Reverse();
    return result;
}

NaGeVector2D NaGeVector2D::operator + (const NaGeVector2D &V1)
{
    NaGeVector2D result;
    result.SetX(GetX()+V1.GetX());
    result.SetY(GetY()+V1.GetY());
    return result;
}

void NaGeVector2D::operator += (const NaGeVector2D &V1)
{
    SetX(GetX()+V1.GetX());
    SetY(GetY()+V1.GetY());
}

NaGeVector2D NaGeVector2D::operator - (const NaGeVector2D &V1)
{
    NaGeVector2D result;
    result.SetX(GetX()-V1.GetX());
    result.SetY(GetY()-V1.GetY());
    return result;
}

void NaGeVector2D::operator -= (const NaGeVector2D &V1)
{
    SetX(GetX()-V1.GetX());
    SetY(GetY()-V1.GetY());
}

NaGeVector2D NaGeVector2D::operator * (const double &scalar)
{
    NaGeVector2D result;
    result.SetX(GetX()*scalar);
    result.SetY(GetY()*scalar);
    return result;
}

NaGeVector2D NaGeVector2D::operator * (const NaGeMatrix22 &M)
{
   NaGeVector2D V;
   V.SetX(M(0,0)*GetX()+M(0,1)*GetY());
   V.SetY(M(1,0)*GetX()+M(1,1)*GetY());
   return V;
}


void NaGeVector2D::operator *= (const double &scalar)
{
    SetX(GetX()*scalar);
    SetY(GetY()*scalar);
}


void NaGeVector2D::operator *= (const NaGeMatrix22 &M)
{
   SetX(M(0,0)*GetX()+M(0,1)*GetY());
   SetY(M(1,0)*GetX()+M(1,1)*GetY());
}

NaGeVector2D NaGeVector2D::operator / (const double &scalar)
{
    NaGeVector2D result;
    if(!IsNull())
    {
	result.SetX(GetX()/scalar);
	result.SetY(GetY()/scalar);
    }
    else
    {
	result.SetX(0);
	result.SetY(0);
    }
    return result;
}

void NaGeVector2D::operator /= (const double &scalar)
{
    if(!IsNull())
    {
	SetX(GetX()/scalar);
	SetY(GetY()/scalar);
    }
    else
    {
	SetX(0);
	SetY(0);
    }
}

NaGeVector2D NaGeVector2D::operator ^ (const NaGeVector2D &V1)
{
    return this->Crossed(V1);
}

void NaGeVector2D::operator ^= (const NaGeVector2D &V1)
{
    this->Cross(V1);
}

bool NaGeVector2D::operator == (const NaGeVector2D& V) const
{
    return(itsX==V.GetX()&&itsY==V.GetY());
}

NaGeVector2D::operator NaGePoint2D()
{
    NaGePoint2D P(itsX, itsY);
    return P;
}

double NaGeVector2D::Magnitude() const
{
    if(!IsNull())
    {
	double result;
	result = sqrt(pow((double)GetX(), 2)+pow((double)GetY(), 2));
	return result;
    }
    else
    {
	return 0;
    }
}

double NaGeVector2D::SqrMagnitude() const
{
    if(!IsNull())
    {
	double result;
	result = pow((double)GetX(), 2)+pow((double)GetY(), 2);
	return result;
    }
    else
	return 0;
}

double NaGeVector2D::CrossMagnitude(const NaGeVector2D &V)
{
    if(!IsNull() && !V.IsNull())
    {
	NaGeVector2D V1 = (*this);
	NaGeVector2D V2 = V;
	V1.Cross(V2);
	double result;
	result = sqrt(pow((double)V1.GetX(), 2)+pow((double)V1.GetY(), 2));
	return result;
    }
    else
    {
	return 0;
    }
}

double NaGeVector2D::CrossSqrMagnitude(const NaGeVector2D &V)
{
    if(!IsNull() && !V.IsNull())
    {
	NaGeVector2D V1 = (*this);
	NaGeVector2D V2 = V;
	V1.Cross(V2);
	double result;
	result = pow((double)V1.GetX(), 2)+pow((double)V1.GetY(), 2);
	return result;
    }
    else
    {
	return 0;
    }
}

double NaGeVector2D::Modulus()
{
    return sqrt(itsX*itsX + itsY*itsY);
}

NaGeVector2D NaGeVector2D::Unit()
{
    NaGeVector2D result;
    double x, y;
    if(!IsNull())
    {
	x = GetX()/Magnitude();
	y = GetY()/Magnitude();
	result.SetX(x);
	result.SetY(y);
	return result;
    }
    else
	return *this;
}

NaGePoint2D NaGeVector2D::Point()
{
    NaGePoint2D aPnt;
    aPnt.SetParam(GetX(), GetY());
    return aPnt;
}

double NaGeVector2D::Angle(const NaGeVector2D& Other) const
{
    double theta, a, b, dot;
    NaGeVector2D tempV = Other;
    if(!this->IsNull() && !tempV.IsNull())
    {
	dot = this->Dot(Other);
	a = this->Magnitude();
	b = tempV.Magnitude();
	theta = acos(dot/(a*b));
	return theta;
    }
    else
	return 0;
}

double NaGeVector2D::Angle(const NaGeVector2D& Other, const NaGeVector2D& Dir) const
{
    double theta;
    NaGeVector2D tempV = Other;
    NaGeVector2D D = Dir;
    NaGeVector2D N = this->Crossed(tempV);
    if(!this->IsNull() && !tempV.IsNull())
    {
	theta = Angle(Other);

	if(IsOpposite(tempV))
	{
	    return PI;
	}
	else
	{
	    if(N.Angle(D)<=0.0001)

		return theta;
	    else
		return -theta;
	}
    }
    else
	return 0;
}

bool NaGeVector2D::IsNull() const
{
    if(itsX==0&&itsY==0)
	return true;
    return false;
}

bool NaGeVector2D::IsParallel(const NaGeVector2D& V) const
{
    /*double ang=0;
      NaGeVector2D tempV = V;
      ang = this->Angle(tempV);
      if(ang==0 || ang==(double)2*PI)
      return true;
      else
      return false;*/
    NaGeVector2D N = this->Crossed(V);
    return (N.IsNull());
}

bool NaGeVector2D::IsOpposite(const NaGeVector2D& V) const

{
    double ang=0;
    NaGeVector2D tempV = V;
    ang = this->Angle(tempV);
    if(fabs(ang-PI)<=0.0001)

	return true;
    else
	return false;
}

bool NaGeVector2D::IsNormal(const NaGeVector2D& V) const
{
    double ang=0;
    NaGeVector2D tempV = V;
    ang = this->Angle(tempV);
    if(fabs(ang-PI/2)<=0.0001)
	return true;
    else
	return false;
}

void NaGeVector2D::Print() const
{
    cout<<"X = "<<GetX()<<endl;
    cout<<"Y = "<<GetY()<<endl;
}

void NaGeVector2D::Normalize()
{
    double x, y;
    if(!IsNull())
    {
	x = GetX()/Magnitude();
	y = GetY()/Magnitude();
	SetX(x);
	SetY(y);
    }
    else
	return;
}

void NaGeVector2D::Translate(const NaGeOneAxis2D& Ax, const double& amt)
{
    NaGeGeometry2D::Translate(Ax, amt);
}

void NaGeVector2D::Translate(double dx, double dy)
{
    NaGePoint2D P = (*this);
    P.Translate(dx, dy);
    NaGeVector2D V = P;
    (*this) = V;

}

void NaGeVector2D::Translate(const NaGeVector2D& dV)
{
    NaGePoint2D P = (*this);
    P.Translate(dV);
    NaGeVector2D V = P;
    (*this) = V;
}

void NaGeVector2D::Translate(const NaGePoint2D& P1, const NaGePoint2D& P2)
{
    NaGePoint2D P = (*this);
    P.Translate(P1, P2);
    NaGeVector2D V = P;
    (*this) = V;
}

void NaGeVector2D::Rotate(const NaGePoint2D& Pt, double ang)
{
    NaGePoint2D P1 = Pt;
    NaGeMatrix22 M;
    M.SetRotation(ang);
    NaGePoint2D tp = *this - (NaGeVector2D)P1;
    NaGeVector2D V = M * (NaGeVector2D)tp;
    V += (NaGeVector2D)P1;
    *this = V;
}

void NaGeVector2D::Scale(const NaGePoint2D& P1, double fact)
{
    NaGePoint2D P = (*this);
    P.Scale(P1, fact);
    NaGeVector2D V = P;
    (*this) = V;
}

void NaGeVector2D::Mirror(const NaGePoint2D& P1)
{
    NaGePoint2D P = (*this);
    P.Mirror(P1);
    NaGeVector2D V = P;
    (*this) = V;
}

void NaGeVector2D::Mirror(const NaGeOneAxis2D& Ax)
{
    NaGePoint2D P = (*this);
    P.Mirror(Ax);
    NaGeVector2D V = P;
    (*this) = V;
}

NaGeVector2D NaGeVector2D::Origin()
{
    return NaGeVector2D(0,0);
}
