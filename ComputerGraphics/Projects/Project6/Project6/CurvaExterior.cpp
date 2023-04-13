// #include "stdafx.h"
#include <GL/glew.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "CGFigure.h"
#include "CurvaExterior.h"


CurvaExterior::CurvaExterior(GLint p, GLint m, GLfloat r0, GLfloat r1, GLuint contador, GLfloat &vx1, GLfloat &vx2, GLfloat &vz1, GLfloat &vz2)
{
//Constructor que se encarga de representar una curva con m sectores, p capas , r1 radio exterior y r0 radio interior
	CGMaterial* mtl0 = new CGMaterial(contador);
	mtl0->SetAmbientReflect(0.0f, 1.0f, 1.0f);
	mtl0->SetDifusseReflect(0.0f, 1.0f, 1.0f);
	mtl0->SetSpecularReflect(1.0f, 1.0f, 1.0f);
	mtl0->SetShininess(20.0f);

	// mtl0->InitTexture("C:/ComputerGraphics/textures/Road/CurvaExterior.png");
	mtl0->InitTexture("textures/Road/RectaStd.jpg");
	
	piece = new Pieza_CurvaExt(mtl0, p,m,r0,r1,vx1,vx2,vz1,vz2);
	
}


CurvaExterior::~CurvaExterior()
{
//Destructor de la curva
	delete this->piece;
}

int CurvaExterior::GetNumPieces()
{
	return 1;
}

CGPiece* CurvaExterior::GetPiece(int index)
{
//Método para devolver la pieza generada
	return piece;
}

