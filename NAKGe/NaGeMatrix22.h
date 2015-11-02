
/***************************************************************************
 *            NaGeMatrix22.h
 ****************************************************************************/


#ifndef _MATRIX22_H
#define _MATRIX22_H

#ifdef NAKGE_EXPORTS
#define NAKGE_API __declspec(dllexport)
#else
#define NAKGE_API __declspec(dllimport)
#endif

#include "NaGeGeometry2D.h"

class NaGePoint2D;
class NaGeVector2D;

class NAKGE_API NaGeMatrix22
{
public:
	NaGeMatrix22();
	NaGeMatrix22(double r1[2],double r2[2]);
	~NaGeMatrix22();
	NaGeMatrix22 operator*(const NaGeMatrix22&);
	NaGeVector2D operator*(const NaGeVector2D&);
	NaGeMatrix22 operator*(const double Value);
	void operator*=(const NaGeMatrix22&);
	void operator*=(const double Value);
	NaGeMatrix22 operator/(const double Value);
	void operator/=(const double Value);
	NaGeMatrix22 operator+(const NaGeMatrix22&);
	void operator+=(const NaGeMatrix22&);
	NaGeMatrix22 operator-(const NaGeMatrix22&);
	void operator-=(const NaGeMatrix22&);
	double Determinant();
	void Invert();
	NaGeMatrix22 Inverted() const;
	void Transpose();
	void Value() const;
	bool IsNull() const;
	bool IsDiagonal() const;
	bool IsSymmetrical() const;
	bool IsScalar() const;
	bool IsIdentity() const;
	bool IsEqual(const NaGeMatrix22&) const;
	inline double operator()(int row, int col) const { return Row[row][col]; }
	inline double &operator()(int row, int col) { return Row[row][col]; }
	void SetIdentity();
	void SetRotation(double ang);
	void SetScale(const NaGePoint2D&);
	NaGePoint2D GetDiagonal() const;
private:
  double Row[2][2];
  NaGeMatrix22 Adjoint();
};

#endif /* _MATRIX22_H */
