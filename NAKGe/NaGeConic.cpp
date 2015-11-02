// Conic.cpp: implementation of the NaGeConic class.
//
//////////////////////////////////////////////////////////////////////


#include "stdafx.h"

#include "NaGeConic.h"
#include "NaGeMMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

NaGeConic::NaGeConic()
{

}

NaGeConic::~NaGeConic()
{

}

void NaGeConic::Reverse()
{
	NaGeVector3D V = itsLocation.GetDirection();
	V *= -1;
	itsLocation.SetDirection(V);
}

void NaGeConic::SetLocation(const NaGeAxisSystem& ax)
{
	itsLocation = ax;
}

