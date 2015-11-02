// Vector3d.cpp: implementation of the NaGeVector3D class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "NaGeVector3D.h"
#include "NaGePoint3D.h"
#include "NaGeMatrix33.h"
#include "NaGeOneAxis.h"
#include "NaGePlane.h"
#include "NaGeMMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//Implementation of class vector
NaGeVector3D::NaGeVector3D()
{
	itsX = 0;
	itsY = 0;
	itsZ = 0;
}

NaGeVector3D::NaGeVector3D(double x, double y, double z)
{
	itsX = x;
	itsY = y;
	itsZ = z;
}

NaGeVector3D::NaGeVector3D(const NaGePoint3D& P)
{
	itsX = P.GetX();
	itsY = P.GetY();
	itsZ = P.GetZ();
}

NaGeVector3D::NaGeVector3D(const NaGeVector3D &V1, const NaGeVector3D &V2)
{
	NaGeVector3D VC1, VC2, VC3;
	VC1 = V1;
	VC2 = V2;
	VC3 = VC2-VC1;
	itsX = VC3.GetX();
	itsY = VC3.GetY();
	itsZ = VC3.GetZ();
}

NaGeVector3D::NaGeVector3D(const NaGePoint3D &V1, const NaGePoint3D &V2)
{
	NaGePoint3D VC1, VC2;
	VC1 = V1;
	VC2 = V2;
	itsX = VC2.GetX()-VC1.GetX();
	itsY = VC2.GetY()-VC1.GetY();
	itsZ = VC2.GetZ()-VC1.GetZ();
}

NaGeVector3D::~NaGeVector3D()
{
}

double NaGeVector3D::Dot(const NaGeVector3D &V1) const
{
	double result;
	result = V1.GetX()*GetX()+V1.GetY()*GetY()+V1.GetZ()*GetZ();
	return result;
}

double NaGeVector3D::DotCross(const NaGeVector3D &V1, const NaGeVector3D &V2)
{
	NaGeVector3D A = (*this), B = V1, C = V2;
	NaGeVector3D cross = B.Crossed(C);
	double Res = A.Dot(cross);
	return Res;
}

void NaGeVector3D::Cross(const NaGeVector3D &V1)
{
	SetX(GetY()*V1.GetZ()-GetZ()*V1.GetY());
	SetY(GetZ()*V1.GetX()-GetX()*V1.GetZ());
	SetZ(GetX()*V1.GetY()-GetY()*V1.GetX());
}

NaGeVector3D NaGeVector3D::Crossed(const NaGeVector3D &V1) const
{
	NaGeVector3D result;
	result.SetX(GetY()*V1.GetZ()-GetZ()*V1.GetY());
	result.SetY(GetZ()*V1.GetX()-GetX()*V1.GetZ());
	result.SetZ(GetX()*V1.GetY()-GetY()*V1.GetX());
	return result;
}

void NaGeVector3D::CrossCross(const NaGeVector3D &V1, const NaGeVector3D &V2)
{
	NaGeVector3D A = (*this), B = V1, C = V2;
	NaGeVector3D Res = B*((C.Dot(A))) - C*(A.Dot(B));
	(*this) = Res;
}

NaGeVector3D NaGeVector3D::CrossCrossed(const NaGeVector3D &V1, const NaGeVector3D &V2)
{
	NaGeVector3D V = (*this);
	V.CrossCross(V1, V2);
	return V;
}

void NaGeVector3D::Reverse()
{
	this->SetX(-GetX());
	this->SetY(-GetY());
	this->SetZ(-GetZ());
}

NaGeVector3D NaGeVector3D::Reversed()
{
	NaGeVector3D result;
	result.Reverse();
	return result;
}

NaGeVector3D NaGeVector3D::operator + (const NaGeVector3D &V1)
{
	NaGeVector3D result;
	result.SetX(GetX()+V1.GetX());
	result.SetY(GetY()+V1.GetY());
	result.SetZ(GetZ()+V1.GetZ());
	return result;
}

void NaGeVector3D::operator += (const NaGeVector3D &V1)
{
	SetX(GetX()+V1.GetX());
	SetY(GetY()+V1.GetY());
	SetZ(GetZ()+V1.GetZ());
}

NaGeVector3D NaGeVector3D::operator - (const NaGeVector3D &V1)
{
	NaGeVector3D result;
	result.SetX(GetX()-V1.GetX());
	result.SetY(GetY()-V1.GetY());
	result.SetZ(GetZ()-V1.GetZ());
	return result;
}

void NaGeVector3D::operator -= (const NaGeVector3D &V1)
{
	SetX(GetX()-V1.GetX());
	SetY(GetY()-V1.GetY());
	SetZ(GetZ()-V1.GetZ());
}

