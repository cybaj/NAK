// GLTrihedron.cpp: implementation of the NaDbTrihedron class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "NaDbTrihedron.h"
#include "NaGeMMath.h"
#include "font.h"
#include <cstring>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

NaDbTrihedron::NaDbTrihedron()
{
    glObjType = GLTRIHEDRON;
    coneObj = gluNewQuadric();
    gluQuadricOrientation(coneObj, GLU_OUTSIDE);
    gluQuadricDrawStyle(coneObj,GLU_SILHOUETTE);
    firstTime = true;
    triList = 0;
    InitDisplayLists();
}

NaDbTrihedron::NaDbTrihedron(GLfloat size)
{
    glObjType = GLTRIHEDRON;
    coneObj = gluNewQuadric();
    gluQuadricOrientation(coneObj, GLU_OUTSIDE);
    gluQuadricDrawStyle(coneObj,GLU_SILHOUETTE);
    csSize = size;
    ComputeBoundLimits();
    glObjID = (int)glObjType + NaDbObject::GetCount();
    firstTime = true;
    triList = 0;
    InitDisplayLists();
}

NaDbTrihedron::~NaDbTrihedron()
{
	FontDestroy(Font);
    glDeleteLists(base, 96);
    glDeleteLists(triList, 1);
}

NaDbObject* NaDbTrihedron::Copy() 
{
	AddRef();
	return (NaDbObject*)this;
}

bool NaDbTrihedron::SaveObject(FILE* fptr)
{
	return false;
}

void NaDbTrihedron::DefineDisplay()
{
    glCallList(triList);
}

void NaDbTrihedron::InitDisplayLists()
{
    if(firstTime)
    {
		Font = FontCreate(wglGetCurrentDC(), "Monospace", 15, 0, 0);
		if(triList)
			glDeleteLists(triList, 1);
		triList = glGenLists(1);
		glNewList(triList, GL_COMPILE);
		firstTime = false;
    }
    glDisable(GL_LIGHTING);
    glDisable(GL_COLOR_MATERIAL);
    //glDisable(GL_DEPTH_TEST);

    //Axes' label
    glColor3f(1.0f, 1.0f, 0.0f);
    glRasterPos3d(0.5*csSize, 0, 0);
    DrawText("X");
    glRasterPos3d(0, 0.5*csSize, 0);
    DrawText("Y");
    glRasterPos3d(0, 0, 0.5*csSize);
    DrawText("Z");

    glColor3f(1.0f, 0, 0);
    //X Axis
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.8*csSize*0.5, 0.0f, 0.0f);
    glEnd();
    glPushMatrix();	
    glTranslatef(0.8*csSize*0.5, 0.0f, 0.0f);
    glRotatef(90.0f,0.0f,1.0f,0.0f);
    gluCylinder(coneObj,0.027*csSize,0,0.09*csSize,10,10);
    glPopMatrix();


    glColor3f(0, 1.0f, 0);
    //Y Axis
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.8*csSize*0.5, 0.0f);
    glEnd();
    glPushMatrix();	
    glTranslatef(0.0f, 0.8*csSize*0.5, 0.0f);
    glRotatef(-90.0f,1.0f,0.0f,0.0f);
    gluCylinder(coneObj,0.027*csSize,0,0.09*csSize,10,10);
    glPopMatrix();

    glColor3f(0, 0, 1.0f);
    //Z Axis
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.8*csSize*0.5);
    glEnd();
    glPushMatrix();	
    glTranslatef(0.0f, 0.0f, 0.8*csSize*0.5);
    gluCylinder(coneObj,0.027*csSize,0,0.09*csSize,10,10);
    glPopMatrix();

    glEndList();
}

void NaDbTrihedron::Display(const GsDisplayMode& /*dMode*/)
{
    DefineDisplay();
}

void NaDbTrihedron::Hilight(const GsDisplayMode& /*dMode*/)
{
}

void NaDbTrihedron::SetSize(GLfloat size)
{
    csSize = size;
    firstTime = true;
	FontDestroy(Font);
    InitDisplayLists();
}

void NaDbTrihedron::DrawText(char* text)
{
    FontPrintf(Font, 1, text);
}

void NaDbTrihedron::ComputeBoundLimits()
{
    itsBox.SetLimits(-csSize, csSize, -csSize, csSize, -csSize, csSize);
}
