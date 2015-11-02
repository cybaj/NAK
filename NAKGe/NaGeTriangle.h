
/***************************************************************************
 *            NaGeTriangle.h
 *
 ****************************************************************************/


#ifndef _TRIANGLE_H
#define _TRIANGLE_H

#ifdef NAKGE_EXPORTS
#define NAKGE_API __declspec(dllexport)
#else
#define NAKGE_API __declspec(dllimport)
#endif

#include "NaGeGeometry.h"
#include "NaGePoint3D.h"
#include "NaGePoint2D.h"
#include "NaGeVector3D.h"

class NAKGE_API NaGeTriangle : public NaGeGeometry
{
public:
    NaGeTriangle();
    NaGeTriangle(const NaGePoint3D& v1, const NaGePoint3D& v2, const NaGePoint3D& v3);
    NaGeTriangle(const NaGeTriangle& other);
    virtual ~NaGeTriangle();
    void SetVertex(const int& index, const NaGePoint3D& v);
    NaGePoint3D GetVertex(const int& index) const;
    NaGeVector3D Normal() const;    
    bool operator == (const NaGeTriangle& p) const;
    virtual void Translate(double dx, double dy, double dz);
    virtual void Translate(const NaGeVector3D&);
    virtual void Translate(const NaGePoint3D&, const NaGePoint3D&);
    virtual void Rotate(const NaGeOneAxis&, double);
    virtual void Scale(const NaGePoint3D&, double);
    virtual void Mirror(const NaGePoint3D&);
    virtual void Mirror(const NaGeOneAxis&);
    virtual void Mirror(const NaGePlane&);
private:
    NaGePoint3D vArray[3];
};

#endif /* _TRIANGLE_H */
