// GLView.cpp : implementation file
//

#include "stdafx.h"
#include "NaGsView.h"
#include "NaGeGeomException.h"
#include "ListOfPoint3D.h"
#include "ListIteratorOfListOfPoint3D.h"
#include "ListException.h"
#include "WGL_ARB_multisample.h"
#include "NaDbApi.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// NaGsView

NaGsView::NaGsView(CWnd* pWnd, NaGsDisplayContext* ctx) : m_ptrWnd(pWnd), m_theContext(ctx)
{
	m_xRot = -45.0f;
	m_zRot = -45.0f;
	m_yRot = 0;
	m_xTrans = m_yTrans = m_zTrans = 0.0f;

	m_myCamera = new NaDbCamera();

	m_myViewType = GLAXONVIEW;
	m_myProjType = GLORTHOGRAPHIC;

	m_nRange = 500;

	m_bkRed = 134 / 255.0;
	m_bkGreen = 193 / 255.0;
	m_bkBlue = 239 / 255.0;

	m_displayMode = GLSHADED;

	m_antialias = false;

	//1
	m_colorv[0].amb[0] =  0.0F;	m_colorv[0].amb[1] =  0.0F;	m_colorv[0].amb[2] =  0.0F;
	m_colorv[0].diff[0] =  0.1F;	m_colorv[0].diff[1] =  0.6F;	m_colorv[0].diff[2] =  0.3F;
	m_colorv[0].spec[0] =  1.0F;	m_colorv[0].spec[1] =  1.0F;	m_colorv[0].spec[2] =  1.0F;
	m_colorv[0].ratio =  0.75F;
	m_colorv[0].indexes[0] =  0;	m_colorv[0].indexes[1] =  0;	m_colorv[0].indexes[2] =  0;

	//2
	m_colorv[1].amb[0] =  0.0F;	m_colorv[1].amb[1] =  0.0F;	m_colorv[1].amb[2] =  0.0F;
	m_colorv[1].diff[0] =  0.0F;	m_colorv[1].diff[1] =  0.2F;	m_colorv[1].diff[2] =  0.5F;
	m_colorv[1].spec[0] =  1.0F;	m_colorv[1].spec[1] =  1.0F;	m_colorv[1].spec[2] =  1.0F;
	m_colorv[1].ratio =  0.75F;
	m_colorv[1].indexes[0] =  0;	m_colorv[1].indexes[1] =  0;	m_colorv[1].indexes[2] =  0;

	//3
	m_colorv[2].amb[0] =  0.0F;	m_colorv[2].amb[1] =  0.05F;	m_colorv[2].amb[2] =  0.05F;
	m_colorv[2].diff[0] =  0.6F;	m_colorv[2].diff[1] =  0.0F;	m_colorv[2].diff[2] =  0.8F ;
	m_colorv[2].spec[0] =  1.0F;	m_colorv[2].spec[1] =  1.0F;	m_colorv[2].spec[2] =  1.0F ;
	m_colorv[2].ratio =  0.75F;
	m_colorv[2].indexes[0] =  0;	m_colorv[2].indexes[1] =  0;	m_colorv[2].indexes[2] =  0 ;

	m_ZoomON = false;
	m_PanON = false;
	m_RotON = false;

	m_gridOn = false;

	myTrihedron = new NaDbTrihedron;
	myGrid = new NaDbGrid;

	InitGL();

}

NaGsView::~NaGsView()
{
	ExitGsModule();

	delete myTrihedron;
	delete myGrid;
	delete m_myCamera;
	::wglDeleteContext(m_hRC);
	m_ptrWnd->ReleaseDC(m_ptrWnd->GetDC());
}

/////////////////////////////////////////////////////////////////////////////
// NaGsView drawing

void NaGsView::Draw()
{
	// ������ ���ؽ�Ʈ ������ Ȯ��
	::wglMakeCurrent(m_hDC,m_hRC);

	// ������ �Լ��� ȣ����
	RenderScene(GL_RENDER);
	
	// ��� ������
	::SwapBuffers(m_hDC);

	// �ٸ� ������ ���ؽ�Ʈ�� ����� �� �ֵ��� �ʱⰪ ���� ����
	::wglMakeCurrent(m_hDC,NULL);
}

/////////////////////////////////////////////////////////////////////////////

