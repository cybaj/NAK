/***************************************************************************
 *            NaDbAxisSystem.h
 *
 ****************************************************************************/


#ifndef _GLAXISSYSTEM_H
#define _GLAXISSYSTEM_H

#ifdef NAKGS_EXPORTS
#define NAKGS_API __declspec(dllexport)
#else
#define NAKGS_API __declspec(dllimport)
#endif

#include "NaDbObject.h"
#include <NaGeOneAxis.h>
#include <NaGeAxisSystem.h>
#include <NaGePoint3D.h>

class NAKGS_API NaDbAxisSystem : public NaDbObject  
{
public:
	NaDbAxisSystem(const NaGeAxisSystem& Ax, const int& length = 100, const int& arrow = 10);
	virtual ~NaDbAxisSystem();
	virtual NaDbObject* Copy();
	virtual void DefineDisplay();
	virtual void Display(const GsDisplayMode& = GLWIREFRAME);
	virtual void Hilight(const GsDisplayMode&);
	void SetLength(const int& len) { itsLength = len; }
	void SetArrowSize(const int& arr) { itsArrow = arr; }
	NaGeAxisSystem GetAxis() const { return itsAxis; }
	int GetLength() const { return itsLength; }
	int GetArrowSize() const { return itsArrow; }
	void ComputeBoundLimits();
	virtual NaGeGeometry* Geometry() const;
private:
	void DrawArrow(const NaGeOneAxis& theAxis);
private:
	NaGeAxisSystem itsAxis;
	int itsLength;
	int itsArrow;
};

#endif /* _GLAXISSYSTEM_H */
