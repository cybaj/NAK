
/***************************************************************************
 *            NaGeOneAxis2D.h
 *
 ****************************************************************************/


#ifndef _ONEAXIS2D_H
#define _ONEAXIS2D_H

#ifdef NAKGE_EXPORTS
#define NAKGE_API __declspec(dllexport)
#else
#define NAKGE_API __declspec(dllimport)
#endif

#include "NaGeGeometry2D.h"
#include "NaGePoint2D.h"
#include "NaGeVector2D.h"

class NaGePoint2D;
class NaGeVector2D;

class NAKGE_API NaGeOneAxis2D : public NaGeGeometry2D
{
public:
	NaGeOneAxis2D();
	NaGeOneAxis2D(const NaGePoint2D& Pos, const NaGeVector2D& Dir);
	~NaGeOneAxis2D();
	void SetPosition(const NaGePoint2D& P);
	void SetPosition(double x, double y);
	void SetDirection(const NaGeVector2D& D);
	void SetDirection(double dx, double dy);
	NaGePoint2D GetPosition() const;
	NaGeVector2D GetOrigin() const;
	NaGeVector2D GetDirection() const;
	bool operator == (const NaGeOneAxis2D&) const;
	virtual void Translate(const NaGeOneAxis2D&, const double&);
	virtual void Translate(double dx, double dy);
	virtual void Translate(const NaGeVector2D&);
	virtual void Translate(const NaGePoint2D&, const NaGePoint2D&);
	virtual void Rotate(const NaGePoint2D&, double);
	virtual void Scale(const NaGePoint2D&, double);
	virtual void Mirror(const NaGePoint2D&);
	virtual void Mirror(const NaGeOneAxis2D&);
	static NaGeOneAxis2D OX();
	static NaGeOneAxis2D OY();
private:
	NaGePoint2D Position;
	NaGeVector2D Origin;
	NaGeVector2D Direction;
};

#endif /* _ONEAXIS2D_H */