void NaGsView::ReSize(int cx, int cy) 
{
	
	// TODO: Add your message handler code here
	::wglMakeCurrent(m_hDC,m_hRC);
			
	GLsizei w, h;
	w = cx;
	h = cy;

	// ������ �Ҵ�ó��
	if (h==0) h=1;
	if(w==0) w=1;
	
	::glViewport(0, 0, w, h);

	// ��ǥ�� �ý����� ������
	::glMatrixMode(GL_PROJECTION);
	::glLoadIdentity();

	if(m_myProjType == GLORTHOGRAPHIC)//���� ����
    {
		if(w <= h)
			glOrtho(-m_nRange-m_xTrans, m_nRange-m_xTrans, -(m_nRange*h/w)-m_yTrans,
				(m_nRange*h/w)-m_yTrans, -(m_nRange*5000.0f)-m_zTrans, (m_nRange*5000.0f)-m_zTrans);
		else
			glOrtho(-(m_nRange*w/h)-m_xTrans, (m_nRange*w/h)-m_xTrans, -m_nRange-m_yTrans,
				m_nRange-m_yTrans, -m_nRange*5000.0f, m_nRange*5000.0f);

    }

    else if(m_myProjType == GLPERSPECTIVE)//���� ����
    {
		if(w <= h)
			gluPerspective(30, (GLdouble)h/(GLdouble)w, 1, m_nRange*5000.0f);
		else
			gluPerspective(30, (GLdouble)w/(GLdouble)h, 1, m_nRange*5000.0f);
		glTranslatef(0, 0, -m_nRange*4);
    }

	::glMatrixMode(GL_MODELVIEW);
	::glLoadIdentity();

	::wglMakeCurrent(m_hDC,NULL);
}

void NaGsView::Refresh()
{
	m_ptrWnd->Invalidate(FALSE);
}

void NaGsView::InitGL() 
{
	int nPixelFormat = 0;					// Pixel format index
	m_hDC = m_ptrWnd->GetDC()->m_hDC;		// Get the Device context

	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),	// Size of this structure
		1,								// Version of this structure	
		PFD_DRAW_TO_WINDOW |			// Draw to Window (not to bitmap)
		PFD_SUPPORT_OPENGL |			// Support OpenGL calls in window
		PFD_DOUBLEBUFFER,				// Double buffered mode
		PFD_TYPE_RGBA,					// RGBA Color mode
		24,								// Want 24bit color 
		0,0,0,0,0,0,					// Not used to m_select mode
		0,0,							// Not used to m_select mode
		0,0,0,0,0,						// Not used to m_select mode
		32,								// Size of depth buffer
		0,								// Not used to m_select mode
		0,								// Not used to m_select mode
		PFD_MAIN_PLANE,					// Draw in main plane
		0,								// Not used to m_select mode
		0,0,0 };						// Not used to m_select mode

	OSVERSIONINFO osvi = { 0 };

	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;

	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	if (!GetVersionEx(&osvi))
		throw std::runtime_error("InitGL() failed.");

	// ������ ��Ÿ ���� �������� ����
	if (osvi.dwMajorVersion > 6 || (osvi.dwMajorVersion == 6 && osvi.dwMinorVersion >= 0))
		pfd.dwFlags |= PFD_SUPPORT_COMPOSITION;

	//
	ChooseBestMultiSampleAntiAliasingPixelFormat(nPixelFormat, m_msaaSamples);

	//DC�� �ʼ� ���� ��ũ���� 
	if (!nPixelFormat)
		nPixelFormat = ChoosePixelFormat(m_hDC, &pfd);

	//����̽� ���ؽ�Ʈ �� �����ȼ� ���� �� ������
	if (!SetPixelFormat(m_hDC, nPixelFormat, &pfd))
		throw std::runtime_error("SetPixelFormat() failed.");

	//������ ���ؽ�Ʈ ����
	if (!(m_hRC = wglCreateContext(m_hDC)))
		throw std::runtime_error("wglCreateContext() failed.");

	//������ ���ؽ�Ʈ�� Ȯ�� , �ʱ�ȭ�� ���� �� �� ������ ����
	if (!wglMakeCurrent(m_hDC, m_hRC))
		throw std::runtime_error("wglMakeCurrent() failed.");

	//NAKGs����� �Լ��� ȣ���Ͽ� �ؽ��� ������ ������
	InitGsModule(m_hDC, m_hRC);

	glClearColor(m_bkRed, m_bkGreen, m_bkBlue, 1.0);

	wglMakeCurrent(m_hDC, NULL);

	// Create the palette if needed
	InitializePalette();
}

