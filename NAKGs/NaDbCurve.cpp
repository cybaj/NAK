// GLCurve.cpp: implementation of the NaDbCurve class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "NaDbCurve.h"
#include "NaGeMMath.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

NaDbCurve::NaDbCurve(const NaGeCurve* crv , const GsLineStyle& lt) : lineStyle(lt)
{
	pCurve = crv->Copy();
	glObjType = GLCURVE;
	glObjID = (int)glObjType + NaDbObject::GetCount();

	SMOOTH = 1000;

	itsRed = 255;
	itsGreen = 0;
	itsBlue = 255;

	pointList = new CListOfPoint3D;
	ComputePoints();
	ComputeBoundLimits();

	listNum = 1;
}

NaDbCurve::~NaDbCurve()
{
	if(pointList)
	{
		pointList->Clear();
		delete pointList;
	}
	delete pCurve;
}

NaDbObject* NaDbCurve::Copy()
{
	AddRef();
	return (NaDbObject*)this;
}

bool NaDbCurve::SaveObject(FILE* fptr)
{
	return false;
}

NaGeGeometry* NaDbCurve::Geometry() const
{
	NaGeCurve* crv = pCurve->Copy();
	return crv;
}

void NaDbCurve::DefineDisplay()
{
	NaGePoint3D curP;
	CListIteratorOfListOfPoint3D myListIter(pointList);

	glDisable(GL_LIGHTING);
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_DEPTH_TEST);

	glColor3ub(itsRed, itsGreen, itsBlue);

	if(lineStyle == LINE_SOLID)
		glDisable(GL_LINE_STIPPLE);
	else
		glEnable(GL_LINE_STIPPLE);

	if(lineStyle == LINE_DOTTED)
		glLineStipple (1, 0x0101);  /*  dotted  */
	if(lineStyle == LINE_DASHED)
		glLineStipple (1, 0x00FF);  /*  dashed  */
	if(lineStyle == LINE_DASHDOTTED)
		glLineStipple (2, 0x1C47);  /*  dash/dot/dash  */

	glBegin(GL_LINE_STRIP);		//LINE_STRIP So that it will be common for Open and Closed Curves
	for(myListIter.Init(); myListIter.More(); myListIter.Next())
	{
		curP = myListIter.Current();
		glVertex3d(curP.GetX(), curP.GetY(), curP.GetZ());
	}
	glEnd();

	glDisable(GL_LINE_STIPPLE);
}

void NaDbCurve::Display(const GsDisplayMode&)
{
	DefineDisplay();
}

void NaDbCurve::Hilight(const GsDisplayMode&)
{
	itsRed = 0; itsGreen = 255; itsBlue = 255;
	DefineDisplay();
}

void NaDbCurve::SetSmooth(const double& sm)
{
	SMOOTH = sm;
	ComputePoints();
	ComputeBoundLimits();
	DefineDisplay();
}

void NaDbCurve::SetCurve(const NaGeCurve* crv)
{
	pCurve = crv->Copy();
	ComputePoints();
	ComputeBoundLimits();
}

void NaDbCurve::ComputePoints()
{
	NaGePoint3D sP, eP, curP;
	double parts , step;
	double fPar, lPar;

	fPar = pCurve->FirstParameter();
	lPar = pCurve->LastParameter();

	parts = SMOOTH/10;

	step = fabs(lPar-fPar)/parts;

	sP = pCurve->PointAtPara(fPar);

	if(pCurve->IsClosed())
		eP = sP;
	else
		eP = pCurve->PointAtPara(lPar);

	if(!pointList->IsEmpty())
		pointList->Clear();

	if(pCurve->IsOfType(LINE))
	{
		pointList->Append(sP);
		pointList->Append(eP);
	}
	else
	{
		for(double i = fPar; i < lPar; i += step)
		{
			curP = pCurve->PointAtPara(i);
			pointList->Append(curP);
		}
		pointList->Append(eP);//To Ensure Closure If Curve Is Closed
	}
}

void NaDbCurve::ComputeBoundLimits()
{
	/*
	double lx=0,ly=0,lz=0,sx=0,sy=0,sz=0;
	NaGePoint3D P;
	QList<double> pxArray, pyArray, pzArray;
	pxArray.setAutoDelete(TRUE);
	pyArray.setAutoDelete(TRUE);
	pzArray.setAutoDelete(TRUE);
	
	CListIteratorOfListOfPoint3D myListIter(pointList);
	for(myListIter.Init(); myListIter.More(); myListIter.Next())
	{
		double *x = new double, *y = new double, *z = new double;
		*x = P.GetX(); *y = P.GetY(); *z = P.GetZ();
		pxArray.append(x);
		pyArray.append(y);
		pzArray.append(z);
	}
	pxArray.sort();
	pyArray.sort();
	pzArray.sort();
	sx = *pxArray.first();  lx = *pxArray.last();
	sy = *pyArray.first();  ly = *pyArray.last();
	sz = *pzArray.first();  lz = *pzArray.last();
	itsBox.SetLimits(sx,lx,sy,ly,sz,lz);
	*/
}
