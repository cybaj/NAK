// Line2D.cpp: implementation of the NaGeLine2D class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "NaGeLine2D.h"
#include "NaGeMMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

NaGeLine2D::NaGeLine2D()
{
	cType = LINE2D;
}

NaGeLine2D::NaGeLine2D(const NaGePoint2D& sP, const NaGePoint2D& eP) : startPoint(sP), endPoint(eP)
{
	NaGeOneAxis2D Ax(sP, NaGeVector2D(sP, eP));
	itsLocation = Ax;
	cType = LINE2D;
}

NaGeLine2D::NaGeLine2D(const NaGePoint2D& P, const NaGeVector2D& V)
{
	NaGeVector2D dir = V;
	NaGeVector2D sv = dir.Unit() * -INFINITY;
	NaGeVector2D ev = dir.Unit() * INFINITY;
	sv.SetParam(sv.GetX()+P.GetX(), sv.GetY()+P.GetY());
	ev.SetParam(ev.GetX()+P.GetX(), ev.GetY()+P.GetY());

	startPoint.SetParam(sv.GetX(), sv.GetY());
	endPoint.SetParam(ev.GetX(), ev.GetY());

	NaGeOneAxis2D Ax(startPoint, NaGeVector2D(sv, ev));
	itsLocation = Ax;

	cType = LINE2D;
}

NaGeLine2D::~NaGeLine2D()
{
}

void NaGeLine2D::Reverse()
{
	NaGePoint2D tPnt = startPoint;
	startPoint = endPoint;
	endPoint = tPnt;
}

NaGePoint2D NaGeLine2D::PointAtPara(const double& par)
{
	double u;
	if (par < 0)
		u = 0;
	else if(par > 1)
		u = 1;
	else
		u = par;

	NaGePoint2D aPnt;
	aPnt = startPoint + (endPoint - startPoint) * u;
	return aPnt;
}

bool NaGeLine2D::IsClosed() const
{
	return false;
}

bool NaGeLine2D::operator == (const NaGeLine2D& L) const
{
	bool eq = (startPoint == L.StartPoint() && endPoint == L.EndPoint());
	return eq;
}

void NaGeLine2D::operator = (const NaGeLine2D& L)
{
	itsLocation = L.GetLocation();
	startPoint = L.StartPoint();
	endPoint = L.EndPoint();
}

NaGeVector2D NaGeLine2D::Direction() const
{
	NaGeVector2D sv(startPoint);
	NaGeVector2D ev(endPoint);
	NaGeVector2D dir(sv, ev);
	return dir.Unit();
}

NaGeVector2D NaGeLine2D::NormalThrough(const NaGePoint2D& P)
{
	NaGePoint2D P3 = P;
	NaGePoint2D P1 = startPoint;
	double D = Distance(P3);
	D = 1/D;
	NaGeVector2D N1 = Direction();
	NaGeVector2D PV = NaGeVector2D(P3 - P1);
	double dt = PV.Dot(N1);
	NaGeVector2D N = (NaGeVector2D(P3 - P1) - N1*(dt)) * D;
	return N;
}

double NaGeLine2D::Distance(const NaGePoint2D& P)
{
	NaGePoint2D P3 = P;
	NaGePoint2D P1 = startPoint;
	NaGePoint2D P2 = endPoint;
	double x1, y1, x2, y2, x3, y3;
	x1 = P1.GetX(); y1 = P1.GetY();
	x2 = P2.GetX(); y2 = P2.GetY();
	x3 = P3.GetX(); y3 = P3.GetY();
	double L = P1.Distance(P2);
	L = 1/L;
	double D = L * (sqrt(pow((x3-x1)*(y2-y1)-(y3-y1)*(x2-x1),2)));
	return D;
}

void NaGeLine2D::Translate(const NaGeOneAxis2D& Ax, const double& amt)
{
	NaGeGeometry2D::Translate(Ax, amt);
}

void NaGeLine2D::Translate(double dx, double dy)
{
	startPoint.Translate(dx,dy);
	endPoint.Translate(dx,dy);
}

void NaGeLine2D::Translate(const NaGeVector2D& V)
{
	startPoint.Translate(V);
	endPoint.Translate(V);
}

NaGeCurve2D* NaGeLine2D::Copy() const
{
	NaGeLine2D* L = new NaGeLine2D(startPoint, endPoint);
	return L;
}

void NaGeLine2D::Translate(const NaGePoint2D& P1, const NaGePoint2D& P2)
{
	startPoint.Translate(P1, P2);
	endPoint.Translate(P1, P2);
}

void NaGeLine2D::Rotate(const NaGePoint2D& Ax, double ang)
{
	startPoint.Rotate(Ax, ang);
	endPoint.Rotate(Ax, ang);
}

void NaGeLine2D::Scale(const NaGePoint2D& P, double fact)
{
	startPoint.Scale(P, fact);
	endPoint.Scale(P, fact);
}

void NaGeLine2D::Mirror(const NaGePoint2D& P)
{
	startPoint.Mirror(P);
	endPoint.Mirror(P);
}

void NaGeLine2D::Mirror(const NaGeOneAxis2D& Ax)
{
	startPoint.Mirror(Ax);
	endPoint.Mirror(Ax);
}

