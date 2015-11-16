// NAKCoreCtrl.cpp : Implementation of the CNAKCoreCtrl ActiveX Control class.

#include "stdafx.h"
#include "NAKCore.h"
#include "NAKCoreCtrl.h"
#include "NAKCorePropPage.h"
#include "afxdialogex.h"


#include "NaDbCurve.h"
#include "NaDbPoint.h"
#include "NaDbText.h"
#include "NaDbTexture.h"
#include "NaDbAxisSystem.h"
#include "NaGeObjTexture.h"
#include "NaDbSurface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CNAKCoreCtrl, COleControl)

// Message map
BEGIN_MESSAGE_MAP(CNAKCoreCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
//	ON_WM_MOVE()
ON_WM_MOUSEMOVE()
ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

// Dispatch map

BEGIN_DISPATCH_MAP(CNAKCoreCtrl, COleControl)
	DISP_FUNCTION_ID(CNAKCoreCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CNAKCoreCtrl, "OpenObject", dispidOpenObject, OpenObject, VT_I4, VTS_BSTR)
	DISP_PROPERTY_NOTIFY_ID(CNAKCoreCtrl, "EffectRed", dispidEffectRed, m_EffectRed, OnEffectRedChanged, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CNAKCoreCtrl, "EffectGreen", dispidEffectGreen, m_EffectGreen, OnEffectGreenChanged, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CNAKCoreCtrl, "EffectBlue", dispidEffectBlue, m_EffectBlue, OnEffectBlueChanged, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CNAKCoreCtrl, "UVImage", dispidUVImage, m_UVImage, OnUVImageChanged, VT_BSTR)
	DISP_PROPERTY_NOTIFY_ID(CNAKCoreCtrl, "EffectGamma", dispidEffectGamma, m_EffectGamma, OnEffectGammaChanged, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CNAKCoreCtrl, "EffectContrast", dispidEffectContrast, m_EffectContrast, OnEffectContrastChanged, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CNAKCoreCtrl, "EffectBrightness", dispidEffectBrightness, m_EffectBrightness, OnEffectBrightnessChanged, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CNAKCoreCtrl, "EffectInvert", dispidEffectInvert, m_EffectInvert, OnEffectInvertChanged, VT_BOOL)
	DISP_FUNCTION_ID(CNAKCoreCtrl, "SaveObject", dispidSaveObject, SaveObject, VT_EMPTY, VTS_BSTR)
	DISP_FUNCTION_ID(CNAKCoreCtrl, "SubdivisionLoop", dispidSubdivisionLoop, SubdivisionLoop, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()

// Event map

BEGIN_EVENT_MAP(CNAKCoreCtrl, COleControl)
END_EVENT_MAP()

// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CNAKCoreCtrl, 1)
	PROPPAGEID(CNAKCorePropPage::guid)
END_PROPPAGEIDS(CNAKCoreCtrl)

// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CNAKCoreCtrl, "NAKCORE.NAKCoreCtrl.1",
	0xb26510e5, 0x118d, 0x4bdd, 0xa8, 0xce, 0xbe, 0x9e, 0xb3, 0xc1, 0x9, 0xa3)

// Type library ID and version

IMPLEMENT_OLETYPELIB(CNAKCoreCtrl, _tlid, _wVerMajor, _wVerMinor)

// Interface IDs

const IID IID_DNAKCore = { 0x6569F7A9, 0x67F, 0x43F1, { 0x8A, 0xC7, 0x80, 0xB2, 0x4D, 0x6B, 0x76, 0xDD } };
const IID IID_DNAKCoreEvents = { 0xD21F3221, 0xDFD, 0x4EB7, { 0x88, 0xBC, 0x9F, 0x57, 0x1, 0x9C, 0x53, 0x2F } };

// Control type information

static const DWORD _dwNAKCoreOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CNAKCoreCtrl, IDS_NAKCORE, _dwNAKCoreOleMisc)

// CNAKCoreCtrl::CNAKCoreCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CNAKCoreCtrl

BOOL CNAKCoreCtrl::CNAKCoreCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_NAKCORE,
			IDB_NAKCORE,
			afxRegApartmentThreading,
			_dwNAKCoreOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


// CNAKCoreCtrl::CNAKCoreCtrl - Constructor

