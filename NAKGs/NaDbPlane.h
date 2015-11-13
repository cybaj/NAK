 
/***************************************************************************
 *            NaDbPlane.h
 *
 ****************************************************************************/


#ifndef _GLPLANE_H
#define _GLPLANE_H

#ifdef NAKGS_EXPORTS
#define NAKGS_API __declspec(dllexport)
#else
#define NAKGS_API __declspec(dllimport)
#endif

#include "NaDbObject.h"
#include <NaGePoint3D.h>
#include <NaGeVector3D.h>
#include <NaGePlane.h>

class NaGePlane;

class NAKGS_API NaDbPlane : public NaDbObject  
{
public:
	NaDbPlane(const NaGePlane&, const double& = 200, const double& = 200);
	virtual ~NaDbPlane();
	virtual NaDbObject* Copy();
	virtual bool SaveObject(FILE* fptr);
	virtual void DefineDisplay();
	virtual void Display(const GsDisplayMode& = GLWIREFRAME);
	virtual void Hilight(const GsDisplayMode&);
	virtual void SetColor(const GLubyte&, const GLubyte&, const GLubyte&);
	virtual void GetColor(GLubyte*) const;
	virtual NaGeGeometry* Geometry() const;
private:
	void ComputeBoundLimits();
private:
	NaGePlane itsPlane;
	double uSize;
	double vSize;
};

#endif /* _GLPLANE_H */
