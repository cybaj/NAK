// Line3D.cpp: implementation of the NaGeLine3D class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "NaGeLine3D.h"
#include "NaGeMMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

NaGeLine3D::NaGeLine3D()
{
	cType = LINE;
}

NaGeLine3D::NaGeLine3D(const NaGePoint3D& sP, const NaGePoint3D& eP) : startPoint(sP), endPoint(eP)
{
	NaGeOneAxis Ax(sP, NaGeVector3D(sP, eP));
	itsLocation = Ax;
	cType = LINE;
}

NaGeLine3D::NaGeLine3D(const NaGePoint3D& P, const NaGeVector3D& V)
{
	NaGeVector3D dir = V;
	NaGeVector3D sv = dir.Unit() * -INFINITY;
	NaGeVector3D ev = dir.Unit() * INFINITY;
	sv.SetParam(sv.GetX()+P.GetX(), sv.GetY()+P.GetY(), sv.GetZ()+P.GetZ());
	ev.SetParam(ev.GetX()+P.GetX(), ev.GetY()+P.GetY(), ev.GetZ()+P.GetZ());

	startPoint.SetParam(sv.GetX(), sv.GetY(), sv.GetZ());
	endPoint.SetParam(ev.GetX(), ev.GetY(), ev.GetZ());

	NaGeOneAxis Ax(startPoint, NaGeVector3D(sv, ev));
	itsLocation = Ax;

	cType = LINE;
}

NaGeLine3D::~NaGeLine3D()
{
}

void NaGeLine3D::Reverse()
{
	NaGePoint3D tPnt = startPoint;
	startPoint = endPoint;
	endPoint = tPnt;
}

NaGePoint3D NaGeLine3D::PointAtPara(const double& par)
{
	double u;
	if (par < 0)
		u = 0;
	else if(par > 1)
		u = 1;
	else
		u = par;

	NaGePoint3D aPnt;
	//aPnt = startPoint + (endPoint - startPoint) * u;

	//(x,y) = (1-t)(x1,y1) + t(x2,y2)
	aPnt = (startPoint * (1-u)) + (endPoint * u);
	return aPnt;
}

bool NaGeLine3D::IsClosed() const
{
	return false;
}

bool NaGeLine3D::operator == (const NaGeLine3D& L) const
{
	bool eq = (startPoint == L.StartPoint() && endPoint == L.EndPoint());
	return eq;
}

void NaGeLine3D::operator = (const NaGeLine3D& L)
{
	itsLocation = L.GetLocation();
	startPoint = L.StartPoint();
	endPoint = L.EndPoint();
}

NaGeVector3D NaGeLine3D::Direction() const
{
	NaGeVector3D sv(startPoint);
	NaGeVector3D ev(endPoint);
	NaGeVector3D dir(sv, ev);
	return dir.Unit();
}

NaGeVector3D NaGeLine3D::NormalThrough(const NaGePoint3D& P)
{
	NaGePoint3D P3 = P;
	NaGePoint3D P1 = startPoint;
	double D = Distance(P3);
	D = 1/D;
	NaGeVector3D N1 = Direction();
	NaGeVector3D PV = NaGeVector3D(P3 - P1);
	double dt = PV.Dot(N1);
	NaGeVector3D N = (NaGeVector3D(P3 - P1) - N1*(dt)) * D;
	return N;
}

double NaGeLine3D::Distance(const NaGePoint3D& P) const
{
	NaGePoint3D P3 = P;
	NaGePoint3D P1 = startPoint;
	NaGePoint3D P2 = endPoint;
	double x1, y1, z1, x2, y2, z2, x3, y3, z3;
	x1 = P1.GetX(); y1 = P1.GetY(); z1 = P1.GetZ();
	x2 = P2.GetX(); y2 = P2.GetY(); z2 = P2.GetZ();
	x3 = P3.GetX(); y3 = P3.GetY(); z3 = P3.GetZ();
	double L = P1.Distance(P2);
	L = 1/L;
	double D = L * (sqrt(pow((y3-y1)*(z2-z1)-(z3-z1)*(y2-y1),2)
		                +pow((z3-z1)*(x2-x1)-(x3-x1)*(z2-z1),2)
						+pow((x3-x1)*(y2-y1)-(y3-y1)*(x2-x1),2)));
	return D;
}

void NaGeLine3D::Translate(const NaGeOneAxis& Ax, const double& amt)
{
	NaGeGeometry::Translate(Ax, amt);
}

void NaGeLine3D::Translate(double dx, double dy, double dz)
{
	startPoint.Translate(dx,dy,dz);
	endPoint.Translate(dx,dy,dz);
}

void NaGeLine3D::Translate(const NaGeVector3D& V)
{
	startPoint.Translate(V);
	endPoint.Translate(V);
}

NaGeCurve* NaGeLine3D::Copy() const
{
	NaGeLine3D* L = new NaGeLine3D(startPoint, endPoint);
	return L;
}

void NaGeLine3D::Translate(const NaGePoint3D& P1, const NaGePoint3D& P2)
{
	startPoint.Translate(P1, P2);
	endPoint.Translate(P1, P2);
}

void NaGeLine3D::Rotate(const NaGeOneAxis& Ax, double ang)
{
	startPoint.Rotate(Ax, ang);
	endPoint.Rotate(Ax, ang);
}

void NaGeLine3D::Scale(const NaGePoint3D& P, double fact)
{
	startPoint.Scale(P, fact);
	endPoint.Scale(P, fact);
}

void NaGeLine3D::Mirror(const NaGePoint3D& P)
{
	startPoint.Mirror(P);
	endPoint.Mirror(P);
}

void NaGeLine3D::Mirror(const NaGeOneAxis& Ax)
{
	startPoint.Mirror(Ax);
	endPoint.Mirror(Ax);
}

void NaGeLine3D::Mirror(const NaGePlane& Pln)
{
	startPoint.Mirror(Pln);
	endPoint.Mirror(Pln);
}
