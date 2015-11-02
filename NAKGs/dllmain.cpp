// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "NaDbApi.h"
#include <cassert>
#include <cmath>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

//-----------------------------------------------------------------------------
// Type definitions.
//-----------------------------------------------------------------------------
#define GL_TEXTURE_MAX_ANISOTROPY_EXT     0x84FE
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF

typedef std::map<std::string, GLuint> ModelTextures;
ModelTextures		g_modelTextures;
GLuint              g_nullTexture;
GLuint              g_blinnPhongShader;
GLuint              g_normalMappingShader;
bool				g_enableTextures = true;
bool				g_supportsProgrammablePipeline = true;
float				g_maxAnisotrophy;
HGLRC				g_hRC;
HDC					g_hDC;

GLuint CompileShader(GLenum type, const GLchar *pszSource, GLint length)
{
	// Compiles the shader given it's source code. Returns the shader object.
	// A std::string object containing the shader's info log is thrown if the
	// shader failed to compile.
	//
	// 'type' is either GL_VERTEX_SHADER or GL_FRAGMENT_SHADER.
	// 'pszSource' is a C style string containing the shader's source code.
	// 'length' is the length of 'pszSource'.

	GLuint shader = glCreateShader(type);

	if (shader)
	{
		GLint compiled = 0;

		glShaderSource(shader, 1, &pszSource, &length);
		glCompileShader(shader);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

		if (!compiled)
		{
			GLsizei infoLogSize = 0;
			std::string infoLog;

			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogSize);
			infoLog.resize(infoLogSize);
			glGetShaderInfoLog(shader, infoLogSize, &infoLogSize, &infoLog[0]);

			throw infoLog;
		}
	}

	return shader;
}

GLuint LinkShaders(GLuint vertShader, GLuint fragShader)
{
	// Links the compiled vertex and/or fragment shaders into an executable
	// shader program. Returns the executable shader object. If the shaders
	// failed to link into an executable shader program, then a std::string
	// object is thrown containing the info log.

	GLuint program = glCreateProgram();

	if (program)
	{
		GLint linked = 0;

		if (vertShader)
			glAttachShader(program, vertShader);

		if (fragShader)
			glAttachShader(program, fragShader);

		glLinkProgram(program);
		glGetProgramiv(program, GL_LINK_STATUS, &linked);

		if (!linked)
		{
			GLsizei infoLogSize = 0;
			std::string infoLog;

			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogSize);
			infoLog.resize(infoLogSize);
			glGetProgramInfoLog(program, infoLogSize, &infoLogSize, &infoLog[0]);

			throw infoLog;
		}

		// Mark the two attached shaders for deletion. These two shaders aren't
		// deleted right now because both are already attached to a shader
		// program. When the shader program is deleted these two shaders will
		// be automatically detached and deleted.

		if (vertShader)
			glDeleteShader(vertShader);

		if (fragShader)
			glDeleteShader(fragShader);
	}

	return program;
}

GLuint CreateNullTexture(int width, int height)
{
	// Create an empty white texture. This texture is applied to OBJ models
	// that don't have any texture maps. This trick allows the same shader to
	// be used to draw the OBJ model with and without textures applied.

	int pitch = ((width * 32 + 31) & ~31) >> 3; // align to 4-byte boundaries
	std::vector<GLubyte> pixels(pitch * height, 255);
	GLuint texture = 0;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_BGRA,
		GL_UNSIGNED_BYTE, &pixels[0]);

	return texture;
}

