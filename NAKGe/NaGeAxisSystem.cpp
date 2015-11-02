// AxisSystem.cpp: implementation of the NaGeAxisSystem class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"

#include "NaGePoint3D.h"
#include "NaGeVector3D.h"
#include "NaGeOneAxis.h"
#include "NaGeAxisSystem.h"
#include "NaGeGeomException.h"
#include "NaGeMMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//Implementation of class CoordSys (Local Coordinate System)
NaGeAxisSystem::NaGeAxisSystem()
{
	geomType = GEAXISSYSTEM;
}

NaGeAxisSystem::NaGeAxisSystem(const NaGePoint3D& Pos, const NaGeVector3D& Dir, const NaGeVector3D& XDir)
{
	Position = Pos;
	Origin.SetParam(Pos.GetX(),Pos.GetY(),Pos.GetZ());
	Direction = Dir;
	Direction.Normalize();
	XDirection = XDir;
	XDirection.Normalize();
	if(!Direction.IsNormal(XDirection))
		throw NaGeGeomException(ConstructionFailure);
	else
		YDirection = Direction.Crossed(XDirection);

	geomType = GEAXISSYSTEM;
}

NaGeAxisSystem::NaGeAxisSystem(const NaGePoint3D& Pos, const NaGeVector3D& Dir)
{
	Position = Pos;
	Origin.SetParam(Pos.GetX(),Pos.GetY(),Pos.GetZ());
	Direction = Dir;
	Direction.Normalize();

	NaGeVector3D V = Direction;
	double lA = V.GetX();
	double lB = V.GetY();
	double lC = V.GetZ();

	double Aabs = lA;
	if (Aabs < 0)
		Aabs = - Aabs;

	double Babs = lB;
	if (Babs < 0)
		Babs = - Babs;

	double Cabs = lC;
	if (Cabs < 0)
		Cabs = - Cabs;

	NaGeVector3D XAxis;
    
	if      ( Babs <= Aabs && Babs <= Cabs)
	{

		if (Aabs > Cabs)
			XAxis.SetParam(-lC,0., lA);
		else
			XAxis.SetParam( lC,0.,-lA);
	}
	else if( Aabs <= Babs && Aabs <= Cabs)
	{
		if (Babs > Cabs)
			XAxis.SetParam(0.,-lC, lB);
		else
			XAxis.SetParam(0., lC,-lB);
	}
	else
	{
		if (Aabs > Babs)
			XAxis.SetParam(-lB, lA,0.);
		else
			XAxis.SetParam(lB,-lA,0.);
	}
	XDirection = XAxis;
	XDirection.Normalize();
	if(!Direction.IsNormal(XDirection))
		throw NaGeGeomException(ConstructionFailure);
	else
		YDirection = Direction.Crossed(XDirection);

	geomType = GEAXISSYSTEM;
}

NaGeAxisSystem::NaGeAxisSystem(const NaGeAxisSystem& Ax) : NaGeGeometry()
{
	Position = Ax.GetPosition();
	Origin = Ax.GetOrigin();
	Direction = Ax.GetDirection();
	XDirection = Ax.GetXDirection();
	YDirection = Direction.Crossed(XDirection);

	geomType = GEAXISSYSTEM;
}

NaGeAxisSystem::~NaGeAxisSystem()
{
}

void NaGeAxisSystem::SetDirection(const NaGeVector3D& D)
{
	Direction = D;
	Direction.Normalize();
	if(!XDirection.IsParallel(Direction))
	{
		NaGeVector3D tempY = D.Crossed(XDirection);
		XDirection = tempY.Crossed(D);
		YDirection = Direction.Crossed(XDirection);
		XDirection.Normalize();
		YDirection.Normalize();
	}
	else
	{
		NaGeVector3D tempX = YDirection.Crossed(D);
		YDirection = D.Crossed(tempX);
		XDirection = Direction.Crossed(YDirection);
		XDirection.Normalize();
		YDirection.Normalize();
	}
}

void NaGeAxisSystem::SetDirection(double dx, double dy, double dz)
{
	NaGeVector3D D(dx, dy, dz);
	D.Unit();
	SetDirection(D);
}

void NaGeAxisSystem::SetXDirection(const NaGeVector3D& XD)
{
	if(!this->Direction.IsParallel(XD))
	{
		NaGeVector3D XDir = XD;
		XDir.Normalize();
		XDirection = Direction.CrossCrossed(XDir,Direction);
		YDirection = Direction.Crossed(XDirection);
	}
	else
		throw NaGeGeomException(ConstructionFailure);
}

