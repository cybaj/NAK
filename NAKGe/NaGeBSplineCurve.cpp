// BSplineCurve.cpp: implementation of the NaGeBSplineCurve class.
//
//////////////////////////////////////////////////////////////////////


#include "stdafx.h"

#include "NaGeBSplineCurve.h"
#include "NaGePoint3d.h"
#include "NaGeGeomException.h"

#include "NaGeBsp.h" //For The Actual BSpline Algorithm 
				 //Copyright 1994 by Keith Vertanen (vertankd@cda.mrs.umn.edu)
#include "NaGeMMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

NaGeBSplineCurve::NaGeBSplineCurve()
{
	cType = BSPLINE;
}

NaGeBSplineCurve::NaGeBSplineCurve(CListOfPoint3D *aList, const int& degree) : itsDegree(degree)
{
	cType = BSPLINE;
	NaGePoint3D curP;
	cpList = new CListOfPoint3D;
	cpCount = 0;
	CListIteratorOfListOfPoint3D myListIter(aList);
	for(myListIter.Init(); myListIter.More(); myListIter.Next())
	{
		curP = myListIter.Current();
		cpList->Append(curP);
		cpCount++;
	}
	if(itsDegree >= cpCount)
		itsDegree = cpCount-1;


	if(itsDegree > GetMaxDegree())
		throw NaGeGeomException(MaxDegree);
}

NaGeBSplineCurve::~NaGeBSplineCurve()
{
	cpList->Clear();
	if(cpList)
		delete cpList;
}

void NaGeBSplineCurve::Reverse()
{
	CListOfPoint3D *temp = new CListOfPoint3D;
	CListIteratorOfListOfPoint3D myListIter(cpList);

	for(myListIter.Init(); myListIter.More(); myListIter.Next())
		temp->Append(myListIter.Current());

	cpList->Clear();

	myListIter.SetList(temp);

	for(myListIter.Init(); myListIter.More(); myListIter.Next())
		cpList->Prepend(myListIter.Current());

	delete temp;
}

NaGePoint3D NaGeBSplineCurve::PointAtPara(const double& para)
{
	NaGePoint3D curP;
	NaGePoint3D P;
	point p;
	int cnt = 0;
	int* u;
	int n = cpCount-1;
	int t = itsDegree+1;
	point calcxyz;
	CListIteratorOfListOfPoint3D myListIter(cpList);

	if(para == FirstParameter())
	{
		P = cpList->First();
		return P;
	}


	if(para == LastParameter())
	{
		P = cpList->Last();
		return P;
	}

	u=new int[n+t+1];
	point *control = new point[n+1];

	for(myListIter.Init(); myListIter.More(); myListIter.Next())
	{
		curP = myListIter.Current();
		p.x = curP.GetX();
		p.y = curP.GetY();
		p.z = curP.GetZ();
		control[cnt] = p;
		cnt++;
	}

	compute_intervals(u, n, t);//Copyright 1994 by Keith Vertanen (vertankd@cda.mrs.umn.edu)
	compute_point(u, n, t, para, control, &calcxyz);//Copyright 1994 by Keith Vertanen (vertankd@cda.mrs.umn.edu)

    P.SetParam(calcxyz.x, calcxyz.y, calcxyz.z);
	delete u;
	delete [] control;
	return P;
}

double NaGeBSplineCurve::FirstParameter() const
{
	return 0.0;
}

double NaGeBSplineCurve::LastParameter() const
{
	int n = cpCount-1 ;
	int k = itsDegree+1;
	return (n-k+2);
}

bool NaGeBSplineCurve::IsClosed() const
{
	return false;
}

NaGeCurve* NaGeBSplineCurve::Copy() const
{
	NaGeBSplineCurve* C = new NaGeBSplineCurve(cpList, itsDegree);
	return C;
}

void NaGeBSplineCurve::Translate(const NaGeOneAxis& Ax, const double& amt)
{
	NaGeGeometry::Translate(Ax, amt);
}

void NaGeBSplineCurve::Translate(double dx, double dy, double dz)
{
	CListOfPoint3D *temp = new CListOfPoint3D;
	NaGePoint3D curP;
	CListIteratorOfListOfPoint3D myListIter(cpList);
	for(myListIter.Init(); myListIter.More(); myListIter.Next())
	{
		curP = myListIter.Current();
		curP.Translate(dx,dy,dz);
		temp->Append(curP);
	}
	cpList->Clear();
	myListIter.SetList(temp);
	for(myListIter.Init(); myListIter.More(); myListIter.Next())
		cpList->Append(myListIter.Current());
	delete temp;
}

