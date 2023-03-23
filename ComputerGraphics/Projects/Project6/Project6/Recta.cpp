//#include "stdafx.h"
#include <GL/glew.h>
#include "CGFigure.h"
#include "Pieza_Recta.h"
#include "Recta.h"


Recta::Recta(GLfloat l1, GLfloat l2, GLuint contador,GLfloat &vx1, GLfloat &vx2, GLfloat &vz1, GLfloat &vz2)
{
//Constructor que se encarga de representar una recta con las dimensiones como parámetros inicializando sus luces , su brillo y asociarle una textura
	CGMaterial* mtl0 = new CGMaterial(contador);
	mtl0->SetAmbientReflect(0.0f, 1.0f, 1.0f);
	mtl0->SetDifusseReflect(0.0f, 1.0f, 1.0f);
	mtl0->SetSpecularReflect(1.0f, 1.0f, 1.0f);
	mtl0->SetShininess(20.0f);
	mtl0->InitTexture("C:/ComputerGraphics/textures/Road/RectaStd.png");

	piece = new Pieza_Recta(mtl0, l1, l2,vx1,vx2,vz1,vz2);
	}
Recta::~Recta()
{
	 delete this->piece;
}

int Recta::GetNumPieces()
{
	return 1;
}

CGPiece* Recta::GetPiece(int index)
{
	return piece;
}

