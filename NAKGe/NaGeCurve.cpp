// Curve.cpp: implementation of the NaGeCurve class.
//
//////////////////////////////////////////////////////////////////////


#include "stdafx.h"

#include "NaGeCurve.h"
#include "NaGeMMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

NaGeCurve::NaGeCurve()
{
	cReversed = false;
	geomType = GECURVE;
}

NaGeCurve::~NaGeCurve()
{

}

CurveType NaGeCurve::Type() const
{
	return cType;
}

bool NaGeCurve::IsOfType(const CurveType& type) const
{
	CurveType typ = type;
	bool b = (cType == typ);
	return b;
}

