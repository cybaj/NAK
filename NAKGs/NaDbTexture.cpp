// GLTexture.cpp: implementation of the NaDbTexture class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "ObjLoader.h"
#include "NaDbTexture.h"
#include "NaGeMMath.h"
//#include "TextureManager.h"
#include "NaDbApi.h"
#include "bitmap.h"
#include <atlconv.h>

// GL_EXT_texture_filter_anisotropic
#define GL_TEXTURE_MAX_ANISOTROPY_EXT     0x84FE
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF

typedef std::map<std::string, GLuint> ModelTextures;

extern ModelTextures		g_modelTextures;
extern GLuint				g_nullTexture;
extern GLuint				g_blinnPhongShader;
extern GLuint				g_normalMappingShader;
extern bool					g_enableTextures;
extern bool					g_supportsProgrammablePipeline;
extern float				g_maxAnisotrophy;
extern HGLRC				g_hRC;
extern HDC					g_hDC;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

NaDbTexture::NaDbTexture(const NaGeSurface* s, const char* filename)
{
	USES_CONVERSION;

	pSurf = s->Copy();
	glObjType = GLTEXTURE;
	glObjID = (int)glObjType + NaDbObject::GetCount();
	SMOOTH = 100;
	CSMOOTH = 100;

	itsShadeRed = 150;
	itsShadeGreen = 150;
	itsShadeBlue = 150;

	itsRed = 200;
	itsGreen = 225;
	itsBlue = 50;

	isoRed = 205;
	isoGreen = 205;
	isoBlue = 255;

	factor = 1;
	pattern = 0x5555;

	SetMaterial(BRONZE);

	pointList = new CListOfPoint3D;
	normalList = new CListOfPoint3D;
	bpointList = new CListOfPoint3D;

	m_path = filename;

	LoadModel(filename);

	ComputePoints();
	ComputeWFPoints();
	ComputeBoundLimits();
	InitDisplayList();
}

NaDbTexture::~NaDbTexture()
{
	if (pointList)
	{
		pointList->Clear();
		delete pointList;
	}
	if (normalList)
	{
		normalList->Clear();
		delete normalList;
	}
	if (bpointList)
	{
		bpointList->Clear();
		delete bpointList;
	}
	glDeleteLists(wireList, 1);
	glDeleteLists(edgeList, 1);
	glDeleteLists(shadList, 1);
	delete pSurf;
	m_model.destroy();
}

void NaDbTexture::DrawModelUsingFixedFuncPipeline()
{
	const ModelOBJ::Mesh *pMesh = 0;
	const ModelOBJ::Material *pMaterial = 0;
	const ModelOBJ::Vertex *pVertices = 0;
	ModelTextures::const_iterator iter;

	for (int i = 0; i < m_model.getNumberOfMeshes(); ++i)
	{
		pMesh = &m_model.getMesh(i);
		pMaterial = pMesh->pMaterial;
		pVertices = m_model.getVertexBuffer();

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, pMaterial->ambient);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, pMaterial->diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, pMaterial->specular);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, pMaterial->shininess * 128.0f);

		if (g_enableTextures)
		{
			iter = g_modelTextures.find(pMaterial->colorMapFilename);

			if (iter == g_modelTextures.end())
			{
				glDisable(GL_TEXTURE_2D);
			}
			else
			{
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, iter->second);
			}
		}
		else
		{
			glDisable(GL_TEXTURE_2D);
		}

		if (m_model.hasPositions())
		{
			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(3, GL_FLOAT, m_model.getVertexSize(),
				m_model.getVertexBuffer()->position);
		}

		if (m_model.hasTextureCoords())
		{
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(2, GL_FLOAT, m_model.getVertexSize(),
				m_model.getVertexBuffer()->texCoord);
		}

		if (m_model.hasNormals())
		{
			glEnableClientState(GL_NORMAL_ARRAY);
			glNormalPointer(GL_FLOAT, m_model.getVertexSize(),
				m_model.getVertexBuffer()->normal);
		}

		glDrawElements(GL_TRIANGLES, pMesh->triangleCount * 3, GL_UNSIGNED_INT,
			m_model.getIndexBuffer() + pMesh->startIndex);

		if (m_model.hasNormals())
			glDisableClientState(GL_NORMAL_ARRAY);

		if (m_model.hasTextureCoords())
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);

		if (m_model.hasPositions())
			glDisableClientState(GL_VERTEX_ARRAY);
	}
}

