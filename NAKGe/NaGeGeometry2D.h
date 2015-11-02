
/***************************************************************************
 *            NaGeGeometry2D.h
 ****************************************************************************/


#ifndef _GEOMETRY2D_H
#define _GEOMETRY2D_H

#ifdef NAKGE_EXPORTS
#define NAKGE_API __declspec(dllexport)
#else
#define NAKGE_API __declspec(dllimport)
#endif

enum Geometry2DType { GEPOINT2D, GEONEAXIS2D, GECURVE2D };

class NaGePoint2D;
class NaGeVector2D;
class NaGeOneAxis2D;

class NAKGE_API NaGeGeometry2D
{

public:
	NaGeGeometry2D();
	virtual ~NaGeGeometry2D();
	virtual void Translate(const NaGeOneAxis2D&, const double& amt);
	virtual void Translate(double dx, double dy) = 0;
	virtual void Translate(const NaGeVector2D&) = 0;
	virtual void Translate(const NaGePoint2D&, const NaGePoint2D&) = 0;
	virtual void Rotate(const NaGePoint2D&, double) = 0;
	virtual void Scale(const NaGePoint2D&, double) = 0;
	virtual void Mirror(const NaGePoint2D&) = 0;
	virtual void Mirror(const NaGeOneAxis2D&) = 0;
	inline Geometry2DType GeomType() const { return geomType; }
private:
	static int refCount;
protected:
	Geometry2DType geomType;

};

#endif /* _GEOMETRY2D_H */
