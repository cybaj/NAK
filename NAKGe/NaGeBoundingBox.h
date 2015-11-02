 
/***************************************************************************
 *            NaGeBoundingBox.h
 *
 ****************************************************************************/


#ifndef _BOUNDINGBOX_H
#define _BOUNDINGBOX_H

#ifdef NAKGE_EXPORTS
#define NAKGE_API __declspec(dllexport)
#else
#define NAKGE_API __declspec(dllimport)
#endif

class NaGePoint3D;

class NAKGE_API NaGeBoundingBox  
{
public:
	NaGeBoundingBox();
	NaGeBoundingBox(const double&, const double&, const double&, const double&, const double&, const double&);
	virtual ~NaGeBoundingBox();
	void SetLimits(const double&, const double&, const double&, const double&, const double&, const double&);
	void GetLimits(double& xMin, double& xMax, double& yMin, double& yMax, double& zMin, double& zMax);
	inline double XMax() const { return itsXMax; }
	inline double XMin() const { return itsXMin; }
	inline double YMax() const { return itsYMax; }
	inline double YMin() const { return itsYMin; }
	inline double ZMax() const { return itsZMax; }
	inline double ZMin() const { return itsZMin; }
	NaGePoint3D Center() const;
	double BoundingRadius() const;
	bool Contains(const NaGePoint3D& P) const;
	void AddBox(const NaGeBoundingBox&);
private:
	double itsXMax;
	double itsXMin;
	double itsYMax;
	double itsYMin;
	double itsZMax;
	double itsZMin;
};

#endif /* _BOUNDINGBOX_H */
