// OffsetCurve.cpp: implementation of the NaGeOffsetCurve class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "NaGeOffsetCurve.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

NaGeOffsetCurve::NaGeOffsetCurve(const NaGeCurve& aCurve, const double& offset, const NaGePlane& refPlane, const bool& sense)
{
	itsCurve = aCurve.Copy();
	itsOffset = offset;
	itsPlane = refPlane;
	itsSense = sense;
}

NaGeOffsetCurve::~NaGeOffsetCurve()
{
	if(itsCurve)
		delete itsCurve;
}

void NaGeOffsetCurve::Reverse()
{
	itsCurve->Reverse();
}

NaGePoint3D NaGeOffsetCurve::PointAtPara(const double& para)
{
	NaGeVector3D dir = itsPlane.GetDirection();
	NaGeVector3D tangent(itsCurve->PointAtPara(para), itsCurve->PointAtPara(para+0.001));
	NaGeVector3D normal = dir^tangent;
	normal.Normalize();
	if(!itsSense)
		normal = normal * -1.0;
	NaGePoint3D P = itsCurve->PointAtPara(para);
	P = P + normal * itsOffset;
	return P;
}

double NaGeOffsetCurve::FirstParameter() const
{
	return itsCurve->FirstParameter();
}

double NaGeOffsetCurve::LastParameter() const
{
	return itsCurve->LastParameter();
}

bool NaGeOffsetCurve::IsClosed() const
{
	return itsCurve->IsClosed();
}

bool NaGeOffsetCurve::IsOfType(const CurveType& type) const
{
	bool b = (type == OFFSETCURVE);
	return b;

}

NaGeCurve* NaGeOffsetCurve::Copy() const
{
	NaGeOffsetCurve* myCurve = new NaGeOffsetCurve(*itsCurve, itsOffset, itsPlane, itsSense);
	return myCurve;
}

void NaGeOffsetCurve::Translate(double dx, double dy, double dz)
{
    itsCurve->Translate(dx, dy, dz);
}

void NaGeOffsetCurve::Translate(const NaGeVector3D& V)
{
    itsCurve->Translate(V);
}

void NaGeOffsetCurve::Translate(const NaGePoint3D& fro, const NaGePoint3D& to)
{
    itsCurve->Translate(fro, to);
}

void NaGeOffsetCurve::Rotate(const NaGeOneAxis& axis, double angle)
{
    itsCurve->Rotate(axis, angle);
}

void NaGeOffsetCurve::Scale(const NaGePoint3D& point, double fact)
{
    itsCurve->Scale(point, fact);
}

void NaGeOffsetCurve::Mirror(const NaGePoint3D& point)
{
    itsCurve->Mirror(point );
}

void NaGeOffsetCurve::Mirror(const NaGeOneAxis& axis)
{
    itsCurve->Mirror(axis);
}

void NaGeOffsetCurve::Mirror(const NaGePlane& plane)
{
    itsCurve->Mirror(plane);
}

