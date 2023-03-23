#pragma once
#include <GL/glew.h>
#include "CGFigure.h"

//
// CLASE: Recta
//
// DESCRIPCIÓN: Representa un rectangulo dibujado en el suelo
// 

class Recta : public CGFigure {
private:
	CGPiece* piece;
public:
	Recta(GLfloat l1, GLfloat l2,GLuint contador,GLfloat &vx1, GLfloat &vx2, GLfloat &vz1, GLfloat &vz2);

	~Recta();
	virtual int GetNumPieces();
	virtual CGPiece* GetPiece(int i);
};