void NaGeAxisSystem::SetXDirection(double dxx, double dxy, double dxz)
{
	NaGeVector3D XD(dxx, dxy, dxz);
	if(!this->Direction.IsParallel(XD))
	{
		SetXDirection(XD.Unit());
	}
	else
		throw NaGeGeomException(ConstructionFailure);
}

void NaGeAxisSystem::SetYDirection(const NaGeVector3D& YD)
{
	if(!this->Direction.IsParallel(YD))
	{
		NaGeVector3D YDir = YD;
		YDir.Normalize();
		YDirection = Direction.CrossCrossed(YDir, Direction);
		XDirection = YDirection.Crossed(Direction);
	}
	else
		throw NaGeGeomException(ConstructionFailure);
}

void NaGeAxisSystem::SetYDirection(double dyx, double dyy, double dyz)
{
	NaGeVector3D YD(dyx, dyy, dyz);
	if(!this->Direction.IsParallel(YD))
	{
		SetYDirection(YD.Unit());
	}
	else
		throw NaGeGeomException(ConstructionFailure);
}

void NaGeAxisSystem::SetPosition(double x, double y, double z)
{
	Position.SetParam(x,y,z);
	Origin.SetParam(x,y,z);
}

void NaGeAxisSystem::SetPosition(const NaGePoint3D& P)
{
	SetPosition(P.GetX(), P.GetY(), P.GetZ());
}

bool NaGeAxisSystem::operator == (const NaGeAxisSystem& C) const
{
	return (Position==C.GetPosition()&&Direction==C.GetDirection()
		&&XDirection==C.GetXDirection()&&YDirection==C.GetYDirection());
}

void NaGeAxisSystem::Translate(const NaGeOneAxis& Ax, const double& amt)
{
	NaGeGeometry::Translate(Ax, amt);
}


void NaGeAxisSystem::Translate(double dx, double dy, double dz)
{
	Position.Translate(dx,dy,dz);
	Origin.Translate(dx,dy,dz);
}

void NaGeAxisSystem::Translate(const NaGeVector3D& V)
{
	Position.Translate(V);
	Origin.Translate(V);
}

void NaGeAxisSystem::Translate(const NaGePoint3D& P1, const NaGePoint3D& P2)
{
	Position.Translate(P1, P2);
	Origin.Translate(P1, P2);
}

void NaGeAxisSystem::Rotate(const NaGeOneAxis& Ax, double ang)
{
	NaGeOneAxis tAx = Ax;
	tAx.Translate(tAx.GetPosition(), NaGePoint3D(0,0,0));
	NaGeVector3D Dir = GetDirection();
	NaGeOneAxis ax(GetPosition(), GetDirection());
	ax.Rotate(tAx, ang);
	Origin.Rotate(Ax, ang);
	Position = Origin.Point();
	SetDirection(ax.GetDirection());
}

void NaGeAxisSystem::Scale(const NaGePoint3D& P, double fact)
{
	Position.Scale(P, fact);
	Origin.Scale(P, fact);
	if (fact < 0)
	{
		Direction.Reverse();
	    XDirection.Reverse();
		YDirection.Reverse();
	}
}

void NaGeAxisSystem::Mirror(const NaGePoint3D& P)
{
	Position.Mirror(P);
	Origin.Mirror(P);
	Direction.Reverse();
	XDirection.Reverse();
	YDirection.Reverse();
}

void NaGeAxisSystem::Mirror(const NaGeOneAxis& Ax)
{
	Position.Mirror(Ax);
	Origin.Mirror(Ax);
	if(Direction.IsParallel(Ax.GetDirection()))
		Direction.Mirror (Ax.GetDirection());
	else
		Direction.Mirror (Ax);
	if(XDirection.IsParallel(Ax.GetDirection()))
		XDirection.Mirror (Ax.GetDirection());
	else
		XDirection.Mirror (Ax);
	if(YDirection.IsParallel(Ax.GetDirection()))
		YDirection.Mirror (Ax.GetDirection());
	else
		YDirection.Mirror (Ax);
	//SetDirection (XDirection.Crossed(YDirection));
}

void NaGeAxisSystem::Mirror(const NaGePlane& Pln)
{
	Position.Mirror(Pln);
	Origin.Mirror(Pln);
	Direction.Mirror (Pln);
	XDirection.Mirror (Pln);
	YDirection.Mirror (Pln);
}