NaGeVector3D NaGeVector3D::operator * (const double &scalar)
{
	NaGeVector3D result;
	result.SetX(GetX()*scalar);
	result.SetY(GetY()*scalar);
	result.SetZ(GetZ()*scalar);
	return result;
}

NaGeVector3D NaGeVector3D::operator * (const NaGeMatrix33 &M)
{
	NaGeVector3D V;
	V.SetX(M(0,0)*GetX()+M(0,1)*GetY()+M(0,2)*GetZ());
	V.SetY(M(1,0)*GetX()+M(1,1)*GetY()+M(1,2)*GetZ());
	V.SetZ(M(2,0)*GetX()+M(2,1)*GetY()+M(2,2)*GetZ());
	return V;
}

void NaGeVector3D::operator *= (const double &scalar)
{
	SetX(GetX()*scalar);
	SetY(GetY()*scalar);
	SetZ(GetZ()*scalar);
}

void NaGeVector3D::operator *= (const NaGeMatrix33 &M)
{
	SetX(M(0,0)*GetX()+M(0,1)*GetY()+M(0,2)*GetZ());
	SetY(M(1,0)*GetX()+M(1,1)*GetY()+M(1,2)*GetZ());
	SetZ(M(2,0)*GetX()+M(2,1)*GetY()+M(2,2)*GetZ());
}

NaGeVector3D NaGeVector3D::operator / (const double &scalar)
{
	NaGeVector3D result;
	if(!IsNull())
	{
		result.SetX(GetX()/scalar);
		result.SetY(GetY()/scalar);
		result.SetZ(GetZ()/scalar);
	}
	else
	{
		result.SetX(0);
		result.SetY(0);
		result.SetZ(0);
	}
	return result;
}

void NaGeVector3D::operator /= (const double &scalar)
{
	if(!IsNull())
	{
		SetX(GetX()/scalar);
		SetY(GetY()/scalar);
		SetZ(GetZ()/scalar);
	}
	else
	{
		SetX(0);
		SetY(0);
		SetZ(0);
	}
}

NaGeVector3D NaGeVector3D::operator ^ (const NaGeVector3D &V1)
{
	return this->Crossed(V1);
}

void NaGeVector3D::operator ^= (const NaGeVector3D &V1)
{
	this->Cross(V1);
}

bool NaGeVector3D::operator == (const NaGeVector3D& V) const
{
	return(itsX==V.GetX()&&itsY==V.GetY()&&itsZ==V.GetZ());
}

NaGeVector3D::operator NaGePoint3D()
{
	NaGePoint3D P(itsX, itsY, itsZ);
	return P;
}

double NaGeVector3D::Magnitude() const
{
	if(!IsNull())
	{
		double result;
		result = sqrt(pow((double)GetX(), 2)+pow((double)GetY(), 2)+pow((double)GetZ(), 2));
		return result;
	}
	else
	{
		return 0;
	}
}

double NaGeVector3D::SqrMagnitude() const
{
	if(!IsNull())
	{
		double result;
		result = pow((double)GetX(), 2)+pow((double)GetY(), 2)+pow((double)GetZ(), 2);
		return result;
	}
	else
		return 0;
}

double NaGeVector3D::CrossMagnitude(const NaGeVector3D &V)
{
	if(!IsNull() && !V.IsNull())
	{
		NaGeVector3D V1 = (*this);
		NaGeVector3D V2 = V;
		V1.Cross(V2);
		double result;
		result = sqrt(pow((double)V1.GetX(), 2)+pow((double)V1.GetY(), 2)+pow((double)V1.GetZ(), 2));
		return result;
	}
	else
	{
		return 0;
	}
}

double NaGeVector3D::CrossSqrMagnitude(const NaGeVector3D &V)
{
	if(!IsNull() && !V.IsNull())
	{
		NaGeVector3D V1 = (*this);
		NaGeVector3D V2 = V;
		V1.Cross(V2);
		double result;
		result = pow((double)V1.GetX(), 2)+pow((double)V1.GetY(), 2)+pow((double)V1.GetZ(), 2);
		return result;
	}
	else
	{
		return 0;
	}
}

double NaGeVector3D::Modulus()
{
	return sqrt(itsX*itsX + itsY*itsY + itsZ*itsZ);
}

NaGeVector3D NaGeVector3D::Unit()
{
	NaGeVector3D result;
	double x, y, z;
	if(!IsNull())
	{
		x = GetX()/Magnitude();
		y = GetY()/Magnitude();
		z = GetZ()/Magnitude();
		result.SetX(x);
		result.SetY(y);
		result.SetZ(z);
		return result;
	}
	else
		return *this;
}

NaGePoint3D NaGeVector3D::Point() const
{
	NaGePoint3D aPnt;
	aPnt.SetParam(GetX(), GetY(), GetZ());
	return aPnt;
}

