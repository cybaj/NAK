
/***************************************************************************
 *            NaGePoint3D.h
 ****************************************************************************/


#ifndef _POINT3D_H
#define _POINT3D_H

#include <iostream>
using namespace std;

#ifdef NAKGE_EXPORTS
#define NAKGE_API __declspec(dllexport)
#else
#define NAKGE_API __declspec(dllimport)
#endif

#include "NaGeGeometry.h"

    class NaGeVector3D;
    class NaGeOneAxis;
    class NaGeLine3D;
    class NaGePlane;


class NAKGE_API NaGePoint3D  : public NaGeGeometry
    {
	friend std::istream &operator>>(std::istream& , NaGePoint3D&);
	friend std::ostream &operator<<(std::ostream& , NaGePoint3D&);
	public:
	NaGePoint3D();
	NaGePoint3D(double, double, double);
	virtual ~NaGePoint3D();
	void SetParam(double, double, double);
	inline void SetX(double x) {itsX=x;}
	inline void SetY(double y) {itsY=y;}
	inline void SetZ(double z) {itsZ=z;}
	inline double GetX() const { return itsX; }
	inline double GetY() const { return itsY; }
	inline double GetZ() const { return itsZ; }
	NaGePoint3D operator+(const NaGePoint3D&);
	NaGePoint3D operator+(const double&);
	NaGePoint3D operator-(const NaGePoint3D&);
	NaGePoint3D operator-(const double&);
	NaGePoint3D operator*(const double scale);
	NaGePoint3D operator/(const double scale);
	void operator+=(const NaGePoint3D&);
	void operator+=(const double&);
	void operator-=(const NaGePoint3D&);
	void operator-=(const double&);
	void operator*=(const double scale);
	void operator/=(const double scale);
	NaGePoint3D operator = (const NaGePoint3D& p);    
	double Distance(const NaGePoint3D&) const;
	double Distance(const NaGePlane&) const;
	double PolarAngle(const NaGePoint3D& P = NaGePoint3D::Origin()) const;
	bool operator == (const NaGePoint3D& p) const;
	operator NaGeVector3D();
	virtual void Translate(const NaGeOneAxis&, const double&);
	virtual void Translate(double dx, double dy, double dz);
	virtual void Translate(const NaGeVector3D&);
	virtual void Translate(const NaGePoint3D&, const NaGePoint3D&);
	virtual void Rotate(const NaGeOneAxis&, double);
	virtual void Scale(const NaGePoint3D&, double);
	virtual void Mirror(const NaGePoint3D&);
	virtual void Mirror(const NaGeOneAxis&);
	virtual void Mirror(const NaGePlane&);
	static NaGePoint3D Origin();
	private:
	double itsX;
	double itsY;
	double itsZ;
};

#endif /* _POINT3D_H */
