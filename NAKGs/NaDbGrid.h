 
/***************************************************************************
 *            NaDbGrid.h
 *
 ****************************************************************************/


#ifndef _GLGRID_H
#define _GLGRID_H

#ifdef NAKGS_EXPORTS
#define NAKGS_API __declspec(dllexport)
#else
#define NAKGS_API __declspec(dllimport)
#endif

#include "NaDbObject.h"
#include <NaGePlane.h>
#include <NaGeOneAxis.h>

class NAKGS_API NaDbGrid : public NaDbObject  
{
public:
	NaDbGrid();
	NaDbGrid(const NaGePlane& plane, const double& size = 100, const double& step = 10);
	virtual ~NaDbGrid();
	void SetPlane(const NaGePlane& plane);
	void SetSize(const double& size);
	void SetStep(const double& step);
	NaGePlane GetPlane() const { return itsPlane; }
	double GetSize() const { return itsSize; }
	double GetStep() const { return itsStep; }
	virtual NaDbObject* Copy();
	virtual bool SaveObject(FILE* fptr);
	virtual void DefineDisplay();
	virtual void Display(const GsDisplayMode& = GLWIREFRAME);
	virtual void Hilight(const GsDisplayMode&) {;}
private:
	double itsSize;
	double itsStep;
	NaGePlane itsPlane;
	GLuint gridList;
private:
	void InitDisplayLists();
};

#endif /* _GLGRID_H */
