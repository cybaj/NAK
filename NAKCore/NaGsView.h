

#if !defined(AFX_GLVIEW_H__859711F8_BE5E_4EFB_9EAB_84708FB5E343__INCLUDED_)
#define AFX_GLVIEW_H__859711F8_BE5E_4EFB_9EAB_84708FB5E343__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GLView.h : header file
//

#include "NaGsDisplayContext.h"
#include "NaDbCamera.h"
#include "NaDbObject.h"
#include "NaDbTrihedron.h"
#include "NaDbGrid.h"

#include "NaGePoint3D.h"

#define NUM_COLORS (sizeof(m_colorv) / sizeof(m_colorv[0]))

/////////////////////////////////////////////////////////////////////////////
// NaGsView view

class NaGsDisplayContext;
class NaGsView
{
public:
	enum GsProjectionType {GLORTHOGRAPHIC, GLPERSPECTIVE};
public:
	NaGsView(CWnd* pWnd, NaGsDisplayContext* aContext);
	~NaGsView();

// Attributes
public:
	HGLRC		m_hRC;			// Rendering Context
	HDC			m_hDC;				// Device Context
	CPalette	m_GLPalette;	// Logical Palette
	HPALETTE	m_hPalette,
				m_hPalette2;

private:
	GLdouble m_nRange;
	GLdouble m_xRot;
	GLdouble m_yRot;
	GLdouble m_zRot;
	GLdouble m_xTrans;
	GLdouble m_yTrans;
	GLdouble m_zTrans;
	GLfloat m_bkRed;
	GLfloat m_bkGreen;
	GLfloat m_bkBlue;
	GsDisplayMode m_displayMode;
	bool m_antialias;

	NaDbTrihedron *myTrihedron;
	NaDbGrid* myGrid;

	// Color Indexes
	struct colorIndexState 
	{
		GLfloat amb[3];		/* ambient color / bottom of ramp */
		GLfloat diff[3];	/* diffuse color / middle of ramp */
		GLfloat spec[3];	/* specular color / top of ramp */
		GLfloat ratio;		/* ratio of diffuse to specular in ramp */
		GLint indexes[3];	/* where ramp was placed in palette */
	};

	colorIndexState m_colorv[3];

	CPoint m_DownPoint;
	bool m_ZoomON;
	bool m_PanON;
	bool m_RotON;

	bool m_gridOn;

	int	 m_msaaSamples;

// Operations
public:
	void InitGL();
	BOOL EnableRC(BOOL bEnable);
	void RenderScene(GLenum mode);
	void InitializePalette(void);

	void ZoomView(CPoint, CPoint);
	void PanView(CPoint, CPoint);
	void RotateView(CPoint, CPoint);

	void StopZooming(){ m_ZoomON = false; }
	void StopPanning(){ m_PanON = false; }
	void StopRotation(){ m_RotON = false; }

	void TopView();
	void BottomView();
	void FrontView();
	void BackView();
	void LeftView();
	void RightView();
	void AxonView();

	GsViewType GetViewType() const { return m_myViewType; }

	void SetProjectionType(const GsProjectionType& aType);
	GsProjectionType GetProjectionType() const { return m_myProjType; }


	void FitAll();
	void ZoomWindow(CRect zcRect);
	void ResetView();

	void PointToScreen(const NaGePoint3D& P, int& x, int& y);
	void ScreenToPoint(const int& x, const int& y, NaGePoint3D&  P);
	void FitView();
	void Fit3d(CRect zcRect);

	void SetBackgroundColor(GLfloat, GLfloat, GLfloat);
	void GetBackgroundColor(GLfloat&, GLfloat&, GLfloat&);
	void SetDisplayMode(const GsDisplayMode& aMode);

	void SetAntiAliasing(const bool& mode);

	void SetGridOn(const bool& mode);
	void SetGridPara(const NaGePlane& plane, const double& size, const double& step);

	void Select(const int& x, const int& y);
	void MultiSelect(const int& x, const int& y);
	void SweepSelect(const CRect& swRect);

	int  ProcessSelection(const int& x, const int& y, const int& sensitivity = 5);
	int  ProcessSweepSelection(const CRect& rect, unsigned long int* id);


	virtual void Draw();
	void ReSize(int cx, int cy);
	void Refresh();

	BOOL QueryNewPalette();
	void PaletteChanged();

private:
	CWnd* m_ptrWnd;
	NaGsDisplayContext* m_theContext;
	NaDbCamera* m_myCamera;
	GsViewType m_myViewType;
	GsProjectionType m_myProjType;
};


#endif // !defined(AFX_GLVIEW_H__859711F8_BE5E_4EFB_9EAB_84708FB5E343__INCLUDED_)
