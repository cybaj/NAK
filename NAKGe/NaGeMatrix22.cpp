// Matrix22.cpp: implementation of the NaGeMatrix22 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "NaGeMatrix22.h"
#include "NaGePoint2D.h"
#include "NaGeVector2D.h"
#include "NaGeGeomException.h"
#include "NaGeMMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//Implementation of NaGeMatrix22 class
NaGeMatrix22::NaGeMatrix22()
{
    int i,j;
    for(i=0;i<2;i++)
    {
	for(j=0;j<2;j++)
	{
	    Row[i][j]=0;
	}
    }
}

NaGeMatrix22::NaGeMatrix22(double R1[2], double R2[2])
{
    int i;
    for(i=0;i<2;i++)
    {
	Row[0][i]=R1[i];
    }
    for(i=0;i<2;i++)
    {
	Row[1][i]=R2[i];
    }
}

NaGeMatrix22::~NaGeMatrix22()
{
}

NaGeMatrix22 NaGeMatrix22::operator*(const NaGeMatrix22 &Other)
{
    int i,j,k;
    NaGeMatrix22 New;
    double temp[2][2];
    for(i=0;i<2;i++)
    {
	for(j=0;j<2;j++)
	{
	    temp[i][j]=0;
	}
    }

    for(i=0;i<2;i++)
    {
	for(j=0;j<2;j++)
	{
	    for(k=0;k<2;k++)
	    {
		temp[i][j]=temp[i][j]+Row[i][k]*Other.Row[k][j];
	    }
	}
    }
    for(i=0;i<2;i++)
    {
	for(j=0;j<2;j++)
	{
	    New.Row[i][j]=temp[i][j];
	}
    }
    return New;
}

NaGeVector2D NaGeMatrix22::operator*(const NaGeVector2D &Other)
{
    NaGeVector2D O = Other;
    NaGeVector2D Result;

    Result.SetX(this->Row[0][0]*O.GetX() + this->Row[0][1]*O.GetY());
    Result.SetY(this->Row[1][0]*O.GetX() + this->Row[1][1]*O.GetY());

    return Result;
}

NaGeMatrix22 NaGeMatrix22::operator*(double value)
{
    NaGeMatrix22 New;
    int i,j;
    for(i=0;i<2;i++)
    {
	for(j=0;j<2;j++)
	{
	    New.Row[i][j]=Row[i][j];
	}
    }
    for(i=0;i<2;i++)
    {
	for(j=0;j<2;j++)
	{
	    New.Row[i][j]*=value;
	}
    }
    return New;
}

void NaGeMatrix22::operator*=(const NaGeMatrix22 &Other)
{
    int i,j,k;
    double temp[2][2];
    for(i=0;i<2;i++)
    {
	for(j=0;j<2;j++)
	{
	    temp[i][j]=0;
	}
    }
    for(i=0;i<2;i++)
    {
	for(j=0;j<2;j++)
	{
	    for(k=0;k<2;k++)
	    {
		temp[i][j]=temp[i][j]+Row[i][k]*Other.Row[k][j];
	    }
	}
    }
    for(i=0;i<2;i++)
    {
	for(j=0;j<2;j++)
	{
	    Row[i][j]=temp[i][j];
	}
    }
}

void NaGeMatrix22::operator*=(double value)
{
    int i, j;
    for(i=0;i<2;i++)
    {
	for(j=0;j<2;j++)
	{
	    Row[i][j]*=value;
	}
    }
}

NaGeMatrix22 NaGeMatrix22::operator/(const double Value)
{
    NaGeMatrix22 New;
    int i,j;
    for(i=0;i<2;i++)
    {
	for(j=0;j<2;j++)
	{
	    New.Row[i][j]=Row[i][j];
	}
    }
    for(i=0;i<2;i++)
    {
	for(j=0;j<2;j++)
	{
	    New.Row[i][j]/=Value;
	}
    }
    return New;
}

void NaGeMatrix22::operator/=(const double Value)
{
    int i,j;
    for(i=0;i<2;i++)
    {
	for(j=0;j<2;j++)
	{
	    Row[i][j]/=Value;
	}
    }
}

NaGeMatrix22 NaGeMatrix22::operator+(const NaGeMatrix22 &Other)
{
    NaGeMatrix22 New;
    int i,j;
    for(i=0;i<2;i++)
    {
	for(j=0;j<2;j++)
	{
	    New.Row[i][j]=Row[i][j];
	}
    }
    for(i=0;i<2;i++)
    {
	for(j=0;j<2;j++)
	{
	    New.Row[i][j]+=Other.Row[i][j];
	}
    }
    return New;
}

void NaGeMatrix22::operator+=(const NaGeMatrix22 &Other)
{
    int i, j;
    for(i=0;i<2;i++)
    {
	for(j=0;j<2;j++)
	{
	    Row[i][j]+=Other.Row[i][j];
	}
    }
}

NaGeMatrix22 NaGeMatrix22::operator-(const NaGeMatrix22 &Other)
{
    NaGeMatrix22 New;
    int i,j;
    for(i=0;i<2;i++)
    {
	for(j=0;j<2;j++)
	{
	    New.Row[i][j]=Row[i][j];
	}
    }
    for(i=0;i<2;i++)
    {
	for(j=0;j<2;j++)

	{
	    New.Row[i][j]-=Other.Row[i][j];

	}
    }
    return New;
}

void NaGeMatrix22::operator-=(const NaGeMatrix22 &Other)
{
    int i, j;
    for(i=0;i<2;i++)
    {
	for(j=0;j<2;j++)
	{
	    Row[i][j]-=Other.Row[i][j];
	}
    }
}