void NaDbTexture::DrawModelUsingProgrammablePipeline()
{
	const ModelOBJ::Mesh *pMesh = 0;
	const ModelOBJ::Material *pMaterial = 0;
	const ModelOBJ::Vertex *pVertices = 0;
	ModelTextures::const_iterator iter;
	GLuint texture = 0;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (int i = 0; i < m_model.getNumberOfMeshes(); ++i)
	{
		pMesh = &m_model.getMesh(i);
		pMaterial = pMesh->pMaterial;
		pVertices = m_model.getVertexBuffer();

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, pMaterial->ambient);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, pMaterial->diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, pMaterial->specular);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, pMaterial->shininess * 128.0f);

		if (pMaterial->bumpMapFilename.empty())
		{
			// Per fragment Blinn-Phong code path.

			glUseProgram(g_blinnPhongShader);

			// Bind the color map texture.

			texture = g_nullTexture;

			if (g_enableTextures)
			{
				iter = g_modelTextures.find(pMaterial->colorMapFilename);

				if (iter != g_modelTextures.end())
					texture = iter->second;
			}

			glActiveTexture(GL_TEXTURE0);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texture);

			// Update shader parameters.

			glUniform1i(glGetUniformLocation(g_blinnPhongShader, "colorMap"), 0);
			glUniform1f(glGetUniformLocation(g_blinnPhongShader, "materialAlpha"), pMaterial->alpha);
		}
		else
		{
			// Normal mapping code path.

			glUseProgram(g_normalMappingShader);

			// Bind the normal map texture.

			iter = g_modelTextures.find(pMaterial->bumpMapFilename);

			if (iter != g_modelTextures.end())
			{
				glActiveTexture(GL_TEXTURE1);
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, iter->second);
			}

			// Bind the color map texture.

			texture = g_nullTexture;

			if (g_enableTextures)
			{
				iter = g_modelTextures.find(pMaterial->colorMapFilename);

				if (iter != g_modelTextures.end())
					texture = iter->second;
			}

			glActiveTexture(GL_TEXTURE0);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texture);

			// Update shader parameters.

			glUniform1i(glGetUniformLocation(g_normalMappingShader, "colorMap"), 0);
			glUniform1i(glGetUniformLocation(g_normalMappingShader, "normalMap"), 1);
			glUniform1f(glGetUniformLocation(g_normalMappingShader, "materialAlpha"), pMaterial->alpha);
		}

		// Render mesh.

		if (m_model.hasPositions())
		{
			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(3, GL_FLOAT, m_model.getVertexSize(),
				m_model.getVertexBuffer()->position);
		}

		if (m_model.hasTextureCoords())
		{
			glClientActiveTexture(GL_TEXTURE0);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(2, GL_FLOAT, m_model.getVertexSize(),
				m_model.getVertexBuffer()->texCoord);
		}

		if (m_model.hasNormals())
		{
			glEnableClientState(GL_NORMAL_ARRAY);
			glNormalPointer(GL_FLOAT, m_model.getVertexSize(),
				m_model.getVertexBuffer()->normal);
		}

		if (m_model.hasTangents())
		{
			glClientActiveTexture(GL_TEXTURE1);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(4, GL_FLOAT, m_model.getVertexSize(),
				m_model.getVertexBuffer()->tangent);
		}

		glDrawElements(GL_TRIANGLES, pMesh->triangleCount * 3, GL_UNSIGNED_INT,
			m_model.getIndexBuffer() + pMesh->startIndex);

		if (m_model.hasTangents())
		{
			glClientActiveTexture(GL_TEXTURE1);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		}

		if (m_model.hasNormals())
			glDisableClientState(GL_NORMAL_ARRAY);

		if (m_model.hasTextureCoords())
		{
			glClientActiveTexture(GL_TEXTURE0);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		}

		if (m_model.hasPositions())
			glDisableClientState(GL_VERTEX_ARRAY);
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);
	glDisable(GL_BLEND);
}

