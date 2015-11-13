// GLFont.cpp: implementation of the NaDbText class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "NaDbText.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

NaDbText::NaDbText(const string& st,		// I - String To Be Displayed
				 const NaGePoint3D& pos,	// I - Position Of Text In 3D Space
				 const char *tf,			// I - Font specification
				 int ht,					// I - Font height/size in pixels
				 int wt,					// I - Weight of font (bold, etc)
	             DWORD it,					// I - Text is italic
				 const TextAlign& al)		// I- Text Justification
				 : itsStr(st), itsPosition(pos), itsAlignment(al), typeface(tf),
					height(ht),
					weight(wt),
					italic(it)
{
	str = &itsStr[0];
	glObjType = GLFONT;
	glObjID = (int)glObjType + NaDbObject::GetCount();
	itsRed = 205;
	itsGreen = 205;
	itsBlue = 25;
	ComputeBoundLimits();
 }

NaDbText::~NaDbText()
{
}

NaDbObject* NaDbText::Copy() 
{
	AddRef();
	return (NaDbObject*)this;
}

bool NaDbText::SaveObject(FILE* fptr)
{
	return false;
}

void NaDbText::DrawString()
{
	glPushAttrib(GL_LIST_BIT);
    glListBase(base);
    glCallLists(itsStr.length(), GL_UNSIGNED_BYTE, itsStr.data());
    glPopAttrib();
	glDeleteLists(base, 256);
}

void NaDbText::DefineDisplay()
{
	glDisable(GL_LIGHTING);
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_DEPTH_TEST);

	HDC hdc = wglGetCurrentDC();
	HFONT  fontid;                     // Windows font ID
    int    charset;                    // Character set code

	unsigned char *ptr;        /* Pointer into string */
    int           width;       /* Width of string in pixels */

	/* Allocate m_display lists */
    base = glGenLists(256);

    /* Select a character set */
    if (_stricmp(typeface, "symbol") == 0)
        charset = SYMBOL_CHARSET;
    else
        charset = ANSI_CHARSET;

    /* Load the font */
    fontid = CreateFontA(height, 0, 0, 0, weight, italic, FALSE, FALSE,
                        charset, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS,
                        ANTIALIASED_QUALITY , DEFAULT_PITCH, typeface);

    SelectObject(hdc, fontid);

    /* Create bitmaps for each character */
    wglUseFontBitmaps(hdc, 0, 256, base);

    /* Get the width and height information for each character */
    GetCharWidth(hdc, 0, 255, fwidths);
    fheight = height;

	/* Figure out the width of the string in pixels... */
    for (ptr = (unsigned char*)str, width = 0; *ptr; ptr ++)
        width += fwidths[*ptr];

	//Set Font Color;
	glColor3ub(itsRed, itsGreen, itsBlue);
	glRasterPos3d(itsPosition.GetX(), itsPosition.GetY(), itsPosition.GetZ());
	/* Adjust the bitmap position as needed to justify the text */
    if (itsAlignment == RIGHT)
        glBitmap(0, 0, 0, 0, -width, 0, NULL);
    else if (itsAlignment == CENTER)
        glBitmap(0, 0, 0, 0, -width / 2, 0, NULL);
    /* Draw the string */
	DrawString();
}

void NaDbText::Display(const GsDisplayMode& dMode)
{
	DefineDisplay();
}

void NaDbText::Hilight(const GsDisplayMode& dMode)
{
	itsRed = 0;
	itsGreen = 255;
	itsBlue = 255;
	DefineDisplay();
}

void NaDbText::ComputeBoundLimits()
{
	NaGePoint3D P = itsPosition;
	unsigned char *ptr;        /* Pointer into string */
    int           width;       /* Width of string in pixels */
	/* Figure out the width of the string in pixels... */
    for (ptr = (unsigned char*)str, width = 0; *ptr; ptr ++)
        width += fwidths[*ptr];
	itsBox.SetLimits(P.GetX()-1, P.GetX()+1, P.GetY()-1, P.GetY()+1, P.GetZ()-1, P.GetZ()+1);
}
