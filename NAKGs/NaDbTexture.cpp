// GLTexture.cpp: implementation of the NaDbTexture class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NaDbTexture.h"
#include "NaGeMMath.h"

#include "NaDbApi.h"
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

NaDbTexture::NaDbTexture(const NaGeSurface* s, const char* filename, double dBrightness, double dContrast, double dGamma, BOOL bInvert)
{
	USES_CONVERSION;

	pSurf = s->Copy();
	glObjType = GLTEXTURE;
	glObjID = (int)glObjType + NaDbObject::GetCount();
	SMOOTH = 100;
	CSMOOTH = 100;

	//!특수 효과
	itsShadeRed = 0;
	itsShadeGreen = 0;
	itsShadeBlue = 0;

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

	AdjustColors(dBrightness, dContrast, dGamma, FALSE);

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

//picking or selecting a triangle of a mesh
// glReadPixels((int)winX, (int)winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &zCursor); 
void NaDbTexture::GetRGBfromVertex(NaGePoint3D& pt, DWORD& rgba)
{
	BOOL bIsFind = FALSE;
	const ModelOBJ::Mesh *pMesh = 0;
	const ModelOBJ::Material *pMaterial = 0;
	const ModelOBJ::Vertex *pVertices = 0;

	pVertices = m_model.getVertexBuffer();
	const int* pindex = m_model.getIndexBuffer();
	int indexSize = m_model.getIndexSize();

	double func[4], eps = 0.1;
	ModelOBJ::Vertex v1, v2, v3;
	NaGePoint3D p1, p2, p3;
	for (int i = 0; i < m_model.getNumberOfMeshes(); ++i)
	{
		pMesh = &m_model.getMesh(i);
		pMaterial = pMesh->pMaterial;
		int sindex = pMesh->startIndex;
		int tindex = pMesh->triangleCount;

		for (int j = 0; j < tindex; j++)
		{
			v1 = pVertices[pindex[sindex + j * 3 + 0]];
			v2 = pVertices[pindex[sindex + j * 3 + 1]];
			v3 = pVertices[pindex[sindex + j * 3 + 2]];

			//세점을 지나는 평면상에 점이 선택되었는지 확인함
			p1.SetParam(v1.position[0], v1.position[1], v1.position[2]);
			p2.SetParam(v2.position[0], v2.position[1], v2.position[2]);
			p3.SetParam(v3.position[0], v3.position[1], v3.position[2]);
			NaGePlane plane(p1, p2, p3);
			plane.EquationAt(pt, func);
			if (fabs(func[0]+ func[1]+ func[2]+ func[3]) < eps)
			{
				bpointList->Clear();
				normalList->Clear();

				bpointList->Append(NaGePoint3D(v1.position[0], v1.position[1], v1.position[2]));
				bpointList->Append(NaGePoint3D(v2.position[0], v2.position[1], v2.position[2]));
				bpointList->Append(NaGePoint3D(v3.position[0], v3.position[1], v3.position[2]));

				normalList->Append(NaGePoint3D(v1.normal[0], v1.normal[1], v1.normal[2]));
				normalList->Append(NaGePoint3D(v2.normal[0], v2.normal[1], v2.normal[2]));
				normalList->Append(NaGePoint3D(v3.normal[0], v3.normal[1], v3.normal[2]));
				break;
			}
		}
	}

	if (bIsFind)
	{
		float normal[3];
		float texCoord[2];

		memcpy(normal, v1.normal, sizeof(float[3]));
		memcpy(texCoord, v1.texCoord, sizeof(float[2]));
		
		//GLuint texture = g_modelTextures[uvmapFile];
	}
}

void NaDbTexture::DrawModelUsingFixedFuncPipeline()
{
	const ModelOBJ::Mesh *pMesh = 0;
	const ModelOBJ::Material *pMaterial = 0;
	const ModelOBJ::Vertex *pVertices = 0;
	ModelTextures::const_iterator iter;

	NaDbMaterial mat;
	for (int i = 0; i < m_model.getNumberOfMeshes(); ++i)
	{
		pMesh = &m_model.getMesh(i);

		pMaterial = pMesh->pMaterial;
		mat.SetAmbient(NaDbColor(pMaterial->ambient[0], pMaterial->ambient[1], pMaterial->ambient[2]));
		mat.SetDiffuse(NaDbColor(pMaterial->diffuse[0], pMaterial->diffuse[1], pMaterial->diffuse[2]));
		mat.SetSpecular(NaDbColor(pMaterial->specular[0], pMaterial->specular[1], pMaterial->specular[2]));
		mat.SetShininessCoeff(pMaterial->shininess);
		SetMaterial(mat);

		pVertices = m_model.getVertexBuffer();

		//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, pMaterial->ambient);
		//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, pMaterial->diffuse);
		//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, pMaterial->specular);
		//glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, pMaterial->shininess * 128.0f);

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

			// 칼라 맵 바이드.
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

			// 쉐이더 파라메터 업데이트
			glUniform1i(glGetUniformLocation(g_blinnPhongShader, "colorMap"), 0);
			glUniform1f(glGetUniformLocation(g_blinnPhongShader, "materialAlpha"), pMaterial->alpha);
		}
		else
		{
			// 노말매핑 
			glUseProgram(g_normalMappingShader);

			// 노말매핑 바인드
			iter = g_modelTextures.find(pMaterial->bumpMapFilename);
			if (iter != g_modelTextures.end())
			{
				glActiveTexture(GL_TEXTURE1);
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, iter->second);		
			}

			// 컬러맵 바인드
			texture = g_nullTexture;

			if (g_enableTextures)
			{
				iter = g_modelTextures.find(pMaterial->colorMapFilename);
				if (iter != g_modelTextures.end())
				{
					texture = iter->second;


					/*
					FIMEMORY* fmemory = FreeImage_OpenMemory((BYTE*)pixels);
					free(pixels);
					FIBITMAP* fdb = FreeImage_LoadFromMemory(FIF_UNKNOWN, fmemory);
					if (fdb)
					{
						FREE_IMAGE_COLOR_CHANNEL channel = FICC_RED;
						fdb = FreeImage_GetChannel(fdb, channel);
						char* pixeles = (char*)FreeImage_GetBits(fdb);
						//GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels
						GLsizei width = FreeImage_GetWidth(fdb);
						GLsizei height = FreeImage_GetHeight(fdb);
						GLint border = 0;
						glTexImage2D(GL_TEXTURE_2D, 0, 0, width, height, border, GL_RGB, GL_UNSIGNED_BYTE, (GLvoid*)pixeles);
						FreeImage_Unload(fdb);
					}
					*/

				}
			}

			glActiveTexture(GL_TEXTURE0);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texture);
			/*
			//=============================================================================
			//이미지 처리
			//GLenum target, GLint level, GLenum format, GLenum type, GLvoid *pixels
			GLint textureWidth, textureHeight;
			glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &textureWidth);
			glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &textureHeight);

			GLubyte *pixels = (GLubyte *)malloc(textureWidth*textureHeight * 4);
			if (pixels)
			{
				glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_BYTE, pixels);
				for (int y = 0; y < textureHeight; y++)
					for (int x = 0; x < textureWidth; x++)
					{
						int startAddressOfPixel = ((y*textureWidth) + x) * 4;
						pixels[startAddressOfPixel + 0] = 120;
						pixels[startAddressOfPixel + 1] = 120;
						pixels[startAddressOfPixel + 2] = 120;
						//pixels[startAddressOfPixel + 3] = 0;
						//printf("pixel at %d %d has colour r=%d g=%d b=%d a=%d\n", x, y, buffer[startAddressOfPixel], buffer[startAddressOfPixel + 1], buffer[startAddressOfPixel + 2], startAddressOfPixel[startAddressOfPixel + 3]);
					}
			//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_BYTE, pixels);
				free(pixels);
			}
			//=============================================================================
			*/


			// 쉐이더 파라메터 업데이트
			glUniform1i(glGetUniformLocation(g_normalMappingShader, "colorMap"), 0);
			glUniform1i(glGetUniformLocation(g_normalMappingShader, "normalMap"), 1);
			glUniform1f(glGetUniformLocation(g_normalMappingShader, "materialAlpha"), pMaterial->alpha);
		}


		// Render mesh.
		if (m_model.hasPositions())
		{
			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(3, GL_FLOAT, m_model.getVertexSize(),m_model.getVertexBuffer()->position);
		}

		if (m_model.hasTextureCoords())
		{
			glClientActiveTexture(GL_TEXTURE0);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(2, GL_FLOAT, m_model.getVertexSize(),m_model.getVertexBuffer()->texCoord);
		}

		if (m_model.hasNormals())
		{
			glEnableClientState(GL_NORMAL_ARRAY);
			glNormalPointer(GL_FLOAT, m_model.getVertexSize(),m_model.getVertexBuffer()->normal);
		}

		if (m_model.hasTangents())
		{
			glClientActiveTexture(GL_TEXTURE1);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(4, GL_FLOAT, m_model.getVertexSize(),	m_model.getVertexBuffer()->tangent);
		}

		glDrawElements(GL_TRIANGLES, pMesh->triangleCount * 3, GL_UNSIGNED_INT,	m_model.getIndexBuffer() + pMesh->startIndex);

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
	FREE_IMAGE_FORMAT formato = FreeImage_GetFileType(pszFilename, 0);
	FIBITMAP* imagen = FreeImage_Load(formato, pszFilename);
	if (imagen)
	{
		FIBITMAP* temp = imagen;
		imagen = FreeImage_ConvertTo32Bits(imagen);
		if (m_dGamma>0.0)
			//FreeImage_AdjustGamma(imagen, m_dGamma);
			FreeImage_AdjustColors(imagen, m_dBrightness, m_dContrast, m_dGamma, m_bInvert);

		FreeImage_Unload(temp);

		int w = FreeImage_GetWidth(imagen);
		int h = FreeImage_GetHeight(imagen);
		//GLubyte* textura = new GLubyte[4 * w*h];
		char* pixeles = (char*)FreeImage_GetBits(imagen);

		/*
		//FreeImage loads in BGR format, so you need to swap some bytes(Or use GL_BGR).
		for (int j = 0; j < w*h; j++)
		{
			textura[j * 4 + 0] = pixeles[j * 4 + 2];
			textura[j * 4 + 1] = pixeles[j * 4 + 1];
			textura[j * 4 + 2] = pixeles[j * 4 + 0];
			textura[j * 4 + 3] = pixeles[j * 4 + 3];
		}*/

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

		gluBuild2DMipmaps(GL_TEXTURE_2D, 4, w, h, GL_BGRA_EXT, GL_UNSIGNED_BYTE, (GLvoid*)pixeles);

		FreeImage_Unload(imagen);
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

			// Obj 파일과 동일한 경로에서 UV 이미지 파일을 로드시킨다.
			m_textureName = m_model.getPath() + filename;
			textureId = LoadTexture(m_textureName.c_str());
		}

		if (textureId)
		{
			g_modelTextures[pMaterial->colorMapFilename] = textureId;
		}

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
			m_bumpName = m_model.getPath() + filename;
			textureId = LoadTexture(m_bumpName.c_str());
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