GLuint NaDbTexture::LoadTexture(const char *pszFilename)
{
	GLuint id = 0;
	Bitmap bitmap;
	USES_CONVERSION;

	if (bitmap.loadPicture(A2W(pszFilename)))
	{
		// The Bitmap class loads images and orients them top-down.
		// OpenGL expects bitmap images to be oriented bottom-up.
		bitmap.flipVertical();

		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		if (g_maxAnisotrophy > 1.0f)
		{
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, g_maxAnisotrophy);
		}

		gluBuild2DMipmaps(GL_TEXTURE_2D, 4, bitmap.width, bitmap.height,
			GL_BGRA_EXT, GL_UNSIGNED_BYTE, bitmap.getPixels());
	}

	return id;
}

void NaDbTexture::LoadModel(const char *pszFilename)
{
	// Import the OBJ file and normalize to unit length.
	SetCursor(LoadCursor(0, IDC_WAIT));

	if (!m_model.import(pszFilename))
	{
		SetCursor(LoadCursor(0, IDC_ARROW));
		throw std::runtime_error("Failed to load model.");
	}

	//m_model.normalize();

	// Load any associated textures.
	// Note the path where the textures are assumed to be located.

	const ModelOBJ::Material *pMaterial = 0;
	GLuint textureId = 0;
	std::string::size_type offset = 0;
	std::string filename;

	for (int i = 0; i < m_model.getNumberOfMaterials(); ++i)
	{
		pMaterial = &m_model.getMaterial(i);

		// Look for and load any diffuse color map textures.

		if (pMaterial->colorMapFilename.empty())
			continue;

		// Try load the texture using the path in the .MTL file.
		textureId = LoadTexture(pMaterial->colorMapFilename.c_str());
		if (!textureId)
		{
			offset = pMaterial->colorMapFilename.find_last_of('\\');

			if (offset != std::string::npos)
				filename = pMaterial->colorMapFilename.substr(++offset);
			else
				filename = pMaterial->colorMapFilename;

			// Try loading the texture from the same directory as the OBJ file.
			textureId = LoadTexture((m_model.getPath() + filename).c_str());
		}

		if (textureId)
			g_modelTextures[pMaterial->colorMapFilename] = textureId;

		// Look for and load any normal map textures.

		if (pMaterial->bumpMapFilename.empty())
			continue;

		// Try load the texture using the path in the .MTL file.
		textureId = LoadTexture(pMaterial->bumpMapFilename.c_str());
		if (!textureId)
		{
			offset = pMaterial->bumpMapFilename.find_last_of('\\');

			if (offset != std::string::npos)
				filename = pMaterial->bumpMapFilename.substr(++offset);
			else
				filename = pMaterial->bumpMapFilename;

			// Try loading the texture from the same directory as the OBJ file.
			textureId = LoadTexture((m_model.getPath() + filename).c_str());
		}

		if (textureId)
			g_modelTextures[pMaterial->bumpMapFilename] = textureId;
	}
	SetCursor(LoadCursor(0, IDC_ARROW));
}

NaDbObject* NaDbTexture::Copy()
{
	AddRef();
	return (NaDbObject*)this;
}