CNAKCoreCtrl::CNAKCoreCtrl()
{
	InitializeIIDs(&IID_DNAKCore, &IID_DNAKCoreEvents);
	// TODO: Initialize your control's instance data here.
	m_lbutdown = false;
	m_mbutdown = false;
	m_rbutdown = false;
	m_winZoom = false;
	m_dShaded = true;
	m_antialiased = false;
	m_gridOn = false;
	m_coord.Format(_T(""));
	m_view.Format(_T(""));
	m_Pen = new CPen(PS_SOLID, 2, RGB(0, 0, 0));
}

// CNAKCoreCtrl::~CNAKCoreCtrl - Destructor

CNAKCoreCtrl::~CNAKCoreCtrl()
{
	// TODO: Cleanup your control's instance data here.
	delete m_Pen;
}

// CNAKCoreCtrl::OnDraw - Drawing function

void CNAKCoreCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& /* rcInvalid */)
{
	if (!pdc)
		return;

	// TODO: Replace the following code with your own drawing code.
	m_myView->Draw();

	//GDI
//	pdc->SetBkMode(0);
	pdc->SetTextColor(RGB(0, 0, 0));
	pdc->TextOut(1, 1, m_view);
	pdc->TextOut(100, 1, m_coord);
}

// CNAKCoreCtrl::DoPropExchange - Persistence support

void CNAKCoreCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.
}


// CNAKCoreCtrl::OnResetState - Reset control to default state

void CNAKCoreCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


// CNAKCoreCtrl::AboutBox - Display an "About" box to the user

void CNAKCoreCtrl::AboutBox()
{
	CDialogEx dlgAbout(IDD_ABOUTBOX_NAKCORE);
	dlgAbout.DoModal();
}


// CNAKCoreCtrl message handlers


int CNAKCoreCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
#ifdef _DEBUG
//	MessageBoxA(NULL, "Debugging Start!!!", "DEBUG", 0);
#endif
	m_dContext = new NaGsDisplayContext(this);
	m_myView = new NaGsView(this, m_dContext);

	m_view.Format(_T("시작"));

	//background 설정
	//void SetBackgroundColor(GLfloat, GLfloat, GLfloat);

	GLfloat red, green, blue;
	m_myView->GetBackgroundColor(red, green, blue);

	m_EffectRed = red * 255;
	m_EffectGreen = green * 255;
	m_EffectBlue = blue * 255;

	m_EffectGamma = 0;
	m_EffectContrast = 0;
	m_EffectBrightness = 0;
//	m_EffectInvert = FALSE;

	return 0;
}


void CNAKCoreCtrl::OnDestroy()
{
	COleControl::OnDestroy();

	// TODO: Add your message handler code here
	delete m_dContext;
	delete m_myView;
}


void CNAKCoreCtrl::OnSize(UINT nType, int cx, int cy)
{
	COleControl::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if (m_myView)
		m_myView->ReSize(cx, cy);
}

void CNAKCoreCtrl::DrawRectangle(const bool  Draw,	const LineStyle aLineStyle)
{
	static int m_DrawMode = R2_MERGEPENNOT;
	static int StoredMinX, StoredMaxX, StoredMinY, StoredMaxY;
	static 	bool m_IsVisible = false;
	static  LineStyle StoredLineStyle = aLineStyle;

	CPen* aOldPen;
	CClientDC clientDC(this);
	if (m_Pen) aOldPen = clientDC.SelectObject(m_Pen);
	clientDC.SetROP2(m_DrawMode);

	if (m_IsVisible) //  m_erase at the old position 
	{
		clientDC.MoveTo(StoredMinX, StoredMinY); clientDC.LineTo(StoredMinX, StoredMaxY);
		clientDC.LineTo(StoredMaxX, StoredMaxY);
		clientDC.LineTo(StoredMaxX, StoredMinY); clientDC.LineTo(StoredMinX, StoredMinY);
		m_IsVisible = false;
	}

	StoredMinX = min(m_myXmin, m_myXmax);    StoredMinY = min(m_myYmin, m_myYmax);
	StoredMaxX = max(m_myXmin, m_myXmax);    StoredMaxY = max(m_myYmin, m_myYmax);

	if (Draw) 
	{ // move : draw
		if (StoredLineStyle != aLineStyle) 
		{
			delete m_Pen;
			if (aLineStyle == Solid)
			{
				m_Pen = new CPen(PS_SOLID, 2, RGB(0, 0, 0)); m_DrawMode = R2_MERGEPENNOT;
			}
			else if (aLineStyle == Dot)
			{
				m_Pen = new CPen(PS_DOT, 1, RGB(0, 0, 0));   m_DrawMode = R2_XORPEN;
			}
			else if (aLineStyle == ShortDash)
			{
				m_Pen = new CPen(PS_DASH, 1, RGB(255, 0, 0));	m_DrawMode = R2_XORPEN;
			}
			else if (aLineStyle == LongDash)
			{
				m_Pen = new CPen(PS_DASH, 1, RGB(0, 0, 0));	m_DrawMode = R2_NOTXORPEN;
			}
			clientDC.SelectObject(m_Pen);
		}

		clientDC.SetROP2(m_DrawMode);
		clientDC.MoveTo(StoredMinX, StoredMinY); clientDC.LineTo(StoredMinX, StoredMaxY);
		clientDC.LineTo(StoredMaxX, StoredMaxY);
		clientDC.LineTo(StoredMaxX, StoredMinY); clientDC.LineTo(StoredMinX, StoredMinY);
		m_IsVisible = true;
	}

	if (m_Pen) clientDC.SelectObject(aOldPen);
}

void CNAKCoreCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	SetCapture();

	//  save the current mouse m_coordinate in min 
	m_myXmin = point.x;  m_myYmin = point.y;
	m_myXmax = point.x;  m_myYmax = point.y;

	m_lbutdown = true;
	m_lDownPnt = point;
	if (!(nFlags & MK_SHIFT) && !(nFlags & MK_CONTROL) && !m_winZoom)
	{
		m_myView->Select(point.x, point.y);

		NaGePoint3D C;
		m_myView->ScreenToPoint(point.x, point.y, C);
		m_coord.Format(_T("선택 위치 : X:%0.3lf Y:%0.3lf Z:%0.3lf"), C.GetX(), C.GetY(), C.GetZ());

		m_myView->SelectTriangle(C);

		InvalidateRect(NULL, FALSE);
	}
	if ((nFlags & MK_SHIFT) && !(nFlags & MK_CONTROL) && !m_winZoom)
	{
		m_myView->MultiSelect(point.x, point.y);
		InvalidateRect(NULL, FALSE);
	}

	COleControl::OnLButtonDown(nFlags, point);
}

void CNAKCoreCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_lbutdown = false;
	m_myView->StopZooming();

	if (!(nFlags & MK_SHIFT) && !(nFlags & MK_CONTROL) && !m_winZoom)
	{
		DrawRectangle(false);
		CRect rect(m_lDownPnt, point);
		rect.NormalizeRect();
		if (rect.Width() && rect.Height())
			m_myView->SweepSelect(rect);
		InvalidateRect(NULL, FALSE);
	}

	if (m_winZoom)
	{
		m_myXmax = point.x;  m_myYmax = point.y;
		DrawRectangle(false);
		CRect myZoomRect(m_myXmin, m_myYmax, m_myXmax, m_myYmin);
		if ((abs(m_myXmin - m_myXmax)>1) || (abs(m_myYmin - m_myYmax)>1))
			// Test if the zoom window size is not null
		{
			m_myView->ZoomWindow(myZoomRect);
		}
	}

	m_winZoom = false;
	ReleaseCapture();

	COleControl::OnLButtonUp(nFlags, point);
}

void CNAKCoreCtrl::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_mbutdown = true;
	m_mDownPnt = point;
	COleControl::OnMButtonDown(nFlags, point);
}

void CNAKCoreCtrl::OnMButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_mbutdown = false;
	m_myView->StopPanning();
	COleControl::OnMButtonUp(nFlags, point);
}

void CNAKCoreCtrl::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_rbutdown = true;
	m_rDownPnt = point;
	COleControl::OnRButtonDown(nFlags, point);
}

void CNAKCoreCtrl::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_rbutdown = false;
	m_myView->StopRotation();
	COleControl::OnRButtonUp(nFlags, point);
}


BOOL CNAKCoreCtrl::OnMouseWheel(UINT nFlags, short zDelta, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CPoint newPos = m_lDownPnt;
	if (zDelta < 0)
	{
		newPos.x += 1.0;
		m_myView->ZoomView(m_lDownPnt, newPos);
		m_lDownPnt.x -= 1.0;
		Invalidate(FALSE);
	}
	else
	{
		newPos.x -= 1.0;
		m_myView->ZoomView(m_lDownPnt, newPos);
		m_lDownPnt.x += 1.0;
		Invalidate(FALSE);
	}
	return COleControl::OnMouseWheel(nFlags, zDelta, point);
}

void CNAKCoreCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

