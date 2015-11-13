 
/***************************************************************************
 *            NaDbOneAxis.h
 *
 ****************************************************************************/


#ifndef _GLONEAXIS_H
#define _GLONEAXIS_H

#ifdef NAKGS_EXPORTS
#define NAKGS_API __declspec(dllexport)
#else
#define NAKGS_API __declspec(dllimport)
#endif

#include "NaDbObject.h"
#include <NaGeOneAxis.h>
#include <NaGeAxisSystem.h>
#include <NaGePoint3D.h>

class NAKGS_API NaDbOneAxis : public NaDbObject  
{
public:
	NaDbOneAxis(const NaGeOneAxis& Ax, const int& length = 100, const int& arrow = 10);
	virtual ~NaDbOneAxis();
	virtual NaDbObject* Copy();
	virtual bool SaveObject(FILE* fptr);
	virtual void DefineDisplay();
	virtual void Display(const GsDisplayMode& = GLWIREFRAME);
	virtual void Hilight(const GsDisplayMode&);
	void SetLength(const int& len) { itsLength = len; }
	void SetArrowSize(const int& arr) { itsArrow = arr; }
	NaGeOneAxis GetAxis() const { return itsAxis; }
	int GetLength() const { return itsLength; }
	int GetArrowSize() const { return itsArrow; }
	void ComputeBoundLimits();
	virtual NaGeGeometry* Geometry() const;
private:
	void DrawArrow(const NaGeOneAxis& theAxis);
private:
	NaGeOneAxis itsAxis;
	int itsLength;
	int itsArrow;
};

#endif /* _GLONEAXIS_H */
