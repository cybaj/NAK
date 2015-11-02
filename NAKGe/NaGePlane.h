 
/***************************************************************************
 *            NaGePlane.h
 *
 ****************************************************************************/

#ifndef _PLANE_H
#define _PLANE_H

#ifdef NAKGE_EXPORTS
#define NAKGE_API __declspec(dllexport)
#else
#define NAKGE_API __declspec(dllimport)
#endif

#include "NaGeGeometry.h"
#include "NaGePoint3D.h"
#include "NaGeVector3D.h"
#include "NaGeOneAxis.h"
#include "NaGeAxisSystem.h"

class NaGePoint3D;
class NaGeVector3D;
class NaGeOneAxis;
class NaGeAxisSystem;

class NAKGE_API NaGePlane : public NaGeGeometry
{
public:
	NaGePlane(){}
	NaGePlane(const NaGePoint3D&, const NaGePoint3D&, const NaGePoint3D&);
	NaGePlane(const NaGePoint3D&, const NaGeVector3D&, const NaGeVector3D&);
	NaGePlane(const double&, const double&, const double&, const double&);
	NaGePlane(const NaGeOneAxis&);
	virtual ~NaGePlane();
	virtual NaGePoint3D PointAtPara(const double uPar, const double vPar);
	NaGePoint3D GetPosition() const;
	NaGeVector3D GetDirection() const;
	void EquationAt(const NaGePoint3D&, double*);
	double GetConstant() const;
	virtual void Translate(const NaGeOneAxis&, const double&);
	virtual void Translate(double dx, double dy, double dz);
	virtual void Translate(const NaGeVector3D&);
	virtual void Translate(const NaGePoint3D&, const NaGePoint3D&);
	virtual void Rotate(const NaGeOneAxis&, double);
	virtual void Scale(const NaGePoint3D&, double);
	virtual void Mirror(const NaGePoint3D&);
	virtual void Mirror(const NaGeOneAxis&);
	virtual void Mirror(const NaGePlane&);
	static NaGePlane XOY();
	static NaGePlane YOZ();
	static NaGePlane ZOX();
private:
	void UpdateEquation();
private:
	double Equation[4];	//Plane Equation
	NaGeAxisSystem itsLocation;

};

#endif /* _PLANE_H */