GLuint LoadShaderProgramFromResource(const char *filename, std::string &infoLog)
{
	infoLog.clear();

	GLuint program = 0;
	std::string buffer;

	FILE* pFile = fopen(filename, "rt");
	if (!pFile)
		return 0;

	fseek(pFile, 0, SEEK_END);
	DWORD dwSize = ftell(pFile);
	char* pBuf = new char[dwSize + 1];
	fseek(pFile, 0, SEEK_SET);
	fread(pBuf, sizeof(char), sizeof(char)*dwSize, pFile);
	pBuf[dwSize] = '\0';
	buffer = pBuf;
	fclose(pFile);
	delete pBuf;

	// Compile and link the vertex and fragment shaders.
	if (buffer.length() > 0)
	{
		const GLchar *pSource = 0;
		GLint length = 0;
		GLuint vertShader = 0;
		GLuint fragShader = 0;

		std::string::size_type vertOffset = buffer.find("[vert]");
		std::string::size_type fragOffset = buffer.find("[frag]");

		try
		{
			// Get the vertex shader source and compile it.
			// The source is between the [vert] and [frag] tags.
			if (vertOffset != std::string::npos)
			{
				vertOffset += 6;        // skip over the [vert] tag
				pSource = reinterpret_cast<const GLchar *>(&buffer[vertOffset]);
				length = static_cast<GLint>(fragOffset - vertOffset);
				vertShader = CompileShader(GL_VERTEX_SHADER, pSource, length);
			}

			// Get the fragment shader source and compile it.
			// The source is between the [frag] tag and the end of the file.
			if (fragOffset != std::string::npos)
			{
				fragOffset += 6;        // skip over the [frag] tag
				pSource = reinterpret_cast<const GLchar *>(&buffer[fragOffset]);
				length = static_cast<GLint>(buffer.length() - fragOffset - 1);
				fragShader = CompileShader(GL_FRAGMENT_SHADER, pSource, length);
			}

			// Now link the vertex and fragment shaders into a shader program.
			program = LinkShaders(vertShader, fragShader);
		}
		catch (const std::string &errors)
		{
			infoLog = errors;
		}
	}

	return program;
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}


bool ExtensionSupported(HDC hDC, const char *pszExtensionName)
{
	static const char *pszGLExtensions = 0;
	static const char *pszWGLExtensions = 0;

	if (!pszGLExtensions)
		pszGLExtensions = reinterpret_cast<const char *>(glGetString(GL_EXTENSIONS));

	if (!pszWGLExtensions)
	{
		// WGL_ARB_extensions_string.

		typedef const char *(WINAPI * PFNWGLGETEXTENSIONSSTRINGARBPROC)(HDC);

		PFNWGLGETEXTENSIONSSTRINGARBPROC wglGetExtensionsStringARB =
			reinterpret_cast<PFNWGLGETEXTENSIONSSTRINGARBPROC>(
				wglGetProcAddress("wglGetExtensionsStringARB"));

		if (wglGetExtensionsStringARB)
			pszWGLExtensions = wglGetExtensionsStringARB(hDC);
	}

	if (!strstr(pszGLExtensions, pszExtensionName))
	{
		if (!strstr(pszWGLExtensions, pszExtensionName))
			return false;
	}

	return true;
}

void InitGsModule(HDC hDC, HGLRC hRC)
{
	char lpFilename[_MAX_PATH], drive[_MAX_DRIVE], path[_MAX_PATH];
	HMODULE hMain = ::GetModuleHandleA("");
	::GetModuleFileNameA(hMain, lpFilename, _MAX_PATH);
	_splitpath(lpFilename, drive, path, NULL, NULL);

	g_hDC = hDC;
	g_hRC = hRC;

	GL2Init();

	g_supportsProgrammablePipeline = GL2SupportsGLVersion(2, 0);

	// Check for GL_EXT_texture_filter_anisotropic support.
	if (ExtensionSupported(hDC, "GL_EXT_texture_filter_anisotropic"))
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &g_maxAnisotrophy);
	else
		g_maxAnisotrophy = 1.0f;

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glActiveTexture(GL_TEXTURE1);
	glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	if (g_supportsProgrammablePipeline)
	{
		std::string infoLog;
		char blinn[_MAX_PATH], mapping[_MAX_PATH];

		sprintf(blinn, "%s%s\\Shaders\\blinn_phong.glsl", drive, path);
		sprintf(mapping, "%s%s\\Shaders\\normal_mapping.glsl", drive, path);

		if (!(g_blinnPhongShader = LoadShaderProgramFromResource(blinn, infoLog)))
			throw std::runtime_error("Failed to load Blinn-Phong shader.\n" + infoLog);

		if (!(g_normalMappingShader = LoadShaderProgramFromResource(mapping, infoLog)))
			throw std::runtime_error("Failed to load normal mapping shader.\n" + infoLog);
		
		if (!(g_nullTexture = CreateNullTexture(2, 2)))
			throw std::runtime_error("Failed to create null texture.");

	}
}

void ExitGsModule()
{
	ModelTextures::iterator i = g_modelTextures.begin();
	while (i != g_modelTextures.end())
	{
		glDeleteTextures(1, &i->second);
		++i;
	}
	g_modelTextures.clear();

	if (g_nullTexture)
	{
		glDeleteTextures(1, &g_nullTexture);
		g_nullTexture = 0;
	}

}