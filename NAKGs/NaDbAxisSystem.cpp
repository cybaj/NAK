// GLAxisSystem.cpp: implementation of the NaDbAxisSystem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "NaDbAxisSystem.h"
#include "NaGeMMath.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

NaDbAxisSystem::NaDbAxisSystem(const NaGeAxisSystem& Ax, const int& length, const int& arrow) : itsAxis(Ax), 
											   itsLength(length), itsArrow(arrow)
{
    glObjType = GLAXIS;
    glObjID = (int)glObjType + NaDbObject::GetCount();
    itsRed = 125;
    itsGreen = 125;
    itsBlue = 220;
    ComputeBoundLimits();
}

NaDbAxisSystem::~NaDbAxisSystem()
{

}


NaDbObject* NaDbAxisSystem::Copy()
{
	AddRef();
	return (NaDbObject*)this;
}


NaGeGeometry* NaDbAxisSystem::Geometry() const
{
    NaGeAxisSystem* Ax = new NaGeAxisSystem(itsAxis.GetPosition(), itsAxis.GetDirection());
    return Ax;
}

void NaDbAxisSystem::DefineDisplay()
{
    glDisable(GL_LIGHTING);
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_DEPTH_TEST);

    NaGeOneAxis zAx(itsAxis.GetPosition(), itsAxis.GetDirection());
    NaGeOneAxis xAx(itsAxis.GetPosition(), itsAxis.GetXDirection());
    NaGeOneAxis yAx(itsAxis.GetPosition(), itsAxis.GetYDirection());

    glColor3ub(itsRed, itsGreen, itsBlue);
    DrawArrow(xAx);
    DrawArrow(yAx);
    glColor3ub(itsRed, GLubyte((double)itsGreen/(double)1.5), GLubyte((double)itsBlue/(double)1.5));
    DrawArrow(zAx);
}

void NaDbAxisSystem::Display(const GsDisplayMode&)
{
    DefineDisplay();
}

void NaDbAxisSystem::Hilight(const GsDisplayMode&)
{	
    itsRed = 0; itsGreen = 255; itsBlue = 255;
    DefineDisplay();
}

void NaDbAxisSystem::ComputeBoundLimits()
{
    NaGePoint3D P = itsAxis.GetPosition();
    NaGePoint3D P1 = P, P2 = P, P3 = P;
    NaGeOneAxis zAx(itsAxis.GetPosition(), itsAxis.GetDirection());
    NaGeOneAxis xAx(itsAxis.GetPosition(), itsAxis.GetXDirection());
    NaGeOneAxis yAx(itsAxis.GetPosition(), itsAxis.GetYDirection());
    P1.Translate(xAx, itsLength);
    P2.Translate(yAx, itsLength);
    P3.Translate(zAx, itsLength);
    itsBox.SetLimits(P.GetX(), P1.GetX(), P.GetY(), P2.GetY(), P.GetZ(), P3.GetZ());
}

void NaDbAxisSystem::DrawArrow(const NaGeOneAxis& theAxis)
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

    glBegin(GL_TRIANGLE_FAN);

    double c = cos(uParam);
    double s = sin(uParam);
    P = CordSys.GetOrigin()+(CordSys.GetXDirection()*c+
	    CordSys.GetYDirection()*s)*0+CordSys.GetDirection()*(vParam);

    glVertex3d(P.GetX(),P.GetY(),P.GetZ());

    vParam = 0;
    for(uParam=0; uParam<=2*PI+2; uParam+=step)
    {		


	double c = cos(uParam);
	double s = sin(uParam);
	P = CordSys.GetOrigin()+(CordSys.GetXDirection()*c+
		CordSys.GetYDirection()*s)*R+CordSys.GetDirection()*(vParam);

	glVertex3d(P.GetX(),P.GetY(),P.GetZ());
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

