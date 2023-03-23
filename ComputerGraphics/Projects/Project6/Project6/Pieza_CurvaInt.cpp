//#include "stdafx.h"
#include "Pieza_CurvaInt.h"
#include <GL/glew.h>
#define _USE_MATH_DEFINES
#include <math.h>

Pieza_CurvaInt::Pieza_CurvaInt(CGMaterial* mtl, GLfloat p, GLfloat m, GLfloat r0, GLfloat r1, GLfloat &vx1, GLfloat &vx2, GLfloat &vz1, GLfloat &vz2)
{
	numFaces = 13;     // Number of faces
	numVertices = 13;  // Number of vertices

	GLfloat p_normals[4][3] = 
	{
	{ 0.0f, 1.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f }
	};

	GLfloat p_textures[12][2] = 
	{
	{ 1.0f, 0.0f },
	{ 0.0f, 0.0f },
	{ 0.0f, 0.2f },
	{ 1.0f, 0.2f },
	{0.0f,0.4f},
	{1.0f,0.4f},
	{0.0f,0.6f},
	{1.0f,0.6f},
	{0.0f,0.8f},
	{1.0f,0.8f },
	{0.0f,1.0f},
	{1.0f,1.0f}
	};
	GLfloat x = r1*sin(M_PI / 20);
	GLfloat z = r1*(1 - cos(M_PI / 20));

	GLfloat p_vertices[12][3] = 
	{
	{ 0, 1.0f, 15.6/2 },
	{ 0, 1.0f, -15.6/2 },
	{ 0+x, 1.0f, (-15.6/2)+ z },
	};

	x = r0*sin(M_PI / 20);
	z = r0*(1 - cos(M_PI / 20));
	p_vertices[3][0] = { p_vertices[0][0]+x };
	p_vertices[3][1] = { 1 };
	p_vertices[3][2] = { p_vertices[0][2] +z };

	x = r1*sin(M_PI / 10);
	z = r1*(1 - cos(M_PI / 10));

	p_vertices[4][0] = { p_vertices[1][0] + x };
	p_vertices[4][1] = { 1 };
	p_vertices[4][2] = { p_vertices[1][2] + z };
	x = r0*sin(M_PI / 10);
	z = r0*(1 - cos(M_PI / 10));

	p_vertices[5][0] = { p_vertices[0][0] + x };
	p_vertices[5][1] = { 1 };
	p_vertices[5][2] = { p_vertices[0][2] + z };


	x = r1*sin(3 * M_PI / 20);
	z = r1*(1 - cos(3 * M_PI / 20));

	p_vertices[6][0] = { p_vertices[1][0] + x };
	p_vertices[6][1] = { 1 };
	p_vertices[6][2] = { p_vertices[1][2] + z };
	x = r0*sin(3 * M_PI / 20);
	z = r0*(1 - cos(3 * M_PI / 20));

	p_vertices[7][0] = { p_vertices[0][0] + x };
	p_vertices[7][1] = { 1 };
	p_vertices[7][2] = { p_vertices[0][2] + z };

	x = r1*sin(M_PI / 5);
	z = r1*(1 - cos(M_PI / 5));

	p_vertices[8][0] = { p_vertices[1][0] + x };
	p_vertices[8][1] = { 1 };
	p_vertices[8][2] = { p_vertices[1][2] + z };
	x = r0*sin(M_PI / 5);
	z = r0*(1 - cos(M_PI / 5));

	p_vertices[9][0] = { p_vertices[0][0] + x };
	p_vertices[9][1] = { 1 };
	p_vertices[9][2] = { p_vertices[0][2] + z };

	x = r1*sin(M_PI / 4);
	z = r1*(1 - cos(M_PI / 4));

	p_vertices[10][0] = { p_vertices[1][0] + x };
	p_vertices[10][1] = { 1 };
	p_vertices[10][2] = { p_vertices[1][2] + z };

	x = r0*sin(M_PI / 4);
	z = r0*(1 - cos(M_PI / 4));

	p_vertices[11][0] = { p_vertices[0][0] + x };
	p_vertices[11][1] = { 1 };
	p_vertices[11][2] = { p_vertices[0][2] + z };

	vx1 = p_vertices[11][0];
	vz1 = p_vertices[11][2];
	vx2 = p_vertices[10][0];
	vz2 = p_vertices[10][2];

	GLushort p_indexes[11][3] = 
	{
	{ 0, 2, 1 },
	{ 0,3,2 },
	{ 4,2,3 },
	{ 5,4,3 },
	{ 5,6,4 },
	{ 6,5,7 },
	{ 6,7,8 },
	{ 7,9,8 },
	{ 8,9,10 },
	{ 9,11,10 }
	};
	vertices = new GLfloat[numVertices * 3];
	for (int i = 0; i < numVertices; i++) for (int j = 0; j < 3; j++) vertices[3 * i + j] = p_vertices[i][j];
	textures = new GLfloat[numVertices * 2];
	for (int i = 0; i < numVertices; i++) for (int j = 0; j < 2; j++) textures[2 * i + j] = p_textures[i][j];
	indexes = new GLushort[numFaces * 3];
	for (int i = 0; i < numFaces; i++) for (int j = 0; j < 3; j++) indexes[3 * i + j] = p_indexes[i][j];
	InitBuffers();
	SetMaterial(mtl);
}

