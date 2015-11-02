
#if !defined(AFX_GLFONT_H__B9B714C5_7F4D_452D_A20F_B773A9CB0BF3__INCLUDED_)
#define AFX_GLFONT_H__B9B714C5_7F4D_452D_A20F_B773A9CB0BF3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef NAKGS_EXPORTS
#define NAKGS_API __declspec(dllexport)
#else
#define NAKGS_API __declspec(dllimport)
#endif

#include "NaDbObject.h"
#include "NaGePoint3D.h"

class NaGePoint3D;

enum TextAlign { CENTER = 0, LEFT, RIGHT };

class NaDbText : public NaDbObject  
{
public:
	NAKGS_API NaDbText(const string&, const NaGePoint3D&, const char *tf = "MS Sans Serif", int ht = 16,
		            int wt = 0, DWORD it = 0, const TextAlign& = LEFT);
	NAKGS_API virtual ~NaDbText();
	NAKGS_API void DrawString();
	NAKGS_API virtual NaDbObject* Copy();
	NAKGS_API virtual void DefineDisplay();
	NAKGS_API virtual void Display(const GsDisplayMode& = GLWIREFRAME);
	NAKGS_API virtual void Hilight(const GsDisplayMode&);
private:
	void ComputeBoundLimits();
private:
	GLuint base;        /* Display list number of first character */
    int    fwidths[256]; /* Width of each character in pixels */
    int    fheight;      /* Height of characters */
	NaGePoint3D itsPosition;
	TextAlign itsAlignment;
	const char *typeface; // I - Font specification
	int height;           // I - Font height/size in pixels
	int weight;           // I - Weight of font (bold, etc)
	DWORD italic;
	const char* str;
	std::string itsStr;
};

#endif // !defined(AFX_GLFONT_H__B9B714C5_7F4D_452D_A20F_B773A9CB0BF3__INCLUDED_)
