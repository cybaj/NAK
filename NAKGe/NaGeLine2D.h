 
/***************************************************************************
 *            NaGeLine2D.h
 *
 ****************************************************************************/


#ifndef _LINE2D_H
#define _LINE2D_H

#ifdef NAKGE_EXPORTS
#define NAKGE_API __declspec(dllexport)
#else
#define NAKGE_API __declspec(dllimport)
#endif

#include "NaGeCurve2D.h"
#include "NaGePoint2D.h"
#include "NaGeVector2D.h"
#include "NaGeOneAxis2D.h"

class NaGePoint2D;
class NaGeVector2D;
class NaGeOneAxis2D;

class NAKGE_API NaGeLine2D : public NaGeCurve2D  
{
public:
	NaGeLine2D();
	NaGeLine2D(const NaGePoint2D&, const NaGePoint2D&);
	NaGeLine2D(const NaGePoint2D&, const NaGeVector2D&);
	virtual ~NaGeLine2D();
	virtual void Reverse();
	virtual NaGePoint2D PointAtPara(const double& par);
	inline virtual double FirstParameter() const { return 0; }
	inline virtual double LastParameter() const {return 1; }
	virtual bool IsClosed() const;
	bool operator == (const NaGeLine2D& L) const;
	void operator = (const NaGeLine2D& L);
	NaGeVector2D Direction() const;
	inline NaGeOneAxis2D GetLocation() const { return itsLocation; }
	NaGeVector2D NormalThrough(const NaGePoint2D&);
	double Distance(const NaGePoint2D&);
	inline double SegmentLength() { return startPoint.Distance(endPoint); }
	inline NaGePoint2D StartPoint() const { return startPoint; }
	inline NaGePoint2D EndPoint() const { return endPoint; }
	virtual NaGeCurve2D* Copy() const;
	virtual void Translate(const NaGeOneAxis2D&, const double&);
	virtual void Translate(double dx, double dy);
	virtual void Translate(const NaGeVector2D&);
	virtual void Translate(const NaGePoint2D&, const NaGePoint2D&);
	virtual void Rotate(const NaGePoint2D&, double);
	virtual void Scale(const NaGePoint2D&, double);
	virtual void Mirror(const NaGePoint2D&);
	virtual void Mirror(const NaGeOneAxis2D&);
private:
	NaGePoint2D startPoint;
	NaGePoint2D endPoint;
	NaGeOneAxis2D itsLocation;
};

#endif /* _LINE2D_H */