double NaGeVector3D::Angle(const NaGeVector3D& Other) const
{
	double theta, a, b, dot;
	NaGeVector3D tempV = Other;
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

double NaGeVector3D::Angle(const NaGeVector3D& Other, const NaGeVector3D& Dir) const
{
	double theta;
	NaGeVector3D tempV = Other;
	NaGeVector3D D = Dir;
	NaGeVector3D N = this->Crossed(tempV);
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

bool NaGeVector3D::IsNull() const
{
	if(itsX==0&&itsY==0&&itsZ==0)
		return true;
	else
		return false;
}

bool NaGeVector3D::IsParallel(const NaGeVector3D& V) const
{
	/*double ang=0;
	NaGeVector3D tempV = V;
	ang = this->Angle(tempV);
	if(ang==0 || ang==(double)2*PI)
		return true;
	else
		return false;*/
	NaGeVector3D N = this->Crossed(V);
	return (N.IsNull());
}

bool NaGeVector3D::IsOpposite(const NaGeVector3D& V) const

{
	double ang=0;
	NaGeVector3D tempV = V;
	ang = this->Angle(tempV);
	if(fabs(ang-PI)<=0.0001)

		return true;
	else
		return false;
}

bool NaGeVector3D::IsNormal(const NaGeVector3D& V) const
{
	double ang=0;
	NaGeVector3D tempV = V;
	ang = this->Angle(tempV);
	if(fabs(ang-PI/2)<=0.0001)
		return true;
	else
		return false;
}

void NaGeVector3D::Print() const
{
	cout<<"X = "<<GetX()<<endl;
	cout<<"Y = "<<GetY()<<endl;
	cout<<"Z = "<<GetZ()<<endl;
}

void NaGeVector3D::Normalize()
{
	double x, y, z;
	if(!IsNull())
	{
		x = GetX()/Magnitude();
		y = GetY()/Magnitude();
		z = GetZ()/Magnitude();
		SetX(x);
		SetY(y);
		SetZ(z);
	}
	else
		return;
}

void NaGeVector3D::Translate(const NaGeOneAxis& Ax, const double& amt)
{
	NaGeGeometry::Translate(Ax, amt);
}

void NaGeVector3D::Translate(double dx, double dy, double dz)
{
	NaGePoint3D P = (*this);
	P.Translate(dx, dy, dz);
	NaGeVector3D V = P;
	(*this) = V;

}

void NaGeVector3D::Translate(const NaGeVector3D& dV)
{
	NaGePoint3D P = (*this);
	P.Translate(dV);
	NaGeVector3D V = P;
	(*this) = V;
}

void NaGeVector3D::Translate(const NaGePoint3D& P1, const NaGePoint3D& P2)
{
	NaGePoint3D P = (*this);
	P.Translate(P1, P2);
	NaGeVector3D V = P;
	(*this) = V;
}

void NaGeVector3D::Rotate(const NaGeOneAxis& Ax, double ang)
{
	NaGeOneAxis ax = Ax;
	NaGeVector3D P1 = ax.GetOrigin();
	NaGeVector3D V = ax.GetDirection();
	V.Normalize();
	NaGeMatrix33 M; NaGeVector3D PV(*this);
	M.SetRotation(V, ang);
	NaGeVector3D RV = M*(PV-P1);
	RV = RV + P1;
	*this = RV;
}

void NaGeVector3D::Scale(const NaGePoint3D& P1, double fact)
{
	NaGePoint3D P = (*this);
	P.Scale(P1, fact);
	NaGeVector3D V = P;
	(*this) = V;
}

void NaGeVector3D::Mirror(const NaGePoint3D& P1)
{
	NaGePoint3D P = (*this);
	P.Mirror(P1);
	NaGeVector3D V = P;
	(*this) = V;
}

void NaGeVector3D::Mirror(const NaGeOneAxis& Ax)
{
	NaGePoint3D P = (*this);
	P.Mirror(Ax);
	NaGeVector3D V = P;
	(*this) = V;
}

void NaGeVector3D::Mirror(const NaGePlane& Pln)
{
	NaGePoint3D P = (*this);
	P.Mirror(Pln);
	NaGeVector3D V = P;
	(*this) = V;
}

NaGeVector3D NaGeVector3D::Origin()
{
	return NaGeVector3D(0,0,0);
}

std::istream &operator>>(std::istream& input, NaGeVector3D &p)
{
    input>>p.itsX>>p.itsY>>p.itsZ;
    return input;
}

std::ostream &operator<<(std::ostream& output, NaGeVector3D &p)
{
    output<< p.itsX << " " << p.itsY << " " << p.itsZ;
    return output;
}

