#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN             // Excluir material rara vez utilizado de encabezados de Windows
// Archivos de encabezado de Windows:
#include <windows.h>

// Archivos de encabezado en tiempo de ejecución de C
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <GL/glew.h>
#include "CGShaderProgram.h"
#include "resource.h"

CGShaderProgram::CGShaderProgram()
{
	GLint status;
	logInfo = NULL;

	// Crea y compila el vertex shader
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, GetVertexShaderFromResource(), NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		linked = GL_FALSE;
		GLint logLength;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &logLength);
		logInfo = (char*)malloc(sizeof(char) * logLength);
		GLsizei written;
		glGetShaderInfoLog(vertexShader, logLength, &written, logInfo);
		return;
	}

	// Crea y compila el fragment shader
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, GetFragmentShaderFromResource(), NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		linked = GL_FALSE;
		GLint logLength;
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &logLength);
		logInfo = (char*)malloc(sizeof(char) * logLength);
		GLsizei written;
		glGetShaderInfoLog(fragmentShader, logLength, &written, logInfo);
		return;
	}

	//Crea y enlaza el programa
	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		linked = GL_FALSE;
		GLint logLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
		logInfo = (char*)malloc(sizeof(char) * logLength);
		GLsizei written;
		glGetProgramInfoLog(program, logLength, &written, logInfo);
		return;
	}

	linked = GL_TRUE;
}

char** CGShaderProgram::GetVertexShaderFromResource()
{
	HRSRC shaderHandle = FindResource(NULL, MAKEINTRESOURCE(IDR_HTML1), RT_HTML);
	HGLOBAL shaderGlobal = LoadResource(NULL, shaderHandle);
	LPCTSTR shaderPtr = static_cast<LPCTSTR>(LockResource(shaderGlobal));
	DWORD shaderSize = SizeofResource(NULL, shaderHandle);
	char* shaderCodeLine = (char*)malloc((shaderSize + 1) * sizeof(char));
	memcpy(shaderCodeLine, shaderPtr, shaderSize);
	shaderCodeLine[shaderSize] = '\0';
	char** shaderCode = (char**)malloc(sizeof(char*));
	shaderCode[0] = shaderCodeLine;
	UnlockResource(shaderGlobal);
	FreeResource(shaderGlobal);
	return shaderCode;
}

char** CGShaderProgram::GetFragmentShaderFromResource()
{
	HRSRC shaderHandle = FindResource(NULL, MAKEINTRESOURCE(IDR_HTML2), RT_HTML);
	HGLOBAL shaderGlobal = LoadResource(NULL, shaderHandle);
	LPCTSTR shaderPtr = static_cast<LPCTSTR>(LockResource(shaderGlobal));
	DWORD shaderSize = SizeofResource(NULL, shaderHandle);
	char* shaderCodeLine = (char*)malloc((shaderSize + 1) * sizeof(char));
	memcpy(shaderCodeLine, shaderPtr, shaderSize);
	shaderCodeLine[shaderSize] = '\0';
	char** shaderCode = (char**)malloc(sizeof(char*));
	shaderCode[0] = shaderCodeLine;
	UnlockResource(shaderGlobal);
	FreeResource(shaderGlobal);
	return shaderCode;
}

CGShaderProgram::~CGShaderProgram()
{
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteProgram(program);
}

GLboolean CGShaderProgram::IsLinked()
{
	return linked;
}

char* CGShaderProgram::GetLog()
{
	return logInfo;
}

GLvoid CGShaderProgram::Use()
{
	glUseProgram(program);
}


void CGShaderProgram::SetUniformF(const char* name, GLfloat f)
{
	GLuint location = glGetUniformLocation(program, name);
	if (location >= 0) glUniform1f(location, f);
}

GLvoid CGShaderProgram::SetUniformMatrix4(const char* name, glm::mat4 m)
{
	GLuint location = glGetUniformLocation(program, name);
	if (location >= 0) glUniformMatrix4fv(location, 1, GL_FALSE, &m[0][0]);
}

void CGShaderProgram::SetUniformVec4(const char* name, glm::vec4 v)
{
	GLuint location = glGetUniformLocation(program, name);
	if (location >= 0) glUniform4fv(location, 1, &v[0]);
}

void CGShaderProgram::SetUniformVec3(const char* name, glm::vec3 v)
{
	GLuint location = glGetUniformLocation(program, name);
	if (location >= 0) glUniform3fv(location, 1, &v[0]);
}

void CGShaderProgram::SetUniformI(const char* name, GLint i)
{
	GLuint location = glGetUniformLocation(program, name);
	if (location >= 0) glUniform1i(location, i);
}

//
// FUNCIÓN: CGShaderProgram::SetVertexShaderUniformSubroutine(const char * name)
//
// PROPÓSITO: Asigna una subrutina en el VertexShader
//
GLvoid CGShaderProgram::SetVertexShaderUniformSubroutine(const char* name)
{
	GLuint location = glGetSubroutineIndex(program, GL_VERTEX_SHADER, name);
	if (location >= 0) glUniformSubroutinesuiv(GL_VERTEX_SHADER, 1, &location);
}

//
// FUNCIÓN: CGShaderProgram::SetFragmentShaderUniformSubroutine(const char * name)
//
// PROPÓSITO: Asigna una subrutina en el FragmentShader
//
GLvoid CGShaderProgram::SetFragmentShaderUniformSubroutine(const char* name)
{
	GLuint location = glGetSubroutineIndex(program, GL_FRAGMENT_SHADER, name);
	if (location >= 0) glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &location);
}