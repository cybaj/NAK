/***************************************************************************
 *           NaGe Conic.h
 *
 ****************************************************************************/


#ifndef _CONIC_H
#define _CONIC_H

#ifdef NAKGE_EXPORTS
#define NAKGE_API __declspec(dllexport)
#else
#define NAKGE_API __declspec(dllimport)
#endif

#include "NaGeCurve.h"
#include "NaGeAxisSystem.h"

class NaGePoint3D;

//Abstract Base Class  For Circle, Ellipse, Parabola and Hyperbola
class NAKGE_API NaGeConic : public NaGeCurve  
{
public:
	NaGeConic();
	virtual ~NaGeConic();
	virtual void Reverse();
	void SetLocation(const NaGeAxisSystem& ax);
	virtual NaGePoint3D PointAtPara(const double& para) = 0;
	virtual double FirstParameter() const = 0;
	virtual double LastParameter() const = 0;
	virtual double Eccentricity() const = 0;
	virtual bool IsClosed() const = 0;
	virtual NaGeCurve* Copy() const = 0;
protected:
	NaGeAxisSystem itsLocation;
};

#endif /* _CONIC_H */