// �ȷ�Ʈ �ʱ�ȭ �Լ�
void NaGsView::InitializePalette(void)
{
	PIXELFORMATDESCRIPTOR pfd;
    LOGPALETTE* pPal;
    int pixelFormat = GetPixelFormat(m_hDC);
    int paletteSize;

    DescribePixelFormat(m_hDC, pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

    /*
    ** Determine if a palette is needed and if so what size.
    */
    if (pfd.dwFlags & PFD_NEED_PALETTE) 
	{
		paletteSize = 1 << pfd.cColorBits;
    }else 
	if (pfd.iPixelType == PFD_TYPE_COLORINDEX) 
	{
		paletteSize = 4096;
    }else 
	{
		return;
    }

    pPal = (LOGPALETTE*)
	malloc(sizeof(LOGPALETTE) + paletteSize * sizeof(PALETTEENTRY));
    pPal->palVersion = 0x300;
    pPal->palNumEntries = paletteSize;

    if (pfd.iPixelType == PFD_TYPE_RGBA) 
	{
		/*
		** Fill the logical paletee with RGB color ramps
		*/
		int redMask = (1 << pfd.cRedBits) - 1;
		int greenMask = (1 << pfd.cGreenBits) - 1;
		int blueMask = (1 << pfd.cBlueBits) - 1;
		int i;

		for (i=0; i<paletteSize; ++i) 
		{
			pPal->palPalEntry[i].peRed =
				(((i >> pfd.cRedShift) & redMask) * 255) / redMask;
			pPal->palPalEntry[i].peGreen =
				(((i >> pfd.cGreenShift) & greenMask) * 255) / greenMask;
			pPal->palPalEntry[i].peBlue =
				(((i >> pfd.cBlueShift) & blueMask) * 255) / blueMask;
			pPal->palPalEntry[i].peFlags = 0;
		}
    }else 
	{
		int numRamps = NUM_COLORS;
		int rampSize = (paletteSize - 20) / numRamps;
		int extra = (paletteSize - 20) - (numRamps * rampSize);
		int i, r;

		GetSystemPaletteEntries(m_hDC, 0, paletteSize, &pPal->palPalEntry[0]);

		for (r=0; r<numRamps; ++r) 
		{
			int rampBase = r * rampSize + 10;
			PALETTEENTRY *pe = &pPal->palPalEntry[rampBase];
			int diffSize = (int) (rampSize * m_colorv[r].ratio);
			int specSize = rampSize - diffSize;

			for (i=0; i<rampSize; ++i) 
			{
				GLfloat *c0, *c1;
				GLint a;
	
				if (i < diffSize) 
				{
					c0 = m_colorv[r].amb;
					c1 = m_colorv[r].diff;
					a = (i * 255) / (diffSize - 1);
				}else 
				{
					c0 = m_colorv[r].diff;
					c1 = m_colorv[r].spec;
					a = ((i - diffSize) * 255) / (specSize - 1);
				}

				pe[i].peRed = (BYTE) (a * (c1[0] - c0[0]) + 255 * c0[0]);
				pe[i].peGreen = (BYTE) (a * (c1[1] - c0[1]) + 255 * c0[1]);
				pe[i].peBlue = (BYTE) (a * (c1[2] - c0[2]) + 255 * c0[2]);
				pe[i].peFlags = PC_NOCOLLAPSE;
			}

			m_colorv[r].indexes[0] = rampBase;
			m_colorv[r].indexes[1] = rampBase + (diffSize-1);
			m_colorv[r].indexes[2] = rampBase + (rampSize-1);
		}

		for (i=0; i<extra; ++i) 
		{
			int index = numRamps*rampSize+10+i;
			PALETTEENTRY *pe = &pPal->palPalEntry[index];

			pe->peRed = (BYTE) 0;
			pe->peGreen = (BYTE) 0;
			pe->peBlue = (BYTE) 0;
		    pe->peFlags = PC_NOCOLLAPSE;
		}
    }

   m_hPalette2 = CreatePalette(pPal);
   free(pPal);

    if(m_hPalette2) 
	{
		SelectPalette(m_hDC, m_hPalette2, FALSE);
		RealizePalette(m_hDC);
    }		
	
}

BOOL NaGsView::EnableRC(BOOL bEnable)
{
	if(bEnable)
	{
		if(!wglMakeCurrent(m_hDC, m_hRC))
		{
			CString err("NaGsView::EnableRC - wglMakeCurrent failed\n");
			MessageBox(0, err, _T("OpenGL ERROR"), MB_OK);
			return FALSE;
		}
	}
	else
		wglMakeCurrent(m_hDC, NULL);

	return TRUE;
}

BOOL NaGsView::QueryNewPalette() 
{
	int nRet;
	// �ȷ�Ʈ �� ������ٸ�
	if((HPALETTE)m_GLPalette)
	{
		//���� ��ġ ���ؽ�Ʈ �� �ȷ�Ʈ �� �����մϴ�
		SelectPalette(m_hDC, (HPALETTE)m_GLPalette, FALSE);

		//�ý��� �ȷ�Ʈ �� ���� ���õ� �ȷ�Ʈ���� �� �׸�
		//��ȯ ���� ���� �� �ȷ�Ʈ �׸� �� ���Դϴ�.
		nRet = RealizePalette(m_hDC);

		//���� ���� �ķ�Ʈ�� �ٽ� ĥ��
		m_ptrWnd->InvalidateRect(NULL,FALSE);

	}
	return nRet;
}

void NaGsView::PaletteChanged() 
{
	
		// ��ġ ���ؽ�Ʈ �� �ȷ�Ʈ �� ����
		SelectPalette(m_hDC,(HPALETTE)m_GLPalette,FALSE);

		//�ý��� �ȷ�Ʈ �� �� �׸�
		RealizePalette(m_hDC);
				
		//�����
		UpdateColors(m_hDC);
}

void NaGsView::RenderScene(GLenum mode)
{
	// Clear the window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	if(m_antialias)
	{
		glEnable (GL_LINE_SMOOTH);
		glEnable (GL_BLEND);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glHint (GL_LINE_SMOOTH_HINT, GL_NICEST);
	    glLineWidth (1.125);
		glDepthFunc(GL_LESS);
		glEnable(GL_DEPTH_TEST);
	}
	else
	{
		glDisable (GL_LINE_SMOOTH);
		glLineWidth (1);
		glDisable (GL_BLEND);
	}

	glPushMatrix();

	m_myCamera->Render();

	//���� ���� ȸ��
	glRotatef(m_xRot,1,0,0);
	glRotatef(m_yRot,0,1,0);
	glRotatef(m_zRot,0,0,1);

	myTrihedron->SetSize(m_nRange/2);
	myTrihedron->Display();

	if(m_gridOn)
		myGrid->Display();

	//���ؽ�Ʈ�� ������� ������
	m_theContext->Render(m_displayMode);
	
	glPopMatrix();

	glFlush();
}

void NaGsView::ZoomView(CPoint dPoint, CPoint mPoint)
{
	if(!m_ZoomON)
		m_DownPoint = dPoint;
	m_ZoomON = true;

	if(m_DownPoint.x > mPoint.x || m_DownPoint.y < mPoint.y)
		m_nRange *= 1.05;
	else
		m_nRange /= 1.05;

	m_DownPoint = mPoint;

	CRect rect;
	m_ptrWnd->GetClientRect(&rect);

	int w = rect.Width();
	int h = rect.Height();

	ReSize(w, h);

}

void NaGsView::PanView(CPoint dPoint, CPoint mPoint)
{
	if(!m_PanON)
		m_DownPoint = dPoint;
	m_PanON = true;
	CSize pan = m_DownPoint - mPoint;
	m_DownPoint = mPoint;	

	m_myCamera->StrafeRight(0.01*m_nRange/2*pan.cx);
	m_myCamera->Move(F3dVector(0.0,-0.01*m_nRange/2*pan.cy,0.0));

	m_DownPoint = mPoint;

	CRect rect;
	m_ptrWnd->GetClientRect(&rect);

	int w = rect.Width();
	int h = rect.Height();

	ReSize(w, h);
}

void NaGsView::RotateView(CPoint dPoint, CPoint mPoint)
{
	if(!m_RotON)
		m_DownPoint = dPoint;
	m_RotON = true;
	CSize rotate = m_DownPoint - mPoint;
	m_myCamera->RotateX(rotate.cy/2);
	m_myCamera->RotateY(rotate.cx/2);
	m_myViewType = GLUNDEFINEDVIEW;
	m_DownPoint = mPoint;
}

void NaGsView::TopView() 
{
	// TODO: Add your command handler code here
	m_xRot = 0;
	m_yRot = 0;
	m_zRot = 0;
	m_myViewType = GLTOPVIEW;
	m_myCamera->ResetCamera();
	Refresh();
}

void NaGsView::BottomView() 
{
	// TODO: Add your command handler code here
	m_xRot = -180;
	m_yRot = 0;
	m_zRot = 0;
	m_myViewType = GLBOTTOMVIEW;
	m_myCamera->ResetCamera();
	Refresh();
}

void NaGsView::FrontView() 
{
	// TODO: Add your command handler code here
	m_xRot = -90;
	m_yRot = 0;
	m_zRot = 0;
	m_myViewType = GLFRONTVIEW;
	m_myCamera->ResetCamera();
	Refresh();
}

void NaGsView::BackView() 
{
	// TODO: Add your command handler code here
	m_xRot = -90;
	m_yRot = 0;
	m_zRot = -180;
	m_myViewType = GLBACKVIEW;
	m_myCamera->ResetCamera();
	Refresh();
}

void NaGsView::LeftView() 
{
	// TODO: Add your command handler code here
	m_xRot = -90;
	m_yRot = 0;
	m_zRot = -90;
	m_myViewType = GLLEFTVIEW;
	m_myCamera->ResetCamera();
	Refresh();
}

void NaGsView::RightView() 
{
	// TODO: Add your command handler code here
	m_xRot = -90;
	m_yRot = 0;
	m_zRot = 90;
	m_myViewType = GLRIGHTVIEW;
	m_myCamera->ResetCamera();
	Refresh();
}

void NaGsView::AxonView() 
{
	// TODO: Add your command handler code here
	m_xRot = -45;
	m_yRot = 0;
	m_zRot = -45;
	m_myViewType = GLAXONVIEW;
	m_myCamera->ResetCamera();
	Refresh();
}

void NaGsView::SetProjectionType(const GsProjectionType& aType)
{
	m_myProjType = aType;
	CRect rect;
	m_ptrWnd->GetClientRect(&rect);

	int w = rect.Width();
	int h = rect.Height();

	ReSize(w, h);
	Refresh();
}

void NaGsView::FitAll() 
{
	// TODO: Add your command handler code here
	if(m_theContext->IsEmpty())
		return;
	FitView();
	CRect rect;
	m_ptrWnd->GetClientRect(&rect);

	int w = rect.Width();
	int h = rect.Height();

	ReSize(w, h);

	Refresh();
}

void NaGsView::ZoomWindow(CRect zcRect)
{		
	CRect rcRect;
	m_ptrWnd->GetClientRect(&rcRect);

	int rcWidth, rcHeight, zcWidth, zcHeight;
	CPoint rcCentre, zcCentre;
	int dx, dy, dw, dh;
	GLdouble wRatio, hRatio;
	GLdouble dRange;

	GLint viewport[4];
	GLdouble mvmatrix[16],projmatrix[16];
	GLint realy;

	GLdouble cx, cy, cz;
	GLdouble mx, my, mz;

	rcWidth = rcRect.Width();
	rcHeight = rcRect.Height();

	zcWidth = zcRect.Width();
	zcHeight = zcRect.Height();

	rcCentre = rcRect.CenterPoint();
	zcCentre = zcRect.CenterPoint();

	wglMakeCurrent(m_hDC,m_hRC);

	glPushMatrix();
	glGetIntegerv(GL_VIEWPORT,viewport);
	glGetDoublev(GL_MODELVIEW_MATRIX,mvmatrix);
	glGetDoublev(GL_PROJECTION_MATRIX,projmatrix);

	realy=viewport[3]-(GLint)zcCentre.y-1;
	gluUnProject((GLdouble)zcCentre.x, (GLdouble)realy, 0.5, mvmatrix, projmatrix, viewport,
				&mx, &my, &mz);

	realy=viewport[3]-(GLint)rcCentre.y-1;
	gluUnProject((GLdouble)rcCentre.x, (GLdouble)realy, 0.5, mvmatrix, projmatrix, viewport,
				&cx, &cy, &cz);

	glPopMatrix();

	dx = cx - mx;
	dy = cy - my;

	dw = rcWidth - zcWidth;
	dh = rcHeight - zcHeight;

	wRatio = (GLdouble) zcWidth/rcWidth;
	hRatio = (GLdouble) zcHeight/rcHeight;

	dRange = (wRatio < hRatio) ? hRatio : wRatio;

	m_nRange *= dRange/0.8;

	//m_xTrans += dx;
	//m_yTrans += dy;
	m_myCamera->StrafeRight(-dx);
	m_myCamera->MoveForwards(-dy);

	wglMakeCurrent(m_hDC,NULL);

	ReSize(rcWidth, rcHeight);

	Refresh();
}

void NaGsView::ResetView() 
{
	// TODO: Add your command handler code here
	m_xRot = -45;
	m_yRot = 0;
	m_zRot = -45;
	m_xTrans = 0;
	m_yTrans = 0;
	m_zTrans = 0;
	m_nRange = 500;
	m_myCamera->ResetCamera();
	m_myViewType = GLAXONVIEW;

	CRect rect;
	m_ptrWnd->GetClientRect(&rect);

	int w = rect.Width();
	int h = rect.Height();

	ReSize(w, h);

	Refresh();
}

void NaGsView::SetBackgroundColor(GLfloat r, GLfloat g, GLfloat b)
{
	m_bkRed = r;
	m_bkGreen = g;
	m_bkBlue = b;
	wglMakeCurrent(m_hDC, m_hRC);
	glClearColor(m_bkRed, m_bkGreen, m_bkBlue, 1.0f);
	::wglMakeCurrent(m_hDC, NULL);
	m_ptrWnd->InvalidateRect(NULL, FALSE);
}

void NaGsView::GetBackgroundColor(GLfloat& r, GLfloat& g, GLfloat& b)
{
	r = m_bkRed;
	g = m_bkGreen;
	b = m_bkBlue;
}

void NaGsView::SetDisplayMode(const GsDisplayMode& aMode)
{
	m_displayMode = aMode;
	m_ptrWnd->InvalidateRect(NULL, FALSE);
}

void NaGsView::SetAntiAliasing(const bool& mode)
{
	m_antialias = mode;
	m_ptrWnd->InvalidateRect(NULL, FALSE);
}

void NaGsView::SetGridOn(const bool& mode)
{
	m_gridOn = mode;
	m_ptrWnd->InvalidateRect(NULL, FALSE);
}

void NaGsView::SetGridPara(const NaGePlane& plane, const double& size, const double& step)
{
	myGrid->SetPlane(plane);
	myGrid->SetSize(size);
	myGrid->SetStep(step);
	m_ptrWnd->InvalidateRect(NULL, FALSE);
}

void NaGsView::PointToScreen(const NaGePoint3D& P, int& x, int& y)
{
	NaGePoint3D p = P;
	GLint viewport[4];
	GLdouble mvmatrix[16],projmatrix[16];
	GLdouble wx, wy, wz;
	::wglMakeCurrent(m_hDC,m_hRC);
	glPushMatrix();
	glRotatef(m_xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(m_yRot, 0.0f, 1.0f, 0.0f);
	glRotatef(m_zRot, 0.0f, 0.0f, 1.0f);
	glGetIntegerv(GL_VIEWPORT,viewport);
	glGetDoublev(GL_MODELVIEW_MATRIX,mvmatrix);
	glGetDoublev(GL_PROJECTION_MATRIX,projmatrix);
	gluProject((GLdouble)p.GetX(), p.GetY(), p.GetZ(), mvmatrix, projmatrix, viewport, &wx, &wy, &wz);
	wx = sround(wx);
	wy = sround(wy);
	x = (int)wx; y = (int)wy;
	glPopMatrix();
	::wglMakeCurrent(m_hDC,NULL);
}

void NaGsView::ScreenToPoint(const int& x, const int& y, NaGePoint3D&  P)
{
	CPoint point(x,y);
	GLint viewport[4];
	GLdouble mvmatrix[16],projmatrix[16];
	GLint realy;
	GLdouble wx, wy, wz;
	::wglMakeCurrent(m_hDC,m_hRC);
	glPushMatrix();
	glRotatef(m_xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(m_yRot, 0.0f, 1.0f, 0.0f);
	glRotatef(m_zRot, 0.0f, 0.0f, 1.0f);
	glGetIntegerv(GL_VIEWPORT,viewport);
	glGetDoublev(GL_MODELVIEW_MATRIX,mvmatrix);
	glGetDoublev(GL_PROJECTION_MATRIX,projmatrix);
	realy=viewport[3]-(GLint)point.y-1;
	gluUnProject((GLdouble)point.x, (GLdouble)realy, 0.5, mvmatrix, projmatrix, viewport,
				&wx, &wy, &wz);
	P.SetParam(wx, wy, wz);
	glPopMatrix();
	::wglMakeCurrent(m_hDC,NULL);
}

void NaGsView::FitView()
{
	GLint viewport[4];
	GLdouble mvmatrix[16],projmatrix[16];
	CRect volRect;
	GLdouble cx, cy, cz;
	GLdouble mx, my, mz;
	GLdouble lx, ly, lz, sx, sy, sz;
	NaGeBoundingBox B = m_theContext->GetBoundingBox();
	lx = B.XMax(); ly = B.YMax(); lz = B.ZMax();
	sx = B.XMin(); sy = B.YMin(); sz = B.ZMin();

	wglMakeCurrent(m_hDC, m_hRC);
	glPushMatrix();

	glRotatef(m_xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(m_yRot, 0.0f, 1.0f, 0.0f);
	glRotatef(m_zRot, 0.0f, 0.0f, 1.0f);

	glGetIntegerv(GL_VIEWPORT,viewport);
	glGetDoublev(GL_MODELVIEW_MATRIX,mvmatrix);
	glGetDoublev(GL_PROJECTION_MATRIX,projmatrix);

	gluProject(lx, ly, lz, mvmatrix, projmatrix, viewport,
				&mx, &my, &mz);

	gluProject(sx, sy, sz, mvmatrix, projmatrix, viewport,
				&cx, &cy, &cz);

	glPopMatrix();
	::wglMakeCurrent(m_hDC, NULL);

	volRect.SetRect(cx,cy,mx,my);
	volRect.NormalizeRect();

	Fit3d(volRect);
}

void NaGsView::Fit3d(CRect rect)
{	
	CRect zcRect = rect;
	CRect rcRect;
	m_ptrWnd->GetClientRect(&rcRect);

	int rcWidth, rcHeight, zcWidth, zcHeight;
	CPoint rcCentre, zcCentre;
	int dx, dy, dw, dh;
	GLdouble wRatio, hRatio;
	GLdouble dRange;

	GLint viewport[4];
	GLdouble mvmatrix[16],projmatrix[16];
	GLint realy;

	GLdouble cx, cy, cz;
	GLdouble mx, my, mz;

	rcWidth = rcRect.Width();
	rcHeight = rcRect.Height();

	zcWidth = zcRect.Width();
	zcHeight = zcRect.Height();

	rcCentre = rcRect.CenterPoint();
	zcCentre = zcRect.CenterPoint();

	::wglMakeCurrent(m_hDC, m_hRC);

	glPushMatrix();

	glGetIntegerv(GL_VIEWPORT,viewport);
	glGetDoublev(GL_MODELVIEW_MATRIX,mvmatrix);
	glGetDoublev(GL_PROJECTION_MATRIX,projmatrix);

	realy=viewport[3]-(GLint)zcCentre.y-1;
	gluUnProject((GLdouble)zcCentre.x, (GLdouble)realy, 0.5, mvmatrix, projmatrix, viewport,
				&mx, &my, &mz);

	realy=viewport[3]-(GLint)rcCentre.y-1;
	gluUnProject((GLdouble)rcCentre.x, (GLdouble)realy, 0.5, mvmatrix, projmatrix, viewport,
				&cx, &cy, &cz);

	glPopMatrix();

	::wglMakeCurrent(m_hDC, NULL);

	dx = cx - mx;
	dy = cy - my;

	dw = rcWidth - zcWidth;
	dh = rcHeight - zcHeight;

	wRatio = (GLdouble) zcWidth/rcWidth;
	hRatio = (GLdouble) zcHeight/rcHeight;

	dRange = (wRatio < hRatio) ? hRatio : wRatio;

	m_nRange *= dRange/(double)0.8;

	m_myCamera->SetPosition(F3dVector(0,0,0));
	m_xTrans += dx;
	m_yTrans -= dy;
}

void NaGsView::Select(const int &x, const int &y)
{
	m_theContext->Select(this, x, y);
}

void NaGsView::MultiSelect(const int &x, const int &y)
{
	m_theContext->MultiSelect(this, x, y);
}

void NaGsView::SweepSelect(const CRect& swRect)
{
	m_theContext->SweepSelect(this, swRect);
}
//
void NaGsView::SelectTriangle(NaGePoint3D& pt)
{
	m_theContext->SelectTriangle(this, pt);
}

//��ŷ�� �Լ�
//��ŷ�� ���� ������ ũ���ε� �˳��� �൵ �ȴ�. ���ڶ�� �ȵȴ�.
//��ŷ���� ���Ǵ� �Է��� ���콺�� ��ǥ�̴�.
int NaGsView::ProcessSelection(const int& xPos, const int& yPos , const int& sensitivity)
{
	int id = 0;

	::wglMakeCurrent(m_hDC,m_hRC);

	// Space for selection buffer
	GLuint selectBuff[512];

	// Hit counter and viewport storeage
	GLint hits, viewport[4];

	//Picking�� ���� ���۸� �����Ѵ�.
	glSelectBuffer(512, selectBuff);
	
	//��ȯ�� �ʿ��� ������ viewport������ ���´�.
	glGetIntegerv(GL_VIEWPORT, viewport);

	// ������ �������� ��Ʈ���� ����.
	// ���ݺ��� �����Ǵ� ��Ʈ������ ������ �����ؾ� �Ѵ�. �⺻�� Modelview�ε� ���� ���������� �����ϴµ�
	// ���Ŀ� ���� ��ȯ�� ���� ����ϴ� ��ȯ�� ������ ���� �ʵ��� push matrix�� �ϴ°��̴�.
	glMatrixMode(GL_PROJECTION);
	//����
	glPushMatrix();

	//���⼭ ���ʹ� �������� ȭ�鿡 ���� �ʴ´�
	//��ǻ�Ͱ� ���콺�� ��� �ɸ����� ã�� ���ؼ� �ٽ� ȥ�� �׷����� �׷� �ܰ谡 ���۵ȴ�.
	glRenderMode(GL_SELECT);

	int n = sensitivity;
	glLoadIdentity();
	gluPickMatrix(xPos, viewport[3] - yPos, n, n, viewport);

	CRect rect;
	m_ptrWnd->GetClientRect(&rect);

	int w = rect.Width();
	int h = rect.Height();

	// Ortho Viewing
    if (w <= h) 
		glOrtho (-m_nRange-m_xTrans, 
				m_nRange-m_xTrans, 
				-(m_nRange*h/w)-m_yTrans,
				(m_nRange*h/w)-m_yTrans, 
				-(m_nRange*5000.0f)-m_zTrans, 
				(m_nRange*5000.0f)-m_zTrans);
	else 
		glOrtho (-(m_nRange*w/h)-m_xTrans,
				(m_nRange*w/h)-m_xTrans, 
				-m_nRange-m_yTrans,
				m_nRange-m_yTrans, 
				-m_nRange*5000.0f, 
				m_nRange*5000.0f);

	// ����� ����
	RenderScene(GL_SELECT);

	// Picknig�� �����ϸ鼭 ������ ���´�. ��, �༮���� �ϰ� �ƴ°� �˷��޶�� �ϴ� �Ͱ� ����.
	hits = glRenderMode(GL_RENDER);

	// �տ��� ������ �������� ��Ʈ������ �����ϱ� ���� ������������ ����
	glMatrixMode(GL_PROJECTION);
	// ����
	glPopMatrix();

	// �ٽ� �׸��� �׸��� ���ؼ� �𵨺�� �����Ѵ�. �������ʹ� �ٽ� ȭ�鿡 �׷�����.
	glMatrixMode(GL_MODELVIEW);

	// If a single hit occured, m_display the info.
	if(hits)
	{
		id =  selectBuff[3];		
	}

	::wglMakeCurrent(m_hDC, NULL);

	return id;

}

int NaGsView::ProcessSweepSelection(const CRect& swRect, unsigned long int* id)
{
	GLint i;
	GLuint j;
	::wglMakeCurrent(m_hDC,m_hRC);

	// Space for selection buffer
	GLuint selectBuff[512];

	// Hit counter and viewport storeage
	GLint hits = 0, viewport[4];

	// Setup selection buffer
	glSelectBuffer(512, selectBuff);
	
	// Get the viewport
	glGetIntegerv(GL_VIEWPORT, viewport);

	// Switch to projection and save the matrix
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	// Change render mode
	glRenderMode(GL_SELECT);

	// Establish new clipping volume to be cube around
	// center point of sweeping rectangle and extending pixels
	// falling within the height and width of the sweep rectangle
	// in the vertical and horzontal direction
	glLoadIdentity();
	gluPickMatrix(swRect.CenterPoint().x, viewport[3] - swRect.CenterPoint().y, swRect.Width(), swRect.Height(), viewport);

	CRect rect;
	m_ptrWnd->GetClientRect(&rect);

	int w = rect.Width();
	int h = rect.Height();

	// Ortho Viewing
    if (w <= h) 
		glOrtho (-m_nRange-m_xTrans, m_nRange-m_xTrans, -(m_nRange*h/w)-m_yTrans,
		(m_nRange*h/w)-m_yTrans, -(m_nRange*5000.0f)-m_zTrans, (m_nRange*5000.0f)-m_zTrans);
	else 
		glOrtho (-(m_nRange*w/h)-m_xTrans, (m_nRange*w/h)-m_xTrans, -m_nRange-m_yTrans,
		m_nRange-m_yTrans, -m_nRange*5000.0f, m_nRange*5000.0f);

	// Draw the scene
	RenderScene(GL_SELECT);

	// Collect the hits
	hits = glRenderMode(GL_RENDER);

	// Restore the projection matrix
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	// Go back to modelview for normal rendering
	glMatrixMode(GL_MODELVIEW);

	// If hits occured, m_display the info.
	if(hits)
	{
		GLuint *ptr, names;
		ptr = (GLuint*) selectBuff;
		for(i=0; i < hits; i++)
		{
			names = *ptr;
			ptr++; ptr++; ptr++;
			for(j = 0; j < names; j++)
			{
				id[i] = *ptr;
				ptr++;
			}
		}
	}

	::wglMakeCurrent(m_hDC, NULL);

	return hits;
}