void NaDbTexture::DefineDisplay()
{
    GLfloat bgcol[4];
    glGetFloatv(GL_COLOR_CLEAR_VALUE, bgcol);

    GLfloat  specref[] =  { 1.0f, 1.0f, 1.0f, 1.0f };
    // Enable Depth Testing
    glEnable(GL_DEPTH_TEST);

    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

    // Enable lighting
    glEnable(GL_LIGHTING);

    // Enable color tracking
    glEnable(GL_COLOR_MATERIAL);

    // Set Material properties to follow glColor values
//    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
//    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,specref);
//    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,128);

    glShadeModel(GL_SMOOTH);

//    glEnable(GL_AUTO_NORMAL);
//    glEnable(GL_NORMALIZE);
	
    if(displayMode == GLSHADED)
    {	
		glPushAttrib(GL_LIGHTING_BIT);
		ApplyMaterial();
		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonOffset(8, 8);
		DrawShaded();	
		glDisable(GL_LIGHTING);
		glDisable(GL_COLOR_MATERIAL);
		glColor3ub(25, 25, 25);
		DrawEdges();
		glDisable(GL_POLYGON_OFFSET_FILL);
		glPopAttrib();
    }	
    else if(displayMode == GLWIREFRAME)
    {
		glPushAttrib(GL_LIGHTING_BIT);
		glDisable(GL_LIGHTING);
		glDisable(GL_COLOR_MATERIAL);
		glDisable(GL_DEPTH_TEST);
		glColor3ub(itsRed, itsGreen, itsBlue);
		DrawWired();
		glPopAttrib();
    }
    else if(displayMode == GLHLREMOVED)
    {	
		glPushAttrib(GL_LIGHTING_BIT);
		glDisable(GL_LIGHTING);
		glDisable(GL_COLOR_MATERIAL);
		glEnable(GL_DEPTH_TEST);

		glColor3f(bgcol[0], bgcol[1], bgcol[2]);
		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonOffset(5, 5);
		DrawShaded();
		DrawWired();

		glDisable(GL_POLYGON_OFFSET_FILL);
		glPopAttrib();
    }
}

void NaDbTexture::Display(const GsDisplayMode& dMode)
{
    displayMode = dMode;
    DefineDisplay();
}

void NaDbTexture::Hilight(const GsDisplayMode&)
{
    glPushAttrib(GL_LIGHTING_BIT);
    glDisable(GL_LIGHTING);
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_DEPTH_TEST);
    itsRed = 0; itsGreen = 255; itsBlue = 255;
    isoRed = 0; isoGreen = 255; isoBlue = 255;
    glColor3ub(itsRed, itsGreen, itsBlue);
    DrawWired();
    glPopAttrib();
}

void NaDbTexture::SetColor(const GLubyte& red, const GLubyte& green, const GLubyte& blue)
{
    if(displayMode == GLWIREFRAME)
    {
		itsRed = red;
		itsGreen = green;
		itsBlue = blue;
    }
    else
    {
		itsShadeRed = red;
		itsShadeGreen = green;
		itsShadeBlue = blue;
    }
    DefineDisplay();
}

void NaDbTexture::GetColor(GLubyte* colVect) const
{
    colVect = new GLubyte[3];
    if(displayMode == GLWIREFRAME)
    {
		colVect[0] = itsRed;
		colVect[1] = itsGreen;
		colVect[2] = itsBlue;
    }
    else
    {
		colVect[0] = itsShadeRed;
		colVect[1] = itsShadeGreen;
		colVect[2] = itsShadeBlue;
    }
}

void NaDbTexture::SetSurface(const NaGeSurface* s)
{
    pSurf = s->Copy();
    ComputePoints();
    ComputeBoundLimits();
}

NaGeGeometry* NaDbTexture::Geometry() const
{
    NaGeSurface* surf = pSurf->Copy();
    return surf;
}

