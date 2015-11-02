// BoundingBox.cpp: implementation of the NaGeBoundingBox class.
//
//////////////////////////////////////////////////////////////////////


#include "stdafx.h"

#include "NaGeBoundingBox.h"
#include "NaGePoint3D.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

NaGeBoundingBox::NaGeBoundingBox()
{

}

NaGeBoundingBox::NaGeBoundingBox(const double& xMin, const double& xMax, 
						   const double& yMin, const double& yMax, 
						   const double& zMin, const double& zMax) : itsXMax(xMax), itsXMin(xMin),
						   itsYMax(yMax), itsYMin(yMin),
						   itsZMax(zMax), itsZMin(zMin)
{
}

NaGeBoundingBox::~NaGeBoundingBox()
{

}

NaGePoint3D NaGeBoundingBox::Center() const
{
	NaGePoint3D P;
	P.SetX((XMax() + XMin())/2);
	P.SetY((YMax() + YMin())/2);
	P.SetZ((ZMax() + ZMin())/2);
	return P;
}

double NaGeBoundingBox::BoundingRadius() const
{
	double rad;
	NaGePoint3D Pmax(XMax(), YMax(), ZMax());
	NaGePoint3D Cen = Center();
	rad = Pmax.Distance(Cen);
	return rad;
}

void NaGeBoundingBox::SetLimits(const double& xMin, const double& xMax, 
						   const double& yMin, const double& yMax, 
						   const double& zMin, const double& zMax)
{
	itsXMax = xMax;
	itsXMin = xMin;
	itsYMax = yMax;
	itsYMin = yMin;
	itsZMax = zMax;
	itsZMin = zMin;
}

void NaGeBoundingBox::GetLimits(double& xMin, double& xMax,
						   double& yMin, double& yMax,
						   double& zMin, double& zMax)
{
	xMax = itsXMax;
	xMin = itsXMin;
	yMax = itsYMax;
	yMin = itsYMin;
	zMax = itsZMax;
	zMin = itsZMin;
}

bool NaGeBoundingBox::Contains(const NaGePoint3D& P) const
{
	bool bx = false, by = false, bz = false;
	bx = (P.GetX() <= XMax() && P.GetX() >= XMin());
	by = (P.GetY() <= YMax() && P.GetY() >= YMin());
	bz = (P.GetZ() <= ZMax() && P.GetZ() >= ZMin());

	return (bx && by &&bz);
}

void NaGeBoundingBox::AddBox(const NaGeBoundingBox& B)
{
	if(B.XMax() > XMax())
		itsXMax = B.XMax();
	if(B.XMin() < XMin())
		itsXMin = B.XMin();

	if(B.YMax() > YMax())
		itsYMax = B.YMax();
	if(B.YMin() < YMin())
		itsYMin = B.YMin();

	if(B.ZMax() > ZMax())
		itsZMax = B.ZMax();
	if(B.ZMin() < ZMin())
		itsZMin = B.ZMin();
}
