// OneAxis2D.cpp: implementation of the NaGeOneAxis2D class.
//
//////////////////////////////////////////////////////////////////////


#include "stdafx.h"

#include "NaGeOneAxis2D.h"
#include "NaGePoint2D.h"
#include "NaGeVector2D.h"
#include "NaGeMMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//Implementation of class OneAxis 
//(Used for construction of revolutions and as axis of symmetries)
NaGeOneAxis2D::NaGeOneAxis2D()
{
	Position = NaGePoint2D(0,0);
	Direction = NaGeVector2D(1,0);
	Direction.Normalize();
	Origin.SetParam(0,0);
	geomType = GEONEAXIS2D;
}

NaGeOneAxis2D::NaGeOneAxis2D(const NaGePoint2D& Pos, const NaGeVector2D& Dir) : Position(Pos), Direction(Dir)
{
	Direction.Normalize();
	Origin.SetParam(Pos.GetX(),Pos.GetY());
	geomType = GEONEAXIS2D;
}

NaGeOneAxis2D::~NaGeOneAxis2D()
{
}

void NaGeOneAxis2D::SetPosition(const NaGePoint2D& P)
{
	Position = P;
	Origin = P;
}

void NaGeOneAxis2D::SetPosition(double x, double y)

{
	Position.SetParam(x,y);
	Origin.SetParam(x,y);
}

void NaGeOneAxis2D::SetDirection(const NaGeVector2D& D)
{
	Direction = D;
	Direction.Normalize();
}

void NaGeOneAxis2D::SetDirection(double dx, double dy)
{
	Direction.SetParam(dx,dy);
	Direction.Normalize();
}

NaGePoint2D NaGeOneAxis2D::GetPosition() const
{
	return Position;
}

NaGeVector2D NaGeOneAxis2D::GetOrigin() const
{
	return Origin;
}

NaGeVector2D NaGeOneAxis2D::GetDirection() const
{
	return Direction;
}

bool NaGeOneAxis2D::operator == (const NaGeOneAxis2D& rhAx) const
{
	bool eq = (Position == rhAx.GetPosition() && Direction == rhAx.GetDirection()
				&& Origin == rhAx.GetOrigin());
	return eq;
}

void NaGeOneAxis2D::Translate(const NaGeOneAxis2D& Ax, const double& amt)
{
	NaGeGeometry2D::Translate(Ax, amt);
}

void NaGeOneAxis2D::Translate(double dx, double dy)
{
	NaGePoint2D P = Position;
	P.Translate(dx, dy);
	SetPosition(P);
	Origin.SetParam(P.GetX(), P.GetY());
}

void NaGeOneAxis2D::Translate(const NaGeVector2D& V)
{
	NaGePoint2D P = Position;
	P.Translate(V);
	SetPosition(P);
	Origin.SetParam(P.GetX(), P.GetY());
}

void NaGeOneAxis2D::Translate(const NaGePoint2D& P1, const NaGePoint2D& P2)
{
	NaGePoint2D P = Position;
	P.Translate(P1, P2);
	SetPosition(P);
	Origin.SetParam(P.GetX(), P.GetY());
}

void NaGeOneAxis2D::Rotate(const NaGePoint2D& Ax, double ang)
{
	NaGePoint2D P = Position;
	NaGeVector2D D = Direction;
	P.Rotate(Ax, ang);
	D.Rotate(Ax, ang);
	SetPosition(P);
	SetDirection(D);
	Origin.SetParam(P.GetX(), P.GetY());
}

void NaGeOneAxis2D::Scale(const NaGePoint2D& Pnt, double fact)
{
	NaGePoint2D P = Position;
	NaGeVector2D D = Direction;
	P.Scale(Pnt, fact);
	D.Scale(Pnt, fact);
	SetPosition(P);
	SetDirection(D);
	Origin.SetParam(P.GetX(), P.GetY());
}

void NaGeOneAxis2D::Mirror(const NaGePoint2D& Pnt)
{
	NaGePoint2D P = Position;
	NaGeVector2D D = Direction;
	P.Mirror(Pnt);
	D.Mirror(Pnt);
	SetPosition(P);
	SetDirection(D);
	Origin.SetParam(P.GetX(), P.GetY());
}

void NaGeOneAxis2D::Mirror(const NaGeOneAxis2D& Ax)
{
	NaGePoint2D P = Position;
	NaGeVector2D D = Direction;
	/*CString str;
	str.Format(" Now Direction X %0.3lf Y %0.3lf Z %0.3lf", D.GetX(),D.GetY(),D.GetZ());
	MessageBox(0, str, "From Axis", MB_OK);*/
	P.Mirror(Ax);
	NaGeVector2D dir = Ax.GetDirection();
	if(dir.IsParallel(D))
		D.Mirror(Ax.GetDirection());
	else
		D.Mirror(Ax);
	/*str.Format(" Now Direction X %0.3lf Y %0.3lf Z %0.3lf", D.GetX(),D.GetY(),D.GetZ());
	MessageBox(0, str, "From Axis", MB_OK);*/
	SetPosition(P);
	SetDirection(D);
	Origin.SetParam(P.GetX(), P.GetY());
}

NaGeOneAxis2D NaGeOneAxis2D::OX()
{
	NaGeOneAxis2D Ax(NaGePoint2D(0,0), NaGeVector2D(1,0));
	return Ax;
}

NaGeOneAxis2D NaGeOneAxis2D::OY()
{
	NaGeOneAxis2D Ax(NaGePoint2D(0,0), NaGeVector2D(0,1));
	return Ax;
}

