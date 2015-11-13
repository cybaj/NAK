// GLOneAxis.cpp: implementation of the NaDbOneAxis class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "NaDbOneAxis.h"
#include "NaGeMMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

NaDbOneAxis::NaDbOneAxis(const NaGeOneAxis& Ax, const int& length, const int& arrow) : itsAxis(Ax), 
															itsLength(length), itsArrow(arrow)
{
	glObjType = GLONEAXIS;
	glObjID = (int)glObjType + NaDbObject::GetCount();
	itsRed = 125;
	itsGreen = 125;
	itsBlue = 220;
	ComputeBoundLimits();
}

NaDbOneAxis::~NaDbOneAxis()
{

}

NaDbObject* NaDbOneAxis::Copy() 
{
	AddRef();
	return (NaDbObject*)this;
}

bool NaDbOneAxis::SaveObject(FILE* fptr)
{
	return false;
}

NaGeGeometry* NaDbOneAxis::Geometry() const
{
	NaGeOneAxis* Ax = new NaGeOneAxis(itsAxis.GetPosition(), itsAxis.GetDirection());
	return Ax;

}

void NaDbOneAxis::DefineDisplay()
{
	glDisable(GL_LIGHTING);
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_DEPTH_TEST);

	glColor3ub(itsRed, itsGreen, itsBlue);
	DrawArrow(itsAxis);
}

void NaDbOneAxis::Display(const GsDisplayMode&)
{
    DefineDisplay();
}

void NaDbOneAxis::Hilight(const GsDisplayMode&)
{
	
	itsRed = 0; itsGreen = 255; itsBlue = 255;
	DefineDisplay();
}

void NaDbOneAxis::ComputeBoundLimits()
{
	NaGePoint3D P1 = itsAxis.GetPosition();
	NaGePoint3D P2 = P1;
	P2.Translate(itsAxis, itsLength);
	itsBox.SetLimits(P1.GetX(), P2.GetX(), P1.GetY(), P2.GetY(), P1.GetZ(), P2.GetZ());
}

void NaDbOneAxis::DrawArrow(const NaGeOneAxis& theAxis)
{
	NaGePoint3D pos = theAxis.GetPosition();
	pos.Translate(theAxis, itsLength-(itsArrow/2));
	NaGeAxisSystem CordSys(pos, theAxis.GetDirection());
	int part=20;
	double step, uParam=0, vParam=0;
	step =2*PI/part;

	NaGeVector3D P, P1, P2;
	double R = itsArrow/3;

	vParam = itsArrow*2;

	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glDisable(GL_LIGHTING);

	glBegin(GL_TRIANGLE_FAN);

	double c = cos(uParam);
	double s = sin(uParam);
	P = CordSys.GetOrigin()+(CordSys.GetXDirection()*c+
					CordSys.GetYDirection()*s)*0+CordSys.GetDirection()*(vParam);

	glVertex3f(P.GetX(),P.GetY(),P.GetZ());

	vParam = 0;
	for(uParam=0; uParam<=2*PI+2; uParam+=step)
	{		

		double c = cos(uParam);
		double s = sin(uParam);
		P = CordSys.GetOrigin()+(CordSys.GetXDirection()*c+
				CordSys.GetYDirection()*s)*R+CordSys.GetDirection()*(vParam);

		glVertex3f(P.GetX(),P.GetY(),P.GetZ());
	}
	glEnd();

	NaGePoint3D O = theAxis.GetPosition();
	NaGePoint3D D = O;
	D.Translate(theAxis, itsLength);
	glBegin(GL_LINES);
		glVertex3d(O.GetX(), O.GetY(), O.GetZ());
		glVertex3d(D.GetX(), D.GetY(), D.GetZ());
	glEnd();
}