double NaGeMatrix22::Determinant()
{
    double D;
    D=(Row[0][0]*(Row[1][1] - Row[0][1]*Row[1][0]));
    return D;
}

void NaGeMatrix22::Invert()
{
    NaGeMatrix22 tmpNaGeMatrix22;
    if(Determinant()==0)
	throw NaGeGeomException(DivideByZero);
    tmpNaGeMatrix22=Adjoint()/Determinant();
    int i, j;
    for(i=0;i<2;i++)
    {
	for(j=0;j<2;j++)
	{
	    Row[i][j]=tmpNaGeMatrix22.Row[i][j];
	}
    }
}

NaGeMatrix22 NaGeMatrix22::Inverted() const
{
    NaGeMatrix22 tmpNaGeMatrix22;
    tmpNaGeMatrix22.Invert();
    return tmpNaGeMatrix22;
}

void NaGeMatrix22::Transpose()
{
    double temp[2][2];
    int i, j;
    for(i=0;i<2;i++)
    {
	for(j=0;j<2;j++)
	{
	    temp[i][j]=Row[j][i];
	}
    }
    for(i=0;i<2;i++)
    {
	for(j=0;j<2;j++)
	{
	    Row[i][j]=temp[i][j];
	}
    }
}

void NaGeMatrix22::Value() const
{
    int i,j;
    for(i=0;i<2;i++)
    {
	for(j=0;j<2;j++)
	{
	    cout<<" "<<Row[i][j];
	}
	cout<<"\n";
    }
    cout<<"\n";
}

bool NaGeMatrix22::IsNull() const
{
    int i,j,flag=0;
    for(i=0;i<2;i++)
    {
	for(j=0;j<2;j++)
	{
	    if(Row[i][j]!=0)
	    {
		flag=1;
		break;
	    }
	}
    }
    if(flag==1)
	return false;
    return true;
}

bool NaGeMatrix22::IsDiagonal() const
{
    if(Row[0][0]==0&&Row[1][1]==0)
	return true;
    return false;
}

bool NaGeMatrix22::IsSymmetrical() const
{
    int i,j,flag=0;
    for(i=0;i<2;i++)
    {
	for(j=0;j<2;j++)
	{
	    if(Row[j][i] != Row[i][j])
	    {
		flag=1;
		break;
	    }
	}
    }
    if(flag==1)
	return false;
    return true;
}

bool NaGeMatrix22::IsScalar() const
{
    if(Row[0][0]==Row[1][1])
	return true;
    return false;
}

bool NaGeMatrix22::IsIdentity() const
{
    if(Row[0][0]==1 && Row[1][1]==1 && Row[0][1]==0 && Row[1][0]==0)
	return true;
    return false;
}

bool NaGeMatrix22::IsEqual(const NaGeMatrix22 &Other) const
{
    int i,j,flag=0;
    for(i=0;i<2;i++)
    {
	for(j=0;j<2;j++)
	{
	    if(Row[i][j] != Other.Row[i][j])
	    {
		flag=1;
		break;
	    }
	}

    }
    if(flag==1)
	return false;
    return true;
}

NaGeMatrix22 NaGeMatrix22::Adjoint()
{
    NaGeMatrix22 tmpNaGeMatrix22;
    Transpose();
    //A11
    tmpNaGeMatrix22.Row[0][0] =  1*(Row[1][1]);
    //B12
    tmpNaGeMatrix22.Row[0][1] = -1*(Row[1][0]);
    //A21
    tmpNaGeMatrix22.Row[1][0]=   1*(Row[0][1]);
    //B22
    tmpNaGeMatrix22.Row[1][1] = -1*(Row[0][0]);
    Transpose();
    return tmpNaGeMatrix22;
}

void NaGeMatrix22::SetIdentity()
{
    //Identity Matrix
    double Row1[2]={1,0};
    double Row2[2]={0,1};
    NaGeMatrix22 M(Row1, Row2);
    *this = M;
}

void NaGeMatrix22::SetRotation(double t)
{

    /*double nx, ny, nz;
    nx = Axis.GetX(); ny = Axis.GetY(); nz = Axis.GetZ();
    double Row1[3]={ nx*nx*vsin(t)+cos(t), nx*ny*vsin(t)-nz*sin(t), nx*nz*vsin(t)+ny*sin(t)};
    double Row2[3]={ nx*ny*vsin(t)+nz*sin(t), ny*ny*vsin(t)+cos(t), ny*nz*vsin(t)-nx*sin(t)};
    double Row3[3]={ nx*nz*vsin(t)-ny*sin(t), ny*nz*vsin(t)+nx*sin(t), nz*nz*vsin(t)+cos(t)};
    NaGeMatrix22 M(Row1, Row2, Row3);
    *this = M;*/
    double Row1[2]={cos(t), -1*sin(t)};
    double Row2[2]={sin(t), cos(t)};
    NaGeMatrix22 M(Row1, Row2);
    *this = M;
}

void NaGeMatrix22::SetScale(const NaGePoint2D& Point)
{
    NaGePoint2D P = Point;
    double Row1[2]={P.GetX(),          0};
    double Row2[2]={0       ,   P.GetY()};
    NaGeMatrix22 M(Row1, Row2);
    *this = M;
}

NaGePoint2D NaGeMatrix22::GetDiagonal() const
{
    NaGePoint2D V;
    NaGeMatrix22 M = *this;
    V.SetX(M(0,0));
    V.SetY(M(1,1));
    return V;
}
