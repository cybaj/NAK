 
/***************************************************************************
 *            NaDbSurface.h
 *
 ****************************************************************************/


#ifndef _GLSURFACE_H
#define _GLSURFACE_H

#ifdef NAKGS_EXPORTS
#define NAKGS_API __declspec(dllexport)
#else
#define NAKGS_API __declspec(dllimport)
#endif

#include "NaDbObject.h"
#include <NaGeGeometry.h>
#include <NaGeGeomException.h>
#include <NaGePoint3D.h>
#include <NaGeVector3D.h>
#include <NaGeLine3D.h>
#include <NaGePlane.h>
#include <NaGeCone.h>
#include <NaGeCylinder.h>
#include <NaGeSphere.h>
#include <NaGeTorus.h>
#include <NaGeExtrudedSurface.h>
#include <NaGeRevolvedSurface.h>
#include <NaGeRuledSurface.h>
#include <NaGePipeSurface.h>

#include <ListOfPoint3D.h>
#include <ListIteratorOfListOfPoint3D.h>

class NAKGS_API NaDbSurface : public NaDbObject  
{
public:
	NaDbSurface(const NaGeSurface*);
	virtual ~NaDbSurface();
	virtual NaDbObject* Copy();
	virtual bool SaveObject(FILE* fptr);
	virtual void DefineDisplay();
	virtual void Display(const GsDisplayMode& = GLWIREFRAME);
	virtual void Hilight(const GsDisplayMode&);
	virtual void SetColor(const GLubyte&, const GLubyte&, const GLubyte&);
	virtual void GetColor(GLubyte*) const;
	void SetSurface(const NaGeSurface*);
	virtual NaGeGeometry* Geometry() const;
private:
	void ComputePoints();
	void ComputeWFPoints();
	void ComputeBoundLimits();
	void DrawWired();
	void DrawShaded();
	void DrawEdges();
	void DrawUIso();
	void DrawVIso();
	void ComputeUIso(const double vPar);
	void ComputeVIso(const double uPar);
	void InitDisplayList();
private:
	GLdouble SMOOTH;
	GLdouble CSMOOTH;
	CListOfPoint3D* pointList;
	CListOfPoint3D* pointWFUList;
	CListOfPoint3D* pointWFVList;
	CListOfPoint3D* normalList;
	CListOfPoint3D* bpointList;
	CListIteratorOfListOfPoint3D myListWFUIter;
	CListIteratorOfListOfPoint3D myListWFVIter;
	NaGeSurface* pSurf;
	GLubyte isoRed;
	GLubyte isoGreen;
	GLubyte isoBlue;
	GLint factor;			// Stippling factor
	GLushort pattern;	// Stipple pattern
	
	GLint wireList;
	GLint edgeList;
	GLint shadList;
};

#endif /* _GLSURFACE_H */
