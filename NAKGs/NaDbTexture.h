/***************************************************************************
 *            NaDbTexture.h
 *
 ****************************************************************************/


#ifndef _GLTexture_H
#define _GLTexture_H

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

#include "model_obj.h"

class ModelOBJ;
class ObjLoader;
class TextureManager;

class NAKGS_API NaDbTexture : public NaDbObject
{
public:
	NaDbTexture(const NaGeSurface*, const char* filename);
	virtual ~NaDbTexture();
	virtual NaDbObject* Copy();
	virtual void DefineDisplay();
	virtual void Display(const GsDisplayMode& = GLWIREFRAME);
	virtual void Hilight(const GsDisplayMode&);
	virtual void SetColor(const GLubyte&, const GLubyte&, const GLubyte&);
	virtual void GetColor(GLubyte*) const;
	void SetSurface(const NaGeSurface*);
	virtual NaGeGeometry* Geometry() const;
	const CListOfPoint3D* GetPositionList() { return pointList; }

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

	void LoadModel(const char *pszFilename);
	void DrawModelUsingFixedFuncPipeline();
	void DrawModelUsingProgrammablePipeline();
	GLuint LoadTexture(const char *pszFilename);

private:
	GLdouble SMOOTH;
	GLdouble CSMOOTH;
	CListOfPoint3D* pointList;
	CListOfPoint3D* normalList;
	CListOfPoint3D* bpointList;
	NaGeSurface* pSurf;
	GLubyte isoRed;
	GLubyte isoGreen;
	GLubyte isoBlue;
	GLint factor;			// Stippling factor
	GLushort pattern;	// Stipple pattern
	
	GLint wireList;
	GLint edgeList;
	GLint shadList;

	std::string m_path;
	ModelOBJ	m_model;
};

#endif /* _GLTexture_H */
