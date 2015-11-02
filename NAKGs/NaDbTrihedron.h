

// NaDbTrihedron.h: interface for the NaDbTrihedron class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_NaDbTrihedron_H__F1DE074D_EC62_4F52_9890_7612816C931B__INCLUDED_)
#define _NaDbTrihedron_H__F1DE074D_EC62_4F52_9890_7612816C931B__INCLUDED_

#ifdef NAKGS_EXPORTS
#define NAKGS_API __declspec(dllexport)
#else
#define NAKGS_API __declspec(dllimport)
#endif

#include "NaDbObject.h"
#include "font.h"

class NAKGS_API NaDbTrihedron : public NaDbObject  
{
public:
	NaDbTrihedron();
	NaDbTrihedron(GLfloat size);
	virtual ~NaDbTrihedron();
	virtual NaDbObject* Copy() ;
	virtual void DefineDisplay();
	virtual void Display(const GsDisplayMode& = GLWIREFRAME);
	virtual void Hilight(const GsDisplayMode&);
	void SetSize(GLfloat size); 
private:
	GLfloat csSize;
	static GLuint list;
	GLUquadricObj* coneObj;
	GLuint base;            // base m_display list for the font set.
	GLuint triList;
	bool firstTime;
	_GLFONT *Font;
private:
	GLvoid BuildFont(GLvoid);
	void DrawText(char* string);
	void ComputeBoundLimits();
	void InitDisplayLists();

};

#endif // !defined(_NaDbTrihedron_H__F1DE074D_EC62_4F52_9890_7612816C931B__INCLUDED_)
