// Matrix33.cpp: implementation of the NaGeMatrix33 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "NaGeMatrix33.h"
#include "NaGePoint3D.h"
#include "NaGeVector3D.h"
#include "NaGeGeomException.h"
#include "NaGeMMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//Implementation of NaGeMatrix33 class
NaGeMatrix33::NaGeMatrix33()
{
	int i,j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			Row[i][j]=0;
		}
	}
}

NaGeMatrix33::NaGeMatrix33(double R1[3], double R2[3], double R3[3])
{
	int i;
	for(i=0;i<3;i++)
	{
		Row[0][i]=R1[i];
	}
    for(i=0;i<3;i++)
	{
		Row[1][i]=R2[i];
	}
	for(i=0;i<3;i++)
	{
		Row[2][i]=R3[i];
	}
}

NaGeMatrix33::~NaGeMatrix33()
{
}

NaGeMatrix33 NaGeMatrix33::operator*(const NaGeMatrix33 &Other)
{
	int i,j,k;
	NaGeMatrix33 New;
	double temp[3][3];
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			temp[i][j]=0;
		}
	}


	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			for(k=0;k<3;k++)
			{
				temp[i][j]=temp[i][j]+Row[i][k]*Other.Row[k][j];
			}
		}
	}
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			New.Row[i][j]=temp[i][j];
		}
	}
	return New;
}

NaGeVector3D NaGeMatrix33::operator*(const NaGeVector3D &Other)
{
	NaGeVector3D O = Other;
	NaGeVector3D Result;

	Result.SetX(this->Row[0][0]*O.GetX() + this->Row[0][1]*O.GetY() + this->Row[0][2]*O.GetZ());
	Result.SetY(this->Row[1][0]*O.GetX() + this->Row[1][1]*O.GetY() + this->Row[1][2]*O.GetZ());
	Result.SetZ(this->Row[2][0]*O.GetX() + this->Row[2][1]*O.GetY() + this->Row[2][2]*O.GetZ());

	return Result;
}

NaGeMatrix33 NaGeMatrix33::operator*(double value)
{
	NaGeMatrix33 New;
	int i,j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			New.Row[i][j]=Row[i][j];
		}
	}
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			New.Row[i][j]*=value;
		}
	}
	return New;
}

void NaGeMatrix33::operator*=(const NaGeMatrix33 &Other)
{
	int i,j,k;
	double temp[3][3];
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			temp[i][j]=0;
		}
	}
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			for(k=0;k<3;k++)
			{
				temp[i][j]=temp[i][j]+Row[i][k]*Other.Row[k][j];
			}
		}
	}
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			Row[i][j]=temp[i][j];
		}
	}
}

void NaGeMatrix33::operator*=(double value)
{
	int i, j;
    for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			Row[i][j]*=value;
		}
	}
}

NaGeMatrix33 NaGeMatrix33::operator/(const double Value)
{
	NaGeMatrix33 New;
	int i,j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			New.Row[i][j]=Row[i][j];
		}
	}
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			New.Row[i][j]/=Value;
		}
	}
	return New;
}

void NaGeMatrix33::operator/=(const double Value)
{
	int i,j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			Row[i][j]/=Value;
		}
	}
}

NaGeMatrix33 NaGeMatrix33::operator+(const NaGeMatrix33 &Other)
{
	NaGeMatrix33 New;
	int i,j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			New.Row[i][j]=Row[i][j];
		}
	}
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			New.Row[i][j]+=Other.Row[i][j];
		}
	}
	return New;
}

void NaGeMatrix33::operator+=(const NaGeMatrix33 &Other)
{
	int i, j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			Row[i][j]+=Other.Row[i][j];
		}
	}
}

NaGeMatrix33 NaGeMatrix33::operator-(const NaGeMatrix33 &Other)
{
	NaGeMatrix33 New;
	int i,j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			New.Row[i][j]=Row[i][j];
		}
	}
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)

		{
			New.Row[i][j]-=Other.Row[i][j];

		}
	}
	return New;
}

void NaGeMatrix33::operator-=(const NaGeMatrix33 &Other)
{
	int i, j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			Row[i][j]-=Other.Row[i][j];
		}
	}
}

double NaGeMatrix33::Determinant()
{
	double D;
	D=(Row[0][0]*(Row[1][1]*Row[2][2]-Row[2][1]*Row[1][2]))
		-(Row[0][1]*(Row[1][0]*Row[2][2]-Row[2][0]*Row[1][2]))
		+(Row[0][2]*(Row[1][0]*Row[2][1]-Row[2][0]*Row[1][1]));
	return D;
}

void NaGeMatrix33::Invert()
{
	NaGeMatrix33 tmpNaGeMatrix33;
	if(Determinant()==0)
		throw NaGeGeomException(DivideByZero);
	tmpNaGeMatrix33=Adjoint()/Determinant();
	int i, j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			Row[i][j]=tmpNaGeMatrix33.Row[i][j];
		}
	}
}

NaGeMatrix33 NaGeMatrix33::Inverted() const
{
	NaGeMatrix33 tmpNaGeMatrix33;
	tmpNaGeMatrix33.Invert();
	return tmpNaGeMatrix33;
}

