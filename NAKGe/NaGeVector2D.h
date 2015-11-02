
/***************************************************************************
 *            NaGeVector2D.h
 *
 ****************************************************************************/


#ifndef _VECTOR2D_H
#define _VECTOR2D_H

#ifdef NAKGE_EXPORTS
#define NAKGE_API __declspec(dllexport)
#else
#define NAKGE_API __declspec(dllimport)
#endif

#include "NaGeGeometry2D.h"

class NaGePoint2D;
class NaGeMatrix22;
class NaGeOneAxis2D;

class NAKGE_API NaGeVector2D : public NaGeGeometry2D  
{
public:
	NaGeVector2D();
	NaGeVector2D(double x, double y);
	NaGeVector2D(const NaGePoint2D&);
	NaGeVector2D(const NaGeVector2D&, const NaGeVector2D&);
	NaGeVector2D(const NaGePoint2D&, const NaGePoint2D&);
	~NaGeVector2D();
	inline void SetX(double x){itsX = x;} //Set The X Component Value
	inline void SetY(double y){itsY = y;} //Set The Y Component Value
	inline void SetParam(double x, double y){itsX = x; itsY = y;} //Set The X Y and Z Values
	inline double GetX() const {return itsX;}// Returns The X Component
	inline double GetY() const {return itsY;}// Returns The Y Component
	double Dot(const NaGeVector2D &V1) const;//Calculate Dot Product
	double DotCross(const NaGeVector2D &V1, const NaGeVector2D &V2);//Calculate Scalar Triple Product
	void Cross(const NaGeVector2D &V1);//Calculate Cross Product Of' this' And Other
	NaGeVector2D Crossed(const NaGeVector2D &V1) const;//Return The Cross Product Vector
	void CrossCross(const NaGeVector2D &V1, const NaGeVector2D &V2);//Calculate The Vector Triple Product
	NaGeVector2D CrossCrossed(const NaGeVector2D &V1, const NaGeVector2D &V2);//Return Vector Triple Product
	void Reverse();//Reverse The Direction Of 'this'
	NaGeVector2D Reversed();//Return The Reversed Vector Of 'this'
	NaGeVector2D operator + (const NaGeVector2D &V1);//Return Addition Of 'this' And Other
	void operator += (const NaGeVector2D &V1);//Add Other To 'this'
	NaGeVector2D operator - (const NaGeVector2D &V1);//Return Subtraction Of 'this' And Other
	void operator -= (const NaGeVector2D &V1);//Subtract Other From 'this'
	NaGeVector2D operator * (const double &scalar);//Scalar Multiple With Other Vector
	NaGeVector2D operator * (const NaGeMatrix22& M);//Multiply With Matrix
	void operator *= (const double &scalar);//Multiply 'this' With Other
	void operator *= (const NaGeMatrix22 &M);//Multiply 'this With Matrix
	NaGeVector2D operator / (const double &scalar);//Scalar Division
	void operator /= (const double &scalar);//Divide 'this' By Scalar
	NaGeVector2D operator ^ (const NaGeVector2D &V1);//Return The Cross Product
	void operator ^= (const NaGeVector2D &V1);//Calculate Cross Product Of' this' And Other
	double Magnitude() const;// Calculate 'this' Vector's Magnitude
	double SqrMagnitude() const;// Calculate 'this' Vector's Square Magnitude
	double CrossMagnitude(const NaGeVector2D &V);// Calculate 'this' Vector's Cross Magnitude
	double CrossSqrMagnitude(const NaGeVector2D &V1);// Calculate 'this' Vector's Cross Square Magnitude
	double Modulus();// Return Modulus
	NaGeVector2D Unit();//Return Normalized Vector Of 'this'
	NaGePoint2D Point();//Return Component Triplet As Point
	double Angle(const NaGeVector2D&) const;//Angle Bet'n 'this' And Other
	double Angle(const NaGeVector2D&, const NaGeVector2D&) const;//Angle Bet'n 'this' And Other WRT Direction
	bool IsNull() const;//Check For Null Vector
	bool IsParallel(const NaGeVector2D&) const;//Check If Parallel To Other
	bool IsOpposite(const NaGeVector2D&) const;//Check If Opposite Direction To Other
	bool IsNormal(const NaGeVector2D&) const;//Check If Normal To Other
	bool operator == (const NaGeVector2D& V) const;//Check Equality
	operator NaGePoint2D();//Convertion Cast To Point;
	void Print() const;//Print Values Of Components
	void Normalize();//Normalize 'this' Vector
	virtual void Translate(const NaGeOneAxis2D&, const double&);
	virtual void Translate(double dx, double dy);
	virtual void Translate(const NaGeVector2D&);
	virtual void Translate(const NaGePoint2D&, const NaGePoint2D&);
	virtual void Rotate(const NaGePoint2D&, double);
	virtual void Scale(const NaGePoint2D&, double);
	virtual void Mirror(const NaGePoint2D&);
	virtual void Mirror(const NaGeOneAxis2D&);
	static NaGeVector2D Origin();
private:
	double itsX;
	double itsY;
};

#endif /* _VECTOR2D_H */