bool NaDbTexture::SaveObject(FILE* fptr)
{
	//todo:
	const ModelOBJ::Mesh *pMesh = 0;
	const ModelOBJ::Material *pMaterial = 0;
	const ModelOBJ::Vertex *pVertices = 0;
	ModelTextures::const_iterator iter;
	GLuint texture = 0;

	Json::StyledWriter writer;
	Json::Value* pvalue = NULL;

	pVertices = m_model.getVertexBuffer();
	const int* pindex = m_model.getIndexBuffer();
	int indexSize = m_model.getIndexSize();

	Json::Value jMesh;

	char triangleName[60];

	for (int i = 0; i < m_model.getNumberOfMeshes(); ++i)
	{
		pMesh = &m_model.getMesh(i);
		pMaterial = pMesh->pMaterial;
		int sindex = pMesh->startIndex;
		int tindex = pMesh->triangleCount;

		if (pMaterial->bumpMapFilename.empty())
		{
			// 칼라 맵 바이드.
			texture = g_nullTexture;
			if (g_enableTextures)
			{
				iter = g_modelTextures.find(pMaterial->colorMapFilename);

				if (iter != g_modelTextures.end())
					texture = iter->second;
			}
		}
		else
		{
			// 노말매핑 
			glUseProgram(g_normalMappingShader);
			// 노말매핑 바인드
			iter = g_modelTextures.find(pMaterial->bumpMapFilename);
			if (iter != g_modelTextures.end())
			{
				texture = iter->second;
			}
			// 컬러맵 바인드
			texture = g_nullTexture;
			if (g_enableTextures)
			{
				iter = g_modelTextures.find(pMaterial->colorMapFilename);
				if (iter != g_modelTextures.end())
				{
					texture = iter->second;
				}
			}
		}

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture);

		//opengl의 메모리에서 rgb값을 얻어온다.
		GLint textureWidth, textureHeight, internalFormat;
		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_COMPONENTS, &internalFormat); // get internal format type of GL texture
		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &textureWidth);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &textureHeight);
		GLubyte *pixels = (GLubyte *)malloc(textureWidth*textureHeight * 4);
		glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_BYTE, pixels);
		if (pixels == NULL)
			continue;

		for (int j = 0; j < tindex; j++)
		{
			ModelOBJ::Vertex v1 = pVertices[pindex[sindex + j * 3 + 0]];
			ModelOBJ::Vertex v2 = pVertices[pindex[sindex + j * 3 + 1]];
			ModelOBJ::Vertex v3 = pVertices[pindex[sindex + j * 3 + 2]];
			//삼각형의 무게중심
			double gravity[3];
			gravity[0] = (v1.position[0] + v2.position[0] + v3.position[0]) / 3.0;
			gravity[1] = (v1.position[1] + v2.position[1] + v3.position[1]) / 3.0;
			gravity[2] = (v1.position[2] + v2.position[2] + v3.position[2]) / 3.0;
			//무게중심의 UV
			double dU = (v1.texCoord[0] + v2.texCoord[0] + v3.texCoord[0]) / 3.0;
			double dV = (v1.texCoord[1] + v2.texCoord[1] + v3.texCoord[1]) / 3.0;

			//face
			Json::Value jface;
			jface["FacetCount"] = 1;			
			jface["VertexCount"] = 3;
			//VertexCoords
			Json::Value jvt;
			jvt.append(v1.position[0]);
			jvt.append(v1.position[1]);
			jvt.append(v1.position[2]);
			jvt.append(v2.position[0]);
			jvt.append(v2.position[1]);
			jvt.append(v2.position[2]);
			jvt.append(v3.position[0]);
			jvt.append(v3.position[1]);
			jvt.append(v3.position[2]);
			//Normals
			Json::Value jnr;
			jnr.append(v1.normal[0]);
			jnr.append(v1.normal[1]);
			jnr.append(v1.normal[2]);
			jnr.append(v2.normal[0]);
			jnr.append(v2.normal[1]);
			jnr.append(v2.normal[2]);
			jnr.append(v3.normal[0]);
			jnr.append(v3.normal[1]);
			jnr.append(v3.normal[2]);
			//VertexIndices
			Json::Value jvi;
			jvi.append(0);
			jvi.append(1);
			jvi.append(2);
			//NormaIndices
			Json::Value jni;
			jni.append(0);
			jni.append(1);
			jni.append(2);
			//Center
			Json::Value jgravity;
			jgravity.append(gravity[0]);
			jgravity.append(gravity[1]);
			jgravity.append(gravity[2]);
			//rgb 값을 검색
			int x = (int)(dU * textureWidth);
			int y = (int)(dV * textureHeight);
			int startAddressOfPixel = ((y*textureWidth) + x) * 4;
			int red = pixels[startAddressOfPixel + 0];
			int green = pixels[startAddressOfPixel + 1];
			int blue = pixels[startAddressOfPixel + 2];
			int alpha = pixels[startAddressOfPixel + 3];

			//LONG rgba = MAKELONG(MAKEWORD(red, green), MAKEWORD(blue, alpha));
			LONG rgba = MAKELONG(MAKEWORD(alpha, blue), MAKEWORD(green, red));
			
			//rgb
			Json::Value jrgb;
			jrgb.append(rgba);
			jrgb.append(green);
			jrgb.append(blue);
			jrgb.append(alpha);

			jface["VertexCoords"] = jvt;
			jface["VertexIndices"] = jvi;
			jface["Normals"] = jnr;
			jface["NormalIndices"] = jni;
			jface["Center"] = jgravity;
			jface["Color"] = jrgb;
			sprintf(triangleName, "face%06d", j);
			jface["Id"] = triangleName;
			jMesh.append(jface);
		}

		//free
		if(pixels) free(pixels);

	}
	std::string strJson = writer.write(jMesh);
	size_t fsize = fwrite(strJson.c_str(), 1, strJson.length(), fptr);
	return fsize?true:false;
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
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,specref);
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,128);

    glShadeModel(GL_SMOOTH);

    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);
	
    if(displayMode == GLSHADED)
    {	
		glPushAttrib(GL_LIGHTING_BIT);
//		ApplyMaterial();
		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonOffset(8, 8);
		DrawShaded();	
		glDisable(GL_LIGHTING);
		glDisable(GL_COLOR_MATERIAL);
		glColor3ub(125, 125, 125);
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

	float x, y, z;
	m_model.getCenter(x, y, z);
	pointList->Append(NaGePoint3D(x,y,z));

	//int nSize = m_model.getVertexSize();
//	int nSize = m_model.getNumberOfVertices();
//	for (int k = 0; k < nSize; k++)
//	{
//		ModelOBJ::Vertex vec = m_model.getVertex(k);
//		pointList->Append(NaGePoint3D(vec.position[0], vec.position[1], vec.position[2]));
//		normalList->Append(NaGePoint3D(vec.normal[0], vec.normal[1], vec.normal[2]));
//	}
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
	const ModelOBJ::Mesh *pMesh = 0;
	const ModelOBJ::Material *pMaterial = 0;
	const ModelOBJ::Vertex *pVertices = 0;

	glLineWidth(1.5);

	pVertices = m_model.getVertexBuffer();
	const int* pindex = m_model.getIndexBuffer();
	int indexSize = m_model.getIndexSize();

	for (int i = 0; i < m_model.getNumberOfMeshes(); ++i)
	{
		pMesh = &m_model.getMesh(i);
		pMaterial = pMesh->pMaterial;
		int sindex = pMesh->startIndex;
		int tindex = pMesh->triangleCount;
		for (int j = 0; j < tindex; j++)
		{
			glBegin(GL_LINE_STRIP);
			ModelOBJ::Vertex v1 = pVertices[pindex[sindex + j * 3 + 0]];
			glNormal3d(v1.normal[0], v1.normal[1], v1.normal[2]);
			glVertex3d(v1.position[0], v1.position[1], v1.position[2]);
			ModelOBJ::Vertex v2 = pVertices[pindex[sindex + j * 3 + 1]];
			glNormal3d(v2.normal[0], v2.normal[1], v2.normal[2]);
			glVertex3d(v2.position[0], v2.position[1], v2.position[2]);
			ModelOBJ::Vertex v3 = pVertices[pindex[sindex + j * 3 + 2]];
			glNormal3d(v3.normal[0], v3.normal[1], v3.normal[2]);
			glVertex3d(v3.position[0], v3.position[1], v3.position[2]);
			glEnd();
		}
	}
	glLineWidth(1.0);
}

void NaDbTexture::DrawShaded()
{
	if (g_supportsProgrammablePipeline)
		DrawModelUsingProgrammablePipeline();
	else
		DrawModelUsingFixedFuncPipeline();
}

// 선택된 triangle 을 그린다.
void NaDbTexture::DrawEdges()
{
	/*
	NaGePoint3D curPt,curNr;
	CListIteratorOfListOfPoint3D myListIterP(bpointList);
	CListIteratorOfListOfPoint3D myListIterN(normalList);
	myListIterP.Init();
	myListIterN.Init();

	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor4b(255, 0, 0, 0.5);
	glLineWidth(4.0);
	glBegin(GL_LINE_STRIP);

	for (myListIterP.Init(); myListIterP.More();)
	{
		curPt = myListIterP.Current();
		curNr = myListIterN.Current();
		glNormal3d(curNr.GetX(), curNr.GetY(), curNr.GetZ());
		glVertex3d(curPt.GetX(), curPt.GetY(), curPt.GetZ());
		
		myListIterP.Next();
		myListIterN.Next();
	}
	glEnd();
	glLineWidth(1.0);
	*/
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