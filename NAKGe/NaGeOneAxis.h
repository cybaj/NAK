 
/***************************************************************************
 *            NaGeOneAxis.h
 *
 ****************************************************************************/


#ifndef _ONEAXIS_H
#define _ONEAXIS_H

#ifdef NAKGE_EXPORTS
#define NAKGE_API __declspec(dllexport)
#else
#define NAKGE_API __declspec(dllimport)
#endif

#include "NaGeGeometry.h"
#include "NaGePoint3D.h"
#include "NaGeVector3D.h"

class NaGePoint3D;
class NaGeVector3D;

class NAKGE_API NaGeOneAxis : public NaGeGeometry  
{
public:
	NaGeOneAxis();
	NaGeOneAxis(const NaGePoint3D& Pos, const NaGeVector3D& Dir);
	~NaGeOneAxis();
	void SetPosition(const NaGePoint3D& P);
	void SetPosition(double x, double y, double z);
	void SetDirection(const NaGeVector3D& D);
	void SetDirection(double dx, double dy, double dz);
	NaGePoint3D GetPosition() const;
	NaGeVector3D GetOrigin() const;
	NaGeVector3D GetDirection() const;
	bool operator == (const NaGeOneAxis&) const;
	virtual void Translate(const NaGeOneAxis&, const double&);
	virtual void Translate(double dx, double dy, double dz);
	virtual void Translate(const NaGeVector3D&);
	virtual void Translate(const NaGePoint3D&, const NaGePoint3D&);
	virtual void Rotate(const NaGeOneAxis&, double);
	virtual void Scale(const NaGePoint3D&, double);
	virtual void Mirror(const NaGePoint3D&);
	virtual void Mirror(const NaGeOneAxis&);
	virtual void Mirror(const NaGePlane&);
	static NaGeOneAxis OX();
	static NaGeOneAxis OY();
	static NaGeOneAxis OZ();
private:
	NaGePoint3D Position;
	NaGeVector3D Origin;
	NaGeVector3D Direction;
};

#endif /* _ONEAXIS_H */
