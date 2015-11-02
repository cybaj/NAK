// GLPoint.cpp: implementation of the NaDbPoint class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "NaDbPoint.h"
#include "NaGeMMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

NaDbPoint::NaDbPoint(const NaGePoint3D& P, const GsPointMarker& M) : itsPoint(P), itsMarker(M)
{
	glObjType = GLPOINT;
	glObjID = (int)glObjType + NaDbObject::GetCount();
	itsRed = 255;
	itsGreen = 99;
	itsBlue = 25;
	ComputeBoundLimits();
}

NaDbPoint::~NaDbPoint()
{
}

NaDbObject* NaDbPoint::Copy() 
{
	AddRef();
	return (NaDbObject*)this;
}

NaGeGeometry* NaDbPoint::Geometry() const
{
	NaGePoint3D* pnt = new NaGePoint3D(itsPoint.GetX(), itsPoint.GetY(), itsPoint.GetZ());
	return pnt;
}

void NaDbPoint::DefineDisplay()
{
	glPushAttrib(GL_COLOR_BUFFER_BIT);
	glColor3ub(itsRed, itsGreen, itsBlue);
	glDisable(GL_LIGHTING);
	glEnable (GL_POINT_SMOOTH);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint (GL_POINT_SMOOTH_HINT, GL_NICEST);
	glPointSize (8);

	if(itsMarker == MARKER_POINT)
	{
		glBegin(GL_POINTS);
			glVertex3d(itsPoint.GetX(), itsPoint.GetY(), itsPoint.GetZ());
		glEnd();
	}
	else
		DrawMarker();

	glDisable (GL_POINT_SMOOTH);
	glPointSize (1);
	glDisable (GL_BLEND);
	glPopAttrib();
}

void NaDbPoint::Display(const GsDisplayMode&)
{
	DefineDisplay();
}

void NaDbPoint::Hilight(const GsDisplayMode&)
{
	itsRed = 0; itsGreen = 255; itsBlue = 255;
	DefineDisplay();
}

void NaDbPoint::ComputeBoundLimits()
{
	NaGePoint3D p = itsPoint;
	itsBox.SetLimits(p.GetX()-1, p.GetX()+1, p.GetY()-1, p.GetY()+1, p.GetZ()-1, p.GetZ()+1);
}

void NaDbPoint::DrawMarker()
{
	/*glDisable(GL_LIGHTING);
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_DEPTH_TEST);

	HDC hdc = wglGetCurrentDC();
	HFONT  fontid;                     // Windows font ID
    int    charset;                    // Character set code

	unsigned char *ptr;        // Pointer into string
    int           width;       // Width of string in pixels

	char* str;
	if(itsMarker == MARKER_PLUS)
		str = "+";
	if(itsMarker == MARKER_CROSS)
		str = "x";
	if(itsMarker == MARKER_STAR)
		str = "*";
	if(itsMarker == MARKER_CIRCLE)
		str = "o";

	LPCTSTR typface;
	if(itsMarker == MARKER_STAR)
		typface = "MS Mincho";
	else
		typface = "Courier";

	fheight = 24;

	// Allocate m_display lists
    base = glGenLists(256);

    charset = ANSI_CHARSET;

    // Load the font
    fontid = CreateFont(fheight, 0, 0, 0, 0, 0, FALSE, FALSE,
                        charset, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS,
                        ANTIALIASED_QUALITY , DEFAULT_PITCH, typface);

    SelectObject(hdc, fontid);

    // Create bitmaps for each character
    wglUseFontBitmaps(hdc, 0, 256, base);


    // Get the width and height information for each character
    GetCharWidth(hdc, 0, 255, fwidths);

	// Figure out the width of the string in pixels....
    for (ptr = (unsigned char*)str, width = 0; *ptr; ptr ++)
        width += fwidths[*ptr];

	//Set Font Color;
	glColor3ub(itsRed, itsGreen, itsBlue);
	glRasterPos3d(itsPoint.GetX(), itsPoint.GetY(), itsPoint.GetZ());
	// Adjust the bitmap position as needed to justify the text
    glBitmap(0, 0, 0, 0, -width / 2, -fheight/4, NULL);
    // Draw the string
	glPushAttrib(GL_LIST_BIT);
    glListBase(base);
    glCallLists(strlen(str), GL_UNSIGNED_BYTE, str);
    glPopAttrib();
	glDeleteLists(base, 256);*/
}