void NaGeBSplineCurve::Translate(const NaGeVector3D& V)
{
	CListOfPoint3D *temp = new CListOfPoint3D;
	NaGePoint3D curP;
	CListIteratorOfListOfPoint3D myListIter(cpList);
	for(myListIter.Init(); myListIter.More(); myListIter.Next())
	{
		curP = myListIter.Current();
		curP.Translate(V);
		temp->Append(curP);
	}
	cpList->Clear();
	myListIter.SetList(temp);
	for(myListIter.Init(); myListIter.More(); myListIter.Next())
		cpList->Append(myListIter.Current());
	delete temp;
}

void NaGeBSplineCurve::Translate(const NaGePoint3D& P1, const NaGePoint3D& P2)
{
	CListOfPoint3D *temp = new CListOfPoint3D;
	NaGePoint3D curP;
	CListIteratorOfListOfPoint3D myListIter(cpList);
	for(myListIter.Init(); myListIter.More(); myListIter.Next())
	{
		curP = myListIter.Current();
		curP.Translate(P1, P2);
		temp->Append(curP);
	}
	cpList->Clear();
	myListIter.SetList(temp);
	for(myListIter.Init(); myListIter.More(); myListIter.Next())
		cpList->Append(myListIter.Current());
	delete temp;
}

void NaGeBSplineCurve::Rotate(const NaGeOneAxis& Ax, double ang)
{
	CListOfPoint3D *temp = new CListOfPoint3D;
	NaGePoint3D curP;
	CListIteratorOfListOfPoint3D myListIter(cpList);
	for(myListIter.Init(); myListIter.More(); myListIter.Next())
	{
		curP = myListIter.Current();
		curP.Rotate(Ax, ang);
		temp->Append(curP);
	}
	cpList->Clear();
	myListIter.SetList(temp);
	for(myListIter.Init(); myListIter.More(); myListIter.Next())
		cpList->Append(myListIter.Current());
	delete temp;
}

void NaGeBSplineCurve::Scale(const NaGePoint3D& P, double fact)
{
	CListOfPoint3D *temp = new CListOfPoint3D;
	NaGePoint3D curP;
	CListIteratorOfListOfPoint3D myListIter(cpList);
	for(myListIter.Init(); myListIter.More(); myListIter.Next())
	{
		curP = myListIter.Current();
		curP.Scale(P, fact);
		temp->Append(curP);
	}
	cpList->Clear();
	myListIter.SetList(temp);
	for(myListIter.Init(); myListIter.More(); myListIter.Next())
		cpList->Append(myListIter.Current());
	delete temp;
}

void NaGeBSplineCurve::Mirror(const NaGePoint3D& P)
{
	CListOfPoint3D *temp = new CListOfPoint3D;

	NaGePoint3D curP;
	CListIteratorOfListOfPoint3D myListIter(cpList);
	for(myListIter.Init(); myListIter.More(); myListIter.Next())
	{
		curP = myListIter.Current();
		curP.Mirror(P);
		temp->Append(curP);
	}
	cpList->Clear();
	myListIter.SetList(temp);
	for(myListIter.Init(); myListIter.More(); myListIter.Next())
		cpList->Append(myListIter.Current());
	delete temp;
}

void NaGeBSplineCurve::Mirror(const NaGeOneAxis& Ax)
{
	CListOfPoint3D *temp = new CListOfPoint3D;
	NaGePoint3D curP;
	CListIteratorOfListOfPoint3D myListIter(cpList);
	for(myListIter.Init(); myListIter.More(); myListIter.Next())
	{
		curP = myListIter.Current();
		curP.Mirror(Ax);
		temp->Append(curP);
	}
	cpList->Clear();
	myListIter.SetList(temp);
	for(myListIter.Init(); myListIter.More(); myListIter.Next())
		cpList->Append(myListIter.Current());
	delete temp;
}

void NaGeBSplineCurve::Mirror(const NaGePlane& Pln)
{
	CListOfPoint3D *temp = new CListOfPoint3D;
	NaGePoint3D curP;
	CListIteratorOfListOfPoint3D myListIter(cpList);
	for(myListIter.Init(); myListIter.More(); myListIter.Next())
	{
		curP = myListIter.Current();
		curP.Mirror(Pln);
		temp->Append(curP);
	}
	cpList->Clear();
	myListIter.SetList(temp);
	for(myListIter.Init(); myListIter.More(); myListIter.Next())
		cpList->Append(myListIter.Current());
	delete temp;
}

