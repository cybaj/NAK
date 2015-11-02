// Geometry.cpp: implementation of the NaGeGeometry class.
//
//////////////////////////////////////////////////////////////////////


#include "stdafx.h"

#include "NaGeGeometry.h"
#include "NaGePoint3D.h"
#include "NaGeVector3D.h"
#include "NaGeLine3D.h"
#include "NaGePlane.h"
#include "NaGeMMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

int NaGeGeometry::refCount = 0;

NaGeGeometry::NaGeGeometry()
{
	refCount++;
}

NaGeGeometry::~NaGeGeometry()
{
	refCount--;
}

void NaGeGeometry::Translate(const NaGeOneAxis& Ax, const double& amt)
{
	NaGeVector3D D = Ax.GetDirection();
	double dx, dy, dz;
	dx = D.GetX(); dy = D.GetY(); dz = D.GetZ();
	dx *= amt; dy *= amt; dz *= amt;
	Translate(dx,dy,dz);
}
