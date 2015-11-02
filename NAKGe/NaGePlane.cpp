// Plane.cpp: implementation of the NaGePlane class.
//
//////////////////////////////////////////////////////////////////////


#include "stdafx.h"

#include "NaGePlane.h"
#include "NaGePoint3D.h"
#include "NaGeVector3D.h"
#include "NaGeOneAxis.h"
#include "NaGeGeomException.h"
#include "NaGeMMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

NaGePlane::NaGePlane(const NaGePoint3D& P1, const NaGePoint3D& P2, const NaGePoint3D& P3)
{
	NaGeVector3D V1(P1, P2);
	NaGeVector3D V2(P1, P3);
	NaGeVector3D Dir = V1^V2;

	NaGeAxisSystem ax(P1, Dir, V1);
	itsLocation = ax;

	UpdateEquation();
	
	geomType = GEPLANE;
}


NaGePlane::NaGePlane(const NaGePoint3D& P1, const NaGeVector3D& V1, const NaGeVector3D& V2)
{
	NaGeVector3D v1 = V1, v2 = V2;
	NaGeVector3D Dir = v1^v2;

	NaGeAxisSystem ax(P1, Dir, v1);
	itsLocation = ax;

	UpdateEquation();
	
	geomType = GEPLANE;
}

NaGePlane::NaGePlane(const double& A, const double& B, const double& C, const double& D)
{
	Equation[0] = A;
	Equation[1] = B;
	Equation[2] = C;
	Equation[3] = D;

	NaGePoint3D Pos(A, B, C);
	NaGeVector3D Dir(A, B, C);

	
	NaGeAxisSystem location(Pos, Dir);

	double d = location.GetDirection().Magnitude();
	if ( d > 0.0 )
	{
		d = 1.0/d;
		NaGeVector3D O = location.GetDirection()*(-d)*Equation[3];
		location.SetPosition(O.Point());
	}

	itsLocation = location;
	
	geomType = GEPLANE;
}

NaGePlane::NaGePlane(const NaGeOneAxis& Ax)
{
	NaGeOneAxis ax = Ax;

	NaGePoint3D P = Ax.GetPosition();
	NaGeVector3D V = Ax.GetDirection();

	NaGeAxisSystem location(P, V);

	itsLocation = location;

	UpdateEquation();
	geomType = GEPLANE;
}

NaGePlane::~NaGePlane()
{
}

NaGePoint3D NaGePlane::PointAtPara(const double uPar, const double vPar)
{
	NaGeVector3D V;
	V = itsLocation.GetOrigin() + itsLocation.GetXDirection() * uPar + itsLocation.GetYDirection() * vPar;
	/*CString str;
	str.Format("YDirection %0.3lf, %0.3lf, %0.3lf",itsLocation.GetYDirection().GetX(),itsLocation.GetYDirection().GetY(),itsLocation.GetYDirection().GetZ());
	MessageBox(0, str, "From Plane", MB_OK);*/
	return V.Point();
}

NaGePoint3D NaGePlane::GetPosition() const
{
	return itsLocation.GetPosition();
}

NaGeVector3D NaGePlane::GetDirection() const
{
	return itsLocation.GetDirection();
}

void NaGePlane::EquationAt(const NaGePoint3D& P, double* e)
{
	double x = P.GetX();
	double y = P.GetY();
	double z = P.GetZ();
	e[0] = Equation[0]*x;
	e[1] = Equation[1]*y;
	e[2] = Equation[2]*z;
	e[3] = Equation[3];
}

double NaGePlane::GetConstant() const
{
	return Equation[3];
}

void NaGePlane::Translate(const NaGeOneAxis& Ax, const double& amt)
{
	NaGeGeometry::Translate(Ax, amt);
}

void NaGePlane::Translate(double dx, double dy, double dz)
{
	itsLocation.Translate(dx, dy, dz);
}

void NaGePlane::Translate(const NaGeVector3D& V)
{
	itsLocation.Translate(V);
}

void NaGePlane::Translate(const NaGePoint3D& P1, const NaGePoint3D& P2)
{
	itsLocation.Translate(P1, P2);
}

void NaGePlane::Rotate(const NaGeOneAxis& Ax, double ang)
{
	itsLocation.Rotate(Ax, ang);
}

void NaGePlane::Scale(const NaGePoint3D& P, double fact)
{
	itsLocation.Scale(P, fact);
}

void NaGePlane::Mirror(const NaGePoint3D& P)
{
	itsLocation.Mirror(P);
}

void NaGePlane::Mirror(const NaGeOneAxis& Ax)
{
	itsLocation.Mirror(Ax);
}

void NaGePlane::Mirror(const NaGePlane& Pln)
{
	itsLocation.Mirror(Pln);
}

void NaGePlane::UpdateEquation()
{
	NaGeVector3D Z = itsLocation.GetDirection();
	Equation[0] = Z.GetX();
	Equation[1] = Z.GetY();
	Equation[2] = Z.GetZ();
	Equation[3] = -(itsLocation.GetOrigin().Dot(Z));
}

NaGePlane NaGePlane::XOY()
{
	NaGePlane P = NaGePlane(NaGeOneAxis(NaGePoint3D(0,0,0), NaGeVector3D(0,0,1)));
	return P;
}

NaGePlane NaGePlane::YOZ()
{
	NaGePlane P = NaGePlane(NaGeOneAxis(NaGePoint3D(0,0,0), NaGeVector3D(1,0,0)));
	return P;
}

NaGePlane NaGePlane::ZOX()
{
	NaGePlane P = NaGePlane(NaGeOneAxis(NaGePoint3D(0,0,0), NaGeVector3D(0,1,0)));
	return P;
}