void NaGeMatrix33::Transpose()
{
	double temp[3][3];
	int i, j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			temp[i][j]=Row[j][i];
		}
	}
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			Row[i][j]=temp[i][j];
		}
	}
}

void NaGeMatrix33::Value() const
{
	int i,j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			cout<<" "<<Row[i][j];
		}
		cout<<"\n";
	}
	cout<<"\n";
}

bool NaGeMatrix33::IsNull() const
{
	int i,j,flag=0;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
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

bool NaGeMatrix33::IsDiagonal() const
{
	if(Row[1][0]==0&&Row[2][0]==0&&Row[2][1]==0
		&&Row[0][1]==0&&Row[0][2]==0&&Row[1][2]==0)
		return true;
	return false;
}

bool NaGeMatrix33::IsSymmetrical() const
{
	int i,j,flag=0;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
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

bool NaGeMatrix33::IsScalar() const
{
	if(Row[0][0]==Row[1][1] && Row[1][1]==Row[2][2]
		 && Row[0][0]==Row[2][2])
		return true;
	return false;
}

bool NaGeMatrix33::IsIdentity() const
{
	if(Row[0][0]==1&&Row[1][1]==1&&Row[2][2]==1&&Row[0][1]==0
		&&Row[0][2]==0&&Row[1][0]==0&&Row[1][2]==0&&Row[2][0]==0
		&&Row[2][1]==0)
		return true;
	return false;
}

bool NaGeMatrix33::IsEqual(const NaGeMatrix33 &Other) const
{
	int i,j,flag=0;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
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

NaGeMatrix33 NaGeMatrix33::Adjoint()
{
	NaGeMatrix33 tmpNaGeMatrix33;
	Transpose();
	//A11
	tmpNaGeMatrix33.Row[0][0]=
		1*(Row[1][1]*Row[2][2]-Row[2][1]*Row[1][2]);
	//B12
	tmpNaGeMatrix33.Row[0][1]=
		-1*(Row[1][0]*Row[2][2]-Row[2][0]*Row[1][2]);
	//C13
	tmpNaGeMatrix33.Row[0][2]=
		1*(Row[1][0]*Row[2][1]-Row[2][0]*Row[1][1]);
	//A21
	tmpNaGeMatrix33.Row[1][0]=
		-1*(Row[0][1]*Row[2][2]-Row[2][1]*Row[0][2]);
	//B22
	tmpNaGeMatrix33.Row[1][1]=
		1*(Row[0][0]*Row[2][2]-Row[2][0]*Row[0][2]);
	//C23
	tmpNaGeMatrix33.Row[1][2]=
		-1*(Row[0][0]*Row[2][1]-Row[2][0]*Row[0][1]);
	//A31
	tmpNaGeMatrix33.Row[2][0]=
		1*(Row[0][1]*Row[1][2]-Row[1][1]*Row[0][2]);
	//B32
	tmpNaGeMatrix33.Row[2][1]=
		-1*(Row[0][0]*Row[1][2]-Row[1][0]*Row[0][2]);
	//C33
	tmpNaGeMatrix33.Row[2][2]=
		1*(Row[0][0]*Row[1][1]-Row[1][0]*Row[0][1]);
	Transpose();
	return tmpNaGeMatrix33;
}

void NaGeMatrix33::SetIdentity()
{
	//Identity Matrix
	double Row1[3]={1,0,0};
	double Row2[3]={0,1,0};
	double Row3[3]={0,0,1};
	NaGeMatrix33 M(Row1, Row2, Row3);
	*this = M;
}

void NaGeMatrix33::SetRotation(const NaGeVector3D& Axis, double t)
{

	double nx, ny, nz;
	nx = Axis.GetX(); ny = Axis.GetY(); nz = Axis.GetZ();
	double Row1[3]={ nx*nx*vsin(t)+cos(t), nx*ny*vsin(t)-nz*sin(t), nx*nz*vsin(t)+ny*sin(t)};
	double Row2[3]={ nx*ny*vsin(t)+nz*sin(t), ny*ny*vsin(t)+cos(t), ny*nz*vsin(t)-nx*sin(t)};
	double Row3[3]={ nx*nz*vsin(t)-ny*sin(t), ny*nz*vsin(t)+nx*sin(t), nz*nz*vsin(t)+cos(t)};
	NaGeMatrix33 M(Row1, Row2, Row3);
	*this = M;
}

void NaGeMatrix33::SetScale(const NaGePoint3D& Point)
{
	NaGePoint3D P = Point;
	double Row1[3]={P.GetX(),          0,          0};
	double Row2[3]={         0, P.GetY(),          0};
	double Row3[3]={         0, 0,          P.GetZ()};
	NaGeMatrix33 M(Row1, Row2, Row3);
	*this = M;
}

NaGePoint3D NaGeMatrix33::GetDiagonal() const
{
	NaGePoint3D V;
	NaGeMatrix33 M = *this;
	V.SetX(M(0,0));
	V.SetY(M(1,1));
	V.SetZ(M(2,2));
	return V;
}
