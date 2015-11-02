 
/***************************************************************************
 *            NaGeCone.h
 *
 ****************************************************************************/


#ifndef _CONE_H
#define _CONE_H

#ifdef NAKGE_EXPORTS
#define NAKGE_API __declspec(dllexport)
#else
#define NAKGE_API __declspec(dllimport)
#endif

#include "NaGeBasicSurface.h"
#include "NaGeMMath.h"


class NAKGE_API NaGeCone : public NaGeBasicSurface  
{
    public:
	NaGeCone(){}
	NaGeCone(const NaGeCircle3d&, const double& ht);	
	NaGeCone(const NaGeAxisSystem&, const double& ht, const double& rad1, const double& rad2 = 0, const double& uStart = 0, const double& uEnd = 2*PI);
	virtual ~NaGeCone();
	inline void SetBaseRadius(const double& r) { baseRadius = r; }
	inline void SetTopRadius(const double& r) { topRadius = r; }
	inline void SetHeight(const double& h) { itsHeight = h; }
	inline double GetBaseRadius() const { return baseRadius; }
	inline double GetTopRadius() const { return topRadius; }
	inline double GetHeight() const { return itsHeight; }
	virtual NaGePoint3D PointAtPara(const double uPar, const double vPar);
	inline virtual double FirstUParameter() const { return itsFirstUParameter; }
	inline virtual double LastUParameter() const { return itsLastUParameter; }
	inline virtual double FirstVParameter() const { return itsFirstVParameter; }
	inline virtual double LastVParameter() const { return itsLastVParameter; }
	virtual bool IsUClosed() const;
	virtual bool IsVClosed() const;
	virtual NaGeSurface* Copy() const;
	virtual void Translate(const NaGeOneAxis&, const double&);
	virtual void Translate(double dx, double dy, double dz);
	virtual void Translate(const NaGeVector3D&);
	virtual void Translate(const NaGePoint3D&, const NaGePoint3D&);
	virtual void Rotate(const NaGeOneAxis&, double);
	virtual void Scale(const NaGePoint3D&, double);
	virtual void Mirror(const NaGePoint3D&);
	virtual void Mirror(const NaGeOneAxis&);
	virtual void Mirror(const NaGePlane&);
    private:
	double itsHeight;
	double baseRadius;
	double topRadius;	
};

#endif /* _CONE_H */