//	if (m_lbutdown )//&& (nFlags & MK_CONTROL))
//	{
//		m_myView->ZoomView(m_lDownPnt, point);
//		Invalidate(FALSE);
//	}
	if (m_mbutdown )//&& (nFlags & MK_CONTROL))
	{
		m_myView->PanView(m_mDownPnt, point);
		Invalidate(FALSE);
	}
	if (m_rbutdown )//&& (nFlags & MK_CONTROL))
	{
		if (m_myView->GetViewType() == GLAXONVIEW ||
			m_myView->GetViewType() == GLUNDEFINEDVIEW)
		{
			m_myView->RotateView(m_rDownPnt, point);
			Invalidate(FALSE);
		}
		else
			m_coord.Format(_T("Axonometric View에서 회전지원"));
	}
	if (m_lbutdown && (nFlags & MK_CONTROL))// && !(nFlags & MK_SHIFT))
	{
		m_myXmax = point.x; m_myYmax = point.y;
		DrawRectangle(true, LongDash);
	}

	NaGePoint3D C;
	m_myView->ScreenToPoint(point.x, point.y, C);
	m_coord.Format(_T("마우스 위치 : X:%0.3lf Y:%0.3lf Z:%0.3lf"), C.GetX(), C.GetY(), C.GetZ());

	COleControl::OnMouseMove(nFlags, point);
}

LONG CNAKCoreCtrl::OpenObject(LPCTSTR strFilename)
{
	USES_CONVERSION;
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	::CWaitCursor aCur;

	m_dContext->DeleteAll();

	m_myView->EnableRC(TRUE);

	std::string colorMap;
	NaGeObjTexture us;
	NaDbTexture* pTexture = new NaDbTexture(&us, W2A(strFilename), m_EffectBrightness / 255.0, m_EffectContrast / 255.0, m_EffectGamma / 255.0, m_EffectInvert);
	//pTexture->AdjustColors(m_EffectBrightness/255.0, m_EffectContrast/ 255.0, m_EffectGamma/ 255.0, m_EffectInvert);
	pTexture->GetColorMap(colorMap);
	m_dContext->Display(pTexture);

	m_UVImage = colorMap.c_str();

	const CListOfPoint3D* pts = pTexture->GetPositionList();

	//NaGeLine3D line(pts->First(), pts->Last());
	//NaDbCurve* gP = new NaDbCurve(&line);
	//m_dContext->Display(gP);

	CString str;
	NaGePoint3D pt = us.PointAtPara(0.5, 0.5);
	str.Format(TEXT("Center : %.3f,%.3f,%.3f"), pts->First().GetX(), pts->First().GetY(), pts->First().GetZ());
	NaDbText* myFont = new NaDbText(W2A(str), pts->First());
	m_dContext->Display(myFont);

	m_myView->EnableRC(FALSE);

	return 0;
}

void CNAKCoreCtrl::SaveObject(LPCTSTR filename)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	m_myView->EnableRC(TRUE);
	m_dContext->SaveObject(filename);
	m_myView->EnableRC(FALSE);
}

void CNAKCoreCtrl::OnEffectRedChanged()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here
	m_myView->SetBackgroundColor(this->m_EffectRed / 255.0, this->m_EffectGreen / 255.0, this->m_EffectBlue / 255.0);
	SetModifiedFlag();
}


void CNAKCoreCtrl::OnEffectGreenChanged()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here
	m_myView->SetBackgroundColor(this->m_EffectRed / 255.0, this->m_EffectGreen / 255.0, this->m_EffectBlue / 255.0);
	SetModifiedFlag();
}


void CNAKCoreCtrl::OnEffectBlueChanged()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here
	m_myView->SetBackgroundColor(this->m_EffectRed / 255.0, this->m_EffectGreen / 255.0, this->m_EffectBlue / 255.0);
	SetModifiedFlag();
}


void CNAKCoreCtrl::OnUVImageChanged()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here

	SetModifiedFlag();
}


void CNAKCoreCtrl::OnEffectGammaChanged()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here

	SetModifiedFlag();
}


void CNAKCoreCtrl::OnEffectContrastChanged()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here

	SetModifiedFlag();
}


void CNAKCoreCtrl::OnEffectBrightnessChanged()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here

	SetModifiedFlag();
}


void CNAKCoreCtrl::OnEffectInvertChanged()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here

	SetModifiedFlag();
}



void CNAKCoreCtrl::SubdivisionLoop()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	m_myView->EnableRC(TRUE);
	m_dContext->SubdivisionLoop();
	m_myView->EnableRC(FALSE);
}
