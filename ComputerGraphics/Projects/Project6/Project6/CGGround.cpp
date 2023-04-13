//#include "stdafx.h"
#include <GL/glew.h>
#include "CGFigure.h"
#include "Pieza_Ground.h"
#include "CGGround.h"


CGGround::CGGround(GLfloat l1, GLfloat l2, GLuint contador, GLfloat& vx1, GLfloat& vx2, GLfloat& vz1, GLfloat& vz2)
{	

	glActiveTexture(GL_TEXTURE1);

	//Constructor de la base del circuito seleccionando la textura, los tipos de luces con su brillo y llamar al constructor de Pieza_Ground (para crear la pieza).
	CGMaterial* mtl0 = new CGMaterial(contador);
	mtl0->SetAmbientReflect(1.0f, 1.0f, 1.0f);
	mtl0->SetDifusseReflect(1.0f, 1.0f, 1.0f);
	mtl0->SetSpecularReflect(0.8f, 0.8f, 0.8f);
	mtl0->SetShininess(16.0f);
	mtl0->InitTexture("textures/Ground/stone.jpg");

	piece = new Pieza_Ground(mtl0, l1, l2, vx1, vx2, vz1, vz2);

}
CGGround::~CGGround()
{
	//Destructor de la pieza generada
	delete this->piece;
}

int CGGround::GetNumPieces()
{
	return 1;
}

CGPiece* CGGround::GetPiece(int index)
{
	//Método para devolver la pieza generada
	return piece;
}
