// Curve.cpp: implementation of the NaGeCurve class.
//
//////////////////////////////////////////////////////////////////////


#include "stdafx.h"

#include "NaGeCurve2D.h"
#include "NaGeMMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

NaGeCurve2D::NaGeCurve2D()
{
	cReversed = false;
	geomType = GECURVE2D;
}

NaGeCurve2D::~NaGeCurve2D()
{

}

Curve2DType NaGeCurve2D::Type() const
{
	return cType;
}

bool NaGeCurve2D::IsOfType(const Curve2DType& type) const
{
	Curve2DType typ = type;
	bool b = (cType == typ);
	return b;
}