void NaDbTexture::ComputeBoundLimits()
{
    /*
       if(pSurf->IsOfType(SPHERE))
       {
       CSphere* pSph = static_cast<CSphere*> (pSurf);
       double rad = pSph->GetRadius();
       NaGePoint3D P = pSph->GetLocation().GetPosition();
       itsBox.SetLimits(-rad+P.GetX(), rad+P.GetX(), -rad+P.GetY(), rad+P.GetY(), -rad+P.GetZ(), rad+P.GetZ());
       return;
       }
       double lx=0,ly=0,lz=0,sx=0,sy=0,sz=0;
       NaGePoint3D P;
       QList<double> pxArray, pyArray, pzArray;
       pxArray.setAutoDelete(TRUE);
       pyArray.setAutoDelete(TRUE);
       pzArray.setAutoDelete(TRUE);

       CListIteratorOfListOfPoint3D myListIter(bpointList);
       for(myListIter.Init(); myListIter.More(); myListIter.Next())
       {
       P = myListIter.Current();	
       double *x = new double, *y = new double, *z = new double;
     *x = P.GetX(); *y = P.GetY(); *z = P.GetZ();
     pxArray.append(x);
     pyArray.append(y);
     pzArray.append(z);
     }
     pxArray.sort();
     pyArray.sort();
     pzArray.sort();
     sx = *pxArray.first();  lx = *pxArray.last();
     sy = *pyArray.first();  ly = *pyArray.last();
     sz = *pzArray.first();  lz = *pzArray.last();

     itsBox.SetLimits(sx,lx,sy,ly,sz,lz);
     */
}

void NaDbTexture::ComputePoints()
{
    SMOOTH *= 6;

    NaGePoint3D curP1;
    double uparts, vparts, istep, jstep;
    double fUPar, lUPar, fVPar, lVPar;

    fUPar = pSurf->FirstUParameter();
    lUPar = pSurf->LastUParameter();

    fVPar = pSurf->FirstVParameter();
    lVPar = pSurf->LastVParameter();

    uparts = vparts = SMOOTH/15;

    istep = fabs(lUPar-fUPar)/uparts;
    jstep = fabs(lVPar-fVPar)/vparts;

    if(pointList && (!pointList->IsEmpty()))
		pointList->Clear();
    if(normalList && (!normalList->IsEmpty()))
		normalList->Clear();
    if(bpointList && (!bpointList->IsEmpty()))
		bpointList->Clear();

	int nSize = m_model.getVertexSize();
	for (int k = 0; k < nSize; k++)
	{
		ModelOBJ::Vertex vec = m_model.getVertex(k);
		pointList->Append(NaGePoint3D(vec.position[0], vec.position[1], vec.position[2]));
		normalList->Append(NaGePoint3D(vec.normal[0], vec.normal[1], vec.normal[2]));
	}


}

void NaDbTexture::ComputeWFPoints()
{

}

void NaDbTexture::ComputeUIso(const double vPar)
{

}

void NaDbTexture::ComputeVIso(const double uPar)
{

}

void NaDbTexture::DrawUIso()
{

}

void NaDbTexture::DrawVIso()
{

}

void NaDbTexture::DrawWired()
{

}

void NaDbTexture::DrawShaded()
{
	if (g_supportsProgrammablePipeline)
		DrawModelUsingProgrammablePipeline();
	else
		DrawModelUsingFixedFuncPipeline();
}

void NaDbTexture::DrawEdges()
{

}

void NaDbTexture::InitDisplayList()
{
    //wire list
    wireList = glGenLists(1);
    glNewList(wireList, GL_COMPILE);
    DrawWired();
    glEndList();

    //edges list
    edgeList = glGenLists(1);
    glNewList(edgeList, GL_COMPILE);
    DrawEdges();
    glEndList();

    //shaded list
    shadList = glGenLists(1);
    glNewList(shadList, GL_COMPILE);
    DrawShaded();
    glEndList();
}
