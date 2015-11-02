// OneAxis.cpp: implementation of the NaGeOneAxis class.
//
//////////////////////////////////////////////////////////////////////


#include "stdafx.h"

#include "NaGeOneAxis.h"
#include "NaGePoint3D.h"
#include "NaGeVector3D.h"
#include "NaGeMMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//Implementation of class OneAxis 
//(Used for construction of revolutions and as axis of symmetries)
NaGeOneAxis::NaGeOneAxis()
{
	Position = NaGePoint3D(0,0,0);
	Direction = NaGeVector3D(0,0,1);
	Direction.Normalize();
	Origin.SetParam(0,0,0);
	geomType = GEONEAXIS;
}

NaGeOneAxis::NaGeOneAxis(const NaGePoint3D& Pos, const NaGeVector3D& Dir) : Position(Pos), Direction(Dir)
{
	Direction.Normalize();
	Origin.SetParam(Pos.GetX(),Pos.GetY(),Pos.GetZ());
	geomType = GEONEAXIS;
}

NaGeOneAxis::~NaGeOneAxis()
{
}

void NaGeOneAxis::SetPosition(const NaGePoint3D& P)
{
	Position = P;
	Origin = P;
}

void NaGeOneAxis::SetPosition(double x, double y, double z)

{
	Position.SetParam(x,y,z);
	Origin.SetParam(x,y,z);
}

void NaGeOneAxis::SetDirection(const NaGeVector3D& D)
{
	Direction = D;
	Direction.Normalize();
}

void NaGeOneAxis::SetDirection(double dx, double dy, double dz)
{
	Direction.SetParam(dx,dy,dz);
	Direction.Normalize();
}

NaGePoint3D NaGeOneAxis::GetPosition() const
{
	return Position;
}

NaGeVector3D NaGeOneAxis::GetOrigin() const
{
	return Origin;
}

NaGeVector3D NaGeOneAxis::GetDirection() const
{
	return Direction;
}

bool NaGeOneAxis::operator == (const NaGeOneAxis& rhAx) const
{
	bool eq = (Position == rhAx.GetPosition() && Direction == rhAx.GetDirection()
				&& Origin == rhAx.GetOrigin());
	return eq;
}

void NaGeOneAxis::Translate(const NaGeOneAxis& Ax, const double& amt)
{
	NaGeGeometry::Translate(Ax, amt);
}

void NaGeOneAxis::Translate(double dx, double dy, double dz)
{
	NaGePoint3D P = Position;
	P.Translate(dx, dy, dz);
	SetPosition(P);
	Origin.SetParam(P.GetX(), P.GetY(), P.GetZ());
}

void NaGeOneAxis::Translate(const NaGeVector3D& V)
{
	NaGePoint3D P = Position;
	P.Translate(V);
	SetPosition(P);
	Origin.SetParam(P.GetX(), P.GetY(), P.GetZ());
}

void NaGeOneAxis::Translate(const NaGePoint3D& P1, const NaGePoint3D& P2)
{
	NaGePoint3D P = Position;
	P.Translate(P1, P2);
	SetPosition(P);
	Origin.SetParam(P.GetX(), P.GetY(), P.GetZ());
}

void NaGeOneAxis::Rotate(const NaGeOneAxis& Ax, double ang)
{
	NaGePoint3D P = Position;
	NaGeVector3D D = Direction;
	P.Rotate(Ax, ang);
	D.Rotate(Ax, ang);
	SetPosition(P);
	SetDirection(D);
	Origin.SetParam(P.GetX(), P.GetY(), P.GetZ());
}

void NaGeOneAxis::Scale(const NaGePoint3D& Pnt, double fact)
{
	NaGePoint3D P = Position;
	NaGeVector3D D = Direction;
	P.Scale(Pnt, fact);
	D.Scale(Pnt, fact);
	SetPosition(P);
	SetDirection(D);
	Origin.SetParam(P.GetX(), P.GetY(), P.GetZ());
}

void NaGeOneAxis::Mirror(const NaGePoint3D& Pnt)
{
	NaGePoint3D P = Position;
	NaGeVector3D D = Direction;
	P.Mirror(Pnt);
	D.Mirror(Pnt);
	SetPosition(P);
	SetDirection(D);
	Origin.SetParam(P.GetX(), P.GetY(), P.GetZ());
}

void NaGeOneAxis::Mirror(const NaGeOneAxis& Ax)
{
	NaGePoint3D P = Position;
	NaGeVector3D D = Direction;
	/*CString str;
	str.Format(" Now Direction X %0.3lf Y %0.3lf Z %0.3lf", D.GetX(),D.GetY(),D.GetZ());
	MessageBox(0, str, "From Axis", MB_OK);*/
	P.Mirror(Ax);
	NaGeVector3D dir = Ax.GetDirection();
	if(dir.IsParallel(D))
		D.Mirror(Ax.GetDirection());
	else
		D.Mirror(Ax);
	/*str.Format(" Now Direction X %0.3lf Y %0.3lf Z %0.3lf", D.GetX(),D.GetY(),D.GetZ());
	MessageBox(0, str, "From Axis", MB_OK);*/
	SetPosition(P);
	SetDirection(D);
	Origin.SetParam(P.GetX(), P.GetY(), P.GetZ());
}

void NaGeOneAxis::Mirror(const NaGePlane& Pln)
{
	NaGePoint3D P = Position;
	NaGeVector3D D = Direction;
	P.Mirror(Pln);
	D.Mirror(Pln);
	SetPosition(P);
	SetDirection(D);
	Origin.SetParam(P.GetX(), P.GetY(), P.GetZ());
}

NaGeOneAxis NaGeOneAxis::OX()
{
	NaGeOneAxis Ax(NaGePoint3D(0,0,0), NaGeVector3D(1,0,0));
	return Ax;
}

NaGeOneAxis NaGeOneAxis::OY()
{
	NaGeOneAxis Ax(NaGePoint3D(0,0,0), NaGeVector3D(0,1,0));
	return Ax;
}

NaGeOneAxis NaGeOneAxis::OZ()
{
	NaGeOneAxis Ax(NaGePoint3D(0,0,0), NaGeVector3D(0,0,1));
	return Ax;
}

