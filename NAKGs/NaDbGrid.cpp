// GLGrid.cpp: implementation of the NaDbGrid class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "NaDbGrid.h"
#include "NaGeMMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

NaDbGrid::NaDbGrid()
{
    itsPlane = NaGePlane::XOY();
    itsSize = 10000;
    itsStep = 50;
    itsRed = 125;
    itsGreen = 125;
    itsBlue = 125;
    glObjID = 0;
    firstTime = true;
}

NaDbGrid::NaDbGrid(const NaGePlane& plane, const double& size, const double& step) : itsSize(size),
										itsStep(step),
										itsPlane(plane)
{
    itsRed = 255;
    itsGreen = 125;
    itsBlue = 125;
    glObjID = 0;
    firstTime = true;
}

NaDbGrid::~NaDbGrid()
{
    glDeleteLists(gridList, 1);
}
NaDbObject* NaDbGrid::Copy() 
{
	AddRef();
	return (NaDbObject*)this;
}

bool NaDbGrid::SaveObject(FILE* fptr)
{
	return false;
}

void NaDbGrid::SetPlane(const NaGePlane& plane)
{ 
    itsPlane = plane; 
    firstTime = true;
}

void NaDbGrid::SetSize(const double& size)
{
    itsSize = size;
    firstTime = true;
}

void NaDbGrid::SetStep(const double& step)
{
    itsStep = step;
    firstTime = true;
}

void NaDbGrid::DefineDisplay()
{
    if(firstTime)
    {
	InitDisplayLists();
	firstTime = false;
    }
    glCallList(gridList);
}

void NaDbGrid::InitDisplayLists()
{
    gridList = glGenLists(1);
    glNewList(gridList, GL_COMPILE);
    double size = itsSize;
    double step = itsStep;
    NaGePlane plane = itsPlane;

    glDisable(GL_LIGHTING);
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_DEPTH_TEST);
    glColor3ub(itsRed, itsGreen, itsBlue);

    double i;
    for(i = -size/2; i <= size/2; i += step)
    {
	NaGePoint3D P1 = plane.PointAtPara(i, -size/2);
	NaGePoint3D P2 = plane.PointAtPara(i, size/2);
	glBegin(GL_LINES);
	glVertex3d(P1.GetX(), P1.GetY(), P1.GetZ());
	glVertex3d(P2.GetX(), P2.GetY(), P2.GetZ());
	glEnd();
    }
    for(i = -size/2; i <= size/2; i += step)
    {
	NaGePoint3D P1 = plane.PointAtPara(-size/2, i);
	NaGePoint3D P2 = plane.PointAtPara(size/2, i);
	glBegin(GL_LINES);
	glVertex3d(P1.GetX(), P1.GetY(), P1.GetZ());
	glVertex3d(P2.GetX(), P2.GetY(), P2.GetZ());
	glEnd();
    }
    glEndList();
}

void NaDbGrid::Display(const GsDisplayMode& /*mode*/)
{
    DefineDisplay();
}

