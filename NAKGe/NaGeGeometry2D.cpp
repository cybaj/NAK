// Geometry.cpp: implementation of the NaGeGeometry class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "NaGeGeometry2D.h"
#include "NaGePoint2D.h"
#include "NaGeVector2D.h"
#include "NaGeOneAxis2D.h"
#include "NaGeMMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

int NaGeGeometry2D::refCount = 0;

NaGeGeometry2D::NaGeGeometry2D()
{
	refCount++;
}

NaGeGeometry2D::~NaGeGeometry2D()
{
	refCount--;
}

void NaGeGeometry2D::Translate(const NaGeOneAxis2D& Ax, const double& amt)
{
	NaGeVector2D D = Ax.GetDirection();
	double dx, dy;
	dx = D.GetX(); dy = D.GetY();
	dx *= amt; dy *= amt;
	Translate(dx,dy);
}

