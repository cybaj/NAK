// GLPlane.cpp: implementation of the NaDbPlane class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "NaDbPlane.h"
#include "NaGeMMath.h"
#include "ListOfPoint3D.h"
#include "ListIteratorOfListOfPoint3D.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

NaDbPlane::NaDbPlane(const NaGePlane& P, const double& length, const double& width) : itsPlane(P), uSize(length), vSize(width)
{
    glObjType = GLPLANE;
    glObjID = (int)glObjType + NaDbObject::GetCount();

    itsMaterial.SetName(PEARL);
    itsShadeRed = 155;
    itsShadeGreen = 155;
    itsShadeBlue = 155;

    itsRed = 225;
    itsGreen = 225;
    itsBlue = 0;

    ComputeBoundLimits();
}

NaDbPlane::~NaDbPlane()
{
}

NaDbObject* NaDbPlane::Copy() 
{
	AddRef();
	return (NaDbObject*)this;
}

NaGeGeometry* NaDbPlane::Geometry() const
{
    NaGeVector3D Dir = itsPlane.GetDirection();
    double Const = itsPlane.GetConstant();
    NaGePlane* pln = new NaGePlane(Dir.GetX(), Dir.GetY(), Dir.GetZ(), Const);
    return pln;
}

void NaDbPlane::DefineDisplay()
{
    NaGePoint3D sP1, sP2, eP1, eP2;
    double uPar = uSize/2;
    double vPar = vSize/2;
    sP1 = itsPlane.PointAtPara(-uPar, -vPar);
    eP1 = itsPlane.PointAtPara(uPar, -vPar);
    sP2 = itsPlane.PointAtPara(-uPar, vPar);
    eP2 = itsPlane.PointAtPara(uPar, vPar);

    NaGeVector3D O(sP1), OX(eP1), OY(sP2);
    NaGeVector3D X(O, OX), Y(O, OY);
    NaGeVector3D N = X^Y;
    N.Normalize();

    if(displayMode == GLWIREFRAME || displayMode == GLHLREMOVED)
    {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		glDisable(GL_LIGHTING);
		glDisable(GL_COLOR_MATERIAL);
		glDisable(GL_DEPTH_TEST);

		glColor3ub(itsRed, itsGreen, itsBlue);
    }

    else if(displayMode == GLSHADED)
    {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		GLfloat  specref[] =  { 1.0f, 1.0f, 1.0f, 1.0f };	

		ApplyMaterial();

		// Enable Depth Testing
		glEnable(GL_DEPTH_TEST);


		glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
		// Enable lighting
		glEnable(GL_LIGHTING);

		// Enable color tracking
		glEnable(GL_COLOR_MATERIAL);

		// Set Material properties to follow glColor values
		glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,specref);
		glMateriali(GL_FRONT_AND_BACK,GL_SHININESS,128);

		glShadeModel(GL_SMOOTH);

		glEnable(GL_AUTO_NORMAL);
		glEnable(GL_NORMALIZE);

		glColor3ub(itsShadeRed, itsShadeGreen, itsShadeBlue);
    }

    glBegin(GL_QUADS);
    glNormal3d(N.GetX(), N.GetY(), N.GetZ());
    glVertex3d(sP1.GetX(), sP1.GetY(), sP1.GetZ());
    glVertex3d(eP1.GetX(), eP1.GetY(), eP1.GetZ());
    glVertex3d(eP2.GetX(), eP2.GetY(), eP2.GetZ());
    glVertex3d(sP2.GetX(), sP2.GetY(), sP2.GetZ());
    glEnd();
}

void NaDbPlane::Display(const GsDisplayMode& dMode)
{
    displayMode = dMode;
    DefineDisplay();
}

void NaDbPlane::Hilight(const GsDisplayMode&)
{
    displayMode = GLWIREFRAME;
    itsRed = 0; itsGreen = 255; itsBlue = 255;
    DefineDisplay();
}

void NaDbPlane::SetColor(const GLubyte& red, const GLubyte& green, const GLubyte& blue)
{
    if(displayMode == GLWIREFRAME)
    {
		itsRed = red;
		itsGreen = green;
		itsBlue = blue;
    }
    else
    {
		itsShadeRed = red;
		itsShadeGreen = green;
		itsShadeBlue = blue;
    }
    DefineDisplay();
}


void NaDbPlane::GetColor(GLubyte* colVect) const
{
    colVect = new GLubyte[3];
    if(displayMode == GLWIREFRAME)
    {
		colVect[0] = itsRed;
		colVect[1] = itsGreen;
		colVect[2] = itsBlue;
    }
    else
    {
		colVect[0] = itsShadeRed;
		colVect[1] = itsShadeGreen;
		colVect[2] = itsShadeBlue;
    }
}

void NaDbPlane::ComputeBoundLimits()
{
    /*
    NaGePoint3D sP1, sP2, eP1, eP2;
    double uPar = uSize/2;
    double vPar = vSize/2;
    sP1 = itsPlane.PointAtPara(-uPar, -vPar);
    eP1 = itsPlane.PointAtPara(uPar, -vPar);
    sP2 = itsPlane.PointAtPara(-uPar, vPar);
    eP2 = itsPlane.PointAtPara(uPar, vPar);

    CListOfPoint3D *pointList = new CListOfPoint3D;

    pointList->Append(sP1);
    pointList->Append(eP1);
    pointList->Append(sP2);
    pointList->Append(eP2);

    double lx=0,ly=0,lz=0,sx=0,sy=0,sz=0;
    NaGePoint3D P;
    QList<double> pxArray, pyArray, pzArray;
    pxArray.setAutoDelete(TRUE);
    pyArray.setAutoDelete(TRUE);
    pzArray.setAutoDelete(TRUE);

    CListIteratorOfListOfPoint3D myListIter(pointList);
    for(myListIter.Init(); myListIter.More(); myListIter.Next())
    {
	P = myListIter.Current();	
	double *x = new double, *y = new double, *z = new double;
	*x = P.GetX(); *y = P.GetY(); *z = P.GetZ();
	pxArray.append(x);
	pyArray.append(y);
	pzArray.append(z);
    }
    delete pointList;
    pxArray.sort();
    pyArray.sort();
    pzArray.sort();

    sx = *pxArray.first();  lx = *pxArray.last();
    sy = *pyArray.first();  ly = *pyArray.last();
    sz = *pzArray.first();  lz = *pzArray.last();

    itsBox.SetLimits(sx,lx,sy,ly,sz,lz);
    */
}
