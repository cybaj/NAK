 
/***************************************************************************
 *            NaGeAxisSystem.h
 *
 ****************************************************************************/


#ifndef _AXISSYSTEM_H
#define _AXISSYSTEM_H

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

class NAKGE_API NaGeAxisSystem : public NaGeGeometry  
{
public:
	NaGeAxisSystem();
	NaGeAxisSystem(const NaGePoint3D& Pos, const NaGeVector3D& Dir, const NaGeVector3D& XDir);
	NaGeAxisSystem(const NaGePoint3D& Pos, const NaGeVector3D& Dir);
	NaGeAxisSystem(const NaGeAxisSystem&);
	~NaGeAxisSystem();
	void SetPosition(const NaGePoint3D& P);
	void SetPosition(double x, double y, double z);
	void SetDirection(const NaGeVector3D& D);
	void SetDirection(double dx, double dy, double dz);
	void SetXDirection(const NaGeVector3D& XD);
	void SetXDirection(double dxx, double dxy, double dxz);
	void SetYDirection(const NaGeVector3D& YD);
	void SetYDirection(double dyx, double dyy, double dyz);
	inline NaGePoint3D GetPosition() const { return Position; }
	inline NaGeVector3D GetOrigin() const	{ return Origin; }
	inline NaGeVector3D GetDirection() const	{ return Direction; }
	inline NaGeVector3D GetXDirection() const { return XDirection; }
	inline NaGeVector3D GetYDirection() const { return YDirection; }
	bool operator == (const NaGeAxisSystem& C) const;
	virtual void Translate(const NaGeOneAxis&, const double&);
	virtual void Translate(double dx, double dy, double dz);
	virtual void Translate(const NaGeVector3D&);
	virtual void Translate(const NaGePoint3D& P1, const NaGePoint3D& P2);
	virtual void Rotate(const NaGeOneAxis&, double);
	virtual void Scale(const NaGePoint3D&, double);
	virtual void Mirror(const NaGePoint3D&);
	virtual void Mirror(const NaGeOneAxis&);
	virtual void Mirror(const NaGePlane&);
private:
	NaGePoint3D Position;
	NaGeVector3D Origin;
	NaGeVector3D Direction;
	NaGeVector3D XDirection;
	NaGeVector3D YDirection;
};

#endif /* _AXISSYSTEM_H */
