/***************************************************************************
 *            NaDbObject.h
 *
 ****************************************************************************/

#ifndef _NaDbObject_H
#define _NaDbObject_H

#ifdef NAKGS_EXPORTS
#define NAKGS_API __declspec(dllexport)
#else
#define NAKGS_API __declspec(dllimport)
#endif

#include "NaDbTypeEnums.h"
#include "NaDbMaterial.h"
#include <NaGeBoundingBox.h>
#include <NaGeGeometry.h>

#include <GL/gl.h>
#include <GL/glu.h>

class NaDbCurve;
class NaDbText;
class NaDbPlane;
class NaDbPoint;
class NaDbSurface;
class NaDbAxisSystem;
class NaDbOneAxis;
class NaDbTrihedron;
class NaDbGrid;

class NAKGS_API NaDbObject
{
public:
	NaDbObject();
	virtual ~NaDbObject();
	virtual NaDbObject* Copy() = 0;
	virtual void DefineDisplay() = 0;
	virtual void Display(const GsDisplayMode& = GLWIREFRAME) = 0;
	virtual void Hilight(const GsDisplayMode&) = 0;
	virtual void SetColor(const GLubyte&, const GLubyte&, const GLubyte&);
	virtual void GetColor(GLubyte*) const;
	virtual DbObjectType GLObjType() const;
	virtual NaGeGeometry* Geometry() const { return 0; }
	virtual void MakeHidden(const bool& flag) { m_bHide = flag; }
	virtual bool IsHidden() const { return m_bHide; }

	unsigned long int GetObjID() const { return glObjID; }
	void SetDisplayMode(const GsDisplayMode& );
	GsDisplayMode GetDisplayMode() const;
	void SetMaterial(const GsMaterialName&);
	void SetMaterial(const NaDbMaterial&);
	NaDbMaterial GetMaterial() const;
	void SetBoundingBox(const NaGeBoundingBox&);
	NaGeBoundingBox GetBoundingBox() const;
	bool IsOfType(const DbObjectType&) const;
	int GetCount() const { return glObjCount; }

	void AddRef();
	int DelRef();
protected:
	void ApplyMaterial();
protected:
	DbObjectType glObjType;
	static int glObjCount;
	unsigned long int glObjID;
	GsDisplayMode displayMode;
	NaDbMaterial itsMaterial;
	GLfloat  ambiMat[4];
	GLfloat  diffMat[4];
	GLfloat  specMat[4];
	GLfloat  emisMat[4];
	GLfloat  coloMat[4];
	GLfloat shine;
	GLdouble Matl[13];
	GLubyte itsRed;
	GLubyte itsGreen;
	GLubyte itsBlue;
	GLubyte itsShadeRed;
	GLubyte itsShadeGreen;
	GLubyte itsShadeBlue;
	GLubyte itsTransparency;
	GLuint list;
	GLuint listNum;
	NaGeBoundingBox itsBox;
	bool m_bHide;
	bool firstTime;

	int m_nRef;
};

//helper function to draw torus... removes 'glut' dependency
NAKGS_API void drawTorus(int numMajor, int numMinor, float majorRadius, float minorRadius);

#endif /* _NaDbObject_H */
