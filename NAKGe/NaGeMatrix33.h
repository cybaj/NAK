
 
/***************************************************************************
 *            NaGeMatrix33.h
 ****************************************************************************/


#ifndef _MATRIX33_H
#define _MATRIX33_H

#ifdef NAKGE_EXPORTS
#define NAKGE_API __declspec(dllexport)
#else
#define NAKGE_API __declspec(dllimport)
#endif

#include "NaGeGeometry.h"

class NaGePoint3D;
class NaGeVector3D;

class NAKGE_API NaGeMatrix33
{
public:
	NaGeMatrix33();
	NaGeMatrix33(double r1[3],double r2[3],double r3[3]);
	~NaGeMatrix33();
	NaGeMatrix33 operator*(const NaGeMatrix33&);
	NaGeVector3D operator*(const NaGeVector3D&);
	NaGeMatrix33 operator*(const double Value);
	void operator*=(const NaGeMatrix33&);
	void operator*=(const double Value);
	NaGeMatrix33 operator/(const double Value);
	void operator/=(const double Value);
	NaGeMatrix33 operator+(const NaGeMatrix33&);
	void operator+=(const NaGeMatrix33&);
	NaGeMatrix33 operator-(const NaGeMatrix33&);
	void operator-=(const NaGeMatrix33&);
	double Determinant();
	void Invert();
	NaGeMatrix33 Inverted() const;
	void Transpose();
	void Value() const;
	bool IsNull() const;
	bool IsDiagonal() const;
	bool IsSymmetrical() const;
	bool IsScalar() const;
	bool IsIdentity() const;
	bool IsEqual(const NaGeMatrix33&) const;
	inline double operator()(int row, int col) const { return Row[row][col]; }
	inline double &operator()(int row, int col) { return Row[row][col]; }
	void SetIdentity();
	void SetRotation(const NaGeVector3D& axis, double ang);
	void SetScale(const NaGePoint3D&);
	NaGePoint3D GetDiagonal() const;
private:
  double Row[3][3];
  NaGeMatrix33 Adjoint();
};

#endif /* _MATRIX33_H */
