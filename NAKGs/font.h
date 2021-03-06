/*
 * OpenGL Font Support Definitions from Chapter 7.
 *
 * Written by Michael Sweet.
 */

#ifndef _FONT_H_
#  define _FONT_H_

#ifdef NAKGS_EXPORTS
#define NAKGS_API __declspec(dllexport)
#else
#define NAKGS_API __declspec(dllimport)
#endif

/*
 * Include necessary headers.
 */

#  include <windows.h>
#  include <GL/gl.h>



/*
 * Font data structure...
 */

typedef struct
    {
    GLuint base;        /* Display list number of first character */
    int    widths[256]; /* Width of each character in pixels */
    int    height;      /* Height of characters */
    } _GLFONT;


/*
 * Prototypes...
 */

NAKGS_API _GLFONT	*FontCreate(HDC hdc, const char *typeface, int height,
		            int weight, DWORD italic);
NAKGS_API void	FontDestroy(_GLFONT *font);
NAKGS_API void	FontPrintf(_GLFONT *font, int align, const char *format, ...);
NAKGS_API void	FontPuts(_GLFONT *font, const char *s);

#endif /* !_FONT_H_ */
