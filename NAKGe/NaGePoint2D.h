
 
/***************************************************************************
 *            NaGePoint2D.h
 *
 ****************************************************************************/


#ifndef _POINT2D_H
#define _POINT2D_H


#include <iostream>
using namespace std;

#ifdef NAKGE_EXPORTS
#define NAKGE_API __declspec(dllexport)
#else
#define NAKGE_API __declspec(dllimport)
#endif

#include "NaGeGeometry2D.h"


class NaGeVector2D;
class NaGeOneAxis2D;

enum ORIENTATION 
{ 
	ORIENTED_CCW, 
	ORIENTED_CW, 
	ORIENTED_COLLINEAR 
};

enum CLASSIFICATION
{
	CLASSIFIED_LEFT,
	CLASSIFIED_RIGHT,
	CLASSIFIED_BEHIND,
	CLASSIFIED_BEYOND,
	CLASSIFIED_BETWEEN,
	CLASSIFIED_ORIGIN,
	CLASSIFIED_DESTINATION
};

class NAKGE_API NaGePoint2D  : public NaGeGeometry2D
{
    friend std::istream &operator>>(std::istream& , NaGePoint2D&);
    friend std::ostream &operator<<(std::ostream& , NaGePoint2D&);
    public:
    NaGePoint2D();
    NaGePoint2D(double, double);
    virtual ~NaGePoint2D();
    void SetParam(double, double);
    inline void SetX(double x) {itsX=x;}
    inline void SetY(double y) {itsY=y;}
    inline double GetX() const { return itsX; }
    inline double GetY() const { return itsY; }
    NaGePoint2D operator+(const NaGePoint2D&);
    NaGePoint2D operator+(const double&);
    NaGePoint2D operator-(const NaGePoint2D&);
    NaGePoint2D operator-(const double&);
    NaGePoint2D operator*(const double scale);
    NaGePoint2D operator/(const double scale);
    void operator+=(const NaGePoint2D&);
    void operator+=(const double&);
    void operator-=(const NaGePoint2D&);
    void operator-=(const double&);
    void operator*=(const double scale);
    void operator/=(const double scale);
    NaGePoint2D operator = (const NaGePoint2D& p);    
    double Distance(const NaGePoint2D&);
    
    double PolarAngle(const NaGePoint2D& P = NaGePoint2D::Origin()) const;
    bool operator == (const NaGePoint2D& p) const;
    ORIENTATION Orientation(const NaGePoint2D& P1, const NaGePoint2D& P2);
    CLASSIFICATION Classification(const NaGePoint2D& P1, const NaGePoint2D& P2);
    operator NaGeVector2D();
    virtual void Translate(const NaGeOneAxis2D&, const double&);
    virtual void Translate(double dx, double dy);
    virtual void Translate(const NaGeVector2D&);
    virtual void Translate(const NaGePoint2D&, const NaGePoint2D&);
    virtual void Rotate(const NaGePoint2D&, double);
    virtual void Scale(const NaGePoint2D&, double);
    virtual void Mirror(const NaGePoint2D&);
    virtual void Mirror(const NaGeOneAxis2D&);
    static NaGePoint2D Origin();
    private:
    double itsX;
    double itsY;
};

#endif /* _POINT2D_H */
