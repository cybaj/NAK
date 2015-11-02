#pragma once

// NAKCoreCtrl.h : Declaration of the CNAKCoreCtrl ActiveX Control class.


// CNAKCoreCtrl : See NAKCoreCtrl.cpp for implementation.
class NaGsView;
class NaGsDisplayContext;
class CNAKCoreCtrl : public COleControl
{
	DECLARE_DYNCREATE(CNAKCoreCtrl)

// Constructor
public:
	CNAKCoreCtrl();

// Overrides
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

private:
	NaGsDisplayContext* m_dContext;
	NaGsView* m_myView;

	CString m_coord;
	CString m_date;
	CString m_time;
	CString m_view;

	bool m_lbutdown;
	bool m_mbutdown;
	bool m_rbutdown;

	CPoint m_lDownPnt;
	CPoint m_mDownPnt;
	CPoint m_rDownPnt;

	//mouse m_coordinate
	int m_myXmin;
	int m_myYmin;
	int m_myXmax;
	int m_myYmax;

	bool m_winZoom;
	bool m_dShaded;
	bool m_antialiased;
	bool m_gridOn;

public:
	enum LineStyle {
		dispidOpenObject = 1L,
		Solid, Dot, ShortDash, LongDash };
	CPen*  m_Pen;

protected:
	virtual void DrawRectangle(const bool  Draw = true,	const LineStyle aLineStyle = Solid);

// Implementation
protected:
	~CNAKCoreCtrl();

	DECLARE_OLECREATE_EX(CNAKCoreCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CNAKCoreCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CNAKCoreCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CNAKCoreCtrl)		// Type name and misc status

// Message maps
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	};
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
//	afx_msg void OnMove(int x, int y);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
protected:
	LONG OpenObject(LPCTSTR strFilename);
};

