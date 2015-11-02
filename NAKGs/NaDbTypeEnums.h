/***************************************************************************
 *            NaDbTypeEnums.h
 ****************************************************************************/


#ifndef _NADBTYPEENUMS_H
#define _NADBTYPEENUMS_H

typedef enum  { 
	GLTOPVIEW, 
	GLBOTTOMVIEW, 
	GLFRONTVIEW, 
	GLBACKVIEW,
    GLLEFTVIEW, 
	GLRIGHTVIEW, 
	GLAXONVIEW, 
	GLUNDEFINEDVIEW} GsViewType;

//Every NaDbObject created in the context must have a unique id;
typedef enum { 
	GLCURVE = 123456, 
	GLFONT = 234561, 
    GLPLANE = 345612, 
	GLPOINT = 456123, 
    GLSURFACE = 561234, 
	GLTEXTURE = 561235,
	GLTRIHEDRON = 612345, 
    GLAXIS = 876543, 
	GLONEAXIS = 765432, 
	GLCUTTER = 876543, 
	GLSIRUS = 987654} DbObjectType;

//Somehow I dont like the GL_POINTS primitive of OpenGL
//So creating some markers for point m_display
typedef enum { 
	MARKER_POINT, 
	MARKER_PLUS, 
	MARKER_CROSS, 
	MARKER_STAR, 
	MARKER_CIRCLE 
} GsPointMarker;

typedef enum { 
	LINE_SOLID, 
	LINE_DOTTED, 
	LINE_DASHED, 
	LINE_DASHDOTTED 
} GsLineStyle;

typedef enum { 
	GLSHADED, 
	GLWIREFRAME, 
	GLHLREMOVED 
} GsDisplayMode;

typedef enum { 
	GLORTHOGRAPHIC, 
	GLPERSPECTIVE 
} GsProjectionType;

// Some Standard Materials
// P_ prefix denotes Polished
typedef enum {
	ALUMINIUM, 
	BRASS, 
	BRONZE, 
	P_BRONZE, 
	CHROME, 
	COPPER, 
	P_COPPER, 
	GOLD, 
	P_GOLD,
    PEWTER, 
	SILVER, 
	P_SILVER, 
	STEEL, 
	EMERALD, 
	JADE, 
	OBSIDIAN, 
	PEARL, 
	RUBY, 
	TURQUOISE, 
	PLASTIC, 
    RUBBER, 
	BLACK_PLASTIC, 
	BLACK_RUBBER, 
	DEFAULT
} GsMaterialName;

#endif /* _NADBTYPEENUMS_H */
