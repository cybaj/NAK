 
/***************************************************************************
 *            NaGeGeometry.h
 *
 ****************************************************************************/


#ifndef _GEOMETRY_H
#define _GEOMETRY_H

#ifdef NAKGE_EXPORTS
#define NAKGE_API __declspec(dllexport)
#else
#define NAKGE_API __declspec(dllimport)
#endif

enum GeometryType { GEPOINT, GEPLANE, GEPOLYGON, GEONEAXIS, GEAXISSYSTEM, GECURVE, GESURFACE };

class NaGePoint3D;
class NaGeVector3D;
class NaGeOneAxis;
class NaGeAxisSystem;
class NaGeLine3D;
class NaGeCircle3d;
class NaGeEllipse3d;
class NaGeHyperbola3D;
class NaGeParabola3D;
class NaGeBezierCurve;
class NaGeBSplineCurve;
class NaGePlane;
class NaGeCone;
class NaGeCylinder;
class NaGeSphere;
class NaGeTorus;
class NaGeExtrudedSurface;
class NaGeRevolvedSurface;
class NaGeRuledSurface;
class NaGePipeSurface;

class NAKGE_API NaGeGeometry
{
public:
	NaGeGeometry();
	virtual ~NaGeGeometry();
	virtual void Translate(const NaGeOneAxis&, const double& amt);
	virtual void Translate(double dx, double dy, double dz) = 0;
	virtual void Translate(const NaGeVector3D&) = 0;
	virtual void Translate(const NaGePoint3D&, const NaGePoint3D&) = 0;
	virtual void Rotate(const NaGeOneAxis&, double) = 0;
	virtual void Scale(const NaGePoint3D&, double) = 0;
	virtual void Mirror(const NaGePoint3D&) = 0;
	virtual void Mirror(const NaGeOneAxis&) = 0;
	virtual void Mirror(const NaGePlane&) = 0;
	inline GeometryType GeomType() const { return geomType; }
private:
	static int refCount;
protected:
	GeometryType geomType;

};

#endif /* _GEOMETRY_H */
