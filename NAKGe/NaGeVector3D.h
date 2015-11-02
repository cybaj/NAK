/***************************************************************************
 *            NaGeVector3D.h
 *
 ****************************************************************************/


#ifndef _VECTOR3D_H
#define _VECTOR3D_H

#ifdef NAKGE_EXPORTS
#define NAKGE_API __declspec(dllexport)
#else
#define NAKGE_API __declspec(dllimport)
#endif

#include <iostream>
using namespace std;

#include "NaGeGeometry.h"

class NaGePoint3D;
class NaGeMatrix33;
class NaGeOneAxis;
class NaGePlane;

class NAKGE_API NaGeVector3D : public NaGeGeometry  
{
    friend std::istream &operator>>(std::istream& , NaGeVector3D&);
    friend std::ostream &operator<<(std::ostream& , NaGeVector3D&);
public:
	NaGeVector3D();
	NaGeVector3D(double x, double y, double z);
	NaGeVector3D(const NaGePoint3D&);
	NaGeVector3D(const NaGeVector3D&, const NaGeVector3D&);
	NaGeVector3D(const NaGePoint3D&, const NaGePoint3D&);
	~NaGeVector3D();
	inline void SetX(double x){itsX = x;} ///Set The X Component Value
	inline void SetY(double y){itsY = y;} ///Set The Y Component Value
	inline void SetZ(double z){itsZ = z;} ///Set The Z Component Value
	inline void SetParam(double x, double y, double z){itsX = x; itsY = y;itsZ = z;} ///Set The X Y and Z Values
	inline double GetX() const {return itsX;}/// Returns The X Component
	inline double GetY() const {return itsY;}/// Returns The Y Component
	inline double GetZ() const {return itsZ;}/// Returns The Z Component
	double Dot(const NaGeVector3D &V1) const;///Calculate Dot Product
	double DotCross(const NaGeVector3D &V1, const NaGeVector3D &V2);///Calculate Scalar Triple Product
	void Cross(const NaGeVector3D &V1);///Calculate Cross Product Of' this' And Other
	NaGeVector3D Crossed(const NaGeVector3D &V1) const;///Return The Cross Product Vector
	void CrossCross(const NaGeVector3D &V1, const NaGeVector3D &V2);///Calculate The Vector Triple Product
	NaGeVector3D CrossCrossed(const NaGeVector3D &V1, const NaGeVector3D &V2);///Return Vector Triple Product
	void Reverse();///Reverse The Direction Of 'this'
	NaGeVector3D Reversed();///Return The Reversed Vector Of 'this'
	NaGeVector3D operator + (const NaGeVector3D &V1);///Return Addition Of 'this' And Other
	void operator += (const NaGeVector3D &V1);///Add Other To 'this'
	NaGeVector3D operator - (const NaGeVector3D &V1);///Return Subtraction Of 'this' And Other
	void operator -= (const NaGeVector3D &V1);///Subtract Other From 'this'
	NaGeVector3D operator * (const double &scalar);///Scalar Multiple With Other Vector
	NaGeVector3D operator * (const NaGeMatrix33& M);///Multiply With Matrix
	void operator *= (const double &scalar);///Multiply 'this' With Other
	void operator *= (const NaGeMatrix33 &M);///Multiply 'this With Matrix
	NaGeVector3D operator / (const double &scalar);///Scalar Division
	void operator /= (const double &scalar);///Divide 'this' By Scalar
	NaGeVector3D operator ^ (const NaGeVector3D &V1);///Return The Cross Product
	void operator ^= (const NaGeVector3D &V1);///Calculate Cross Product Of' this' And Other
	double Magnitude() const;/// Calculate 'this' Vector's Magnitude
	double SqrMagnitude() const;/// Calculate 'this' Vector's Square Magnitude
	double CrossMagnitude(const NaGeVector3D &V);/// Calculate 'this' Vector's Cross Magnitude
	double CrossSqrMagnitude(const NaGeVector3D &V1);/// Calculate 'this' Vector's Cross Square Magnitude
	double Modulus();/// Return Modulus
	NaGeVector3D Unit();///Return Normalized Vector Of 'this'
	NaGePoint3D Point() const;///Return Component Triplet As Point
	double Angle(const NaGeVector3D&) const;///Angle Bet'n 'this' And Other
	double Angle(const NaGeVector3D&, const NaGeVector3D&) const;///Angle Bet'n 'this' And Other WRT Direction
	bool IsNull() const;///Check For Null Vector
	bool IsParallel(const NaGeVector3D&) const;///Check If Parallel To Other
	bool IsOpposite(const NaGeVector3D&) const;///Check If Opposite Direction To Other
	bool IsNormal(const NaGeVector3D&) const;///Check If Normal To Other
	bool operator == (const NaGeVector3D& V) const;///Check Equality
	operator NaGePoint3D();///Convertion Cast To Point;
	void Print() const;///Print Values Of Components
	void Normalize();///Normalize 'this' Vector
	virtual void Translate(const NaGeOneAxis&, const double&);
	virtual void Translate(double dx, double dy, double dz);
	virtual void Translate(const NaGeVector3D&);
	virtual void Translate(const NaGePoint3D&, const NaGePoint3D&);
	virtual void Rotate(const NaGeOneAxis&, double);
	virtual void Scale(const NaGePoint3D&, double);
	virtual void Mirror(const NaGePoint3D&);
	virtual void Mirror(const NaGeOneAxis&);
	virtual void Mirror(const NaGePlane&);
	static NaGeVector3D Origin();
private:
	double itsX;
	double itsY;
	double itsZ;
};

#endif /* _VECTOR3D_H */
