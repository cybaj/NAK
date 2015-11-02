// BezierCurve.cpp: implementation of the NaGeBezierCurve class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "NaGeBezierCurve.h"
#include "NaGePoint3D.h"
#include "NaGeGeomException.h"
#include "NaGeMMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

NaGeBezierCurve::NaGeBezierCurve()
{
    cType = BEZIER;
}

NaGeBezierCurve::NaGeBezierCurve(CListOfPoint3D *aList)
{
    cType = BEZIER;
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
    if(cpCount > GetMaxDegree())
	throw NaGeGeomException(MaxDegree);
}

NaGeBezierCurve::~NaGeBezierCurve()
{
    cpList->Clear();
    if(cpList)
	delete cpList;
}

void NaGeBezierCurve::Reverse()
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

NaGePoint3D NaGeBezierCurve::PointAtPara(const double& para)
{
    NaGePoint3D P;
    int cnt = 0;
    double x=0, y=0, z=0;
    double degree = cpCount-1;
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

    for(myListIter.Init(); myListIter.More(); myListIter.Next(), cnt++)
    {
	x+=myListIter.Current().GetX()*BlendingFunc((int)degree,cnt,para);
	y+=myListIter.Current().GetY()*BlendingFunc((int)degree,cnt,para);
	z+=myListIter.Current().GetZ()*BlendingFunc((int)degree,cnt,para);
    }
    P.SetParam(x,y,z);
    return P;
}

double NaGeBezierCurve::FirstParameter() const
{
    return 0.0;
}

double NaGeBezierCurve::LastParameter() const
{
    return 1.0;
}

bool NaGeBezierCurve::IsClosed() const
{
    return false;
}

NaGeCurve* NaGeBezierCurve::Copy() const
{
    NaGeBezierCurve* C = new NaGeBezierCurve(cpList);
    return C;
}

void NaGeBezierCurve::Translate(const NaGeOneAxis& Ax, const double& amt)
{
    NaGeGeometry::Translate(Ax, amt);
}

void NaGeBezierCurve::Translate(double dx, double dy, double dz)
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


void NaGeBezierCurve::Translate(const NaGeVector3D& V)
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

void NaGeBezierCurve::Translate(const NaGePoint3D& P1, const NaGePoint3D& P2)
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

void NaGeBezierCurve::Rotate(const NaGeOneAxis& Ax, double ang)
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

void NaGeBezierCurve::Scale(const NaGePoint3D& P, double fact)
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

void NaGeBezierCurve::Mirror(const NaGePoint3D& P)
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

void NaGeBezierCurve::Mirror(const NaGeOneAxis& Ax)
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

void NaGeBezierCurve::Mirror(const NaGePlane& Pln)
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

double NaGeBezierCurve::BlendingFunc(int n,int r,float t)
{
    long int p=1,m=1;
    int i;
    if(t<1e-5)
	return  (r==0 ?  1.0 : 0.0);
    if(t>.999995)
	return (r==n ? 1.0 : 0.0) ;

    for(i=1;i<=r;i++)
    {
	m*=i;
	p*=(n-i+1);
    }
    return ((double)(p/m))*pow(t,r)*pow(1.0-t,n-r);
}

