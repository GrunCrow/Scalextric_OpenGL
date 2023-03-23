#pragma once
#include <GL/glew.h>
#include "CGFigure.h"
#include "Pieza_CurvaSTD.h"
//
// CLASE: Disk3D
//
// DESCRIPCIÓN: Representa un disco de radio interior 'r0' (puede ser cero), 
//              radio exterior 'r1', dividido en 'p' capas y 'm' sectores.
//
class CurvaStd : public CGFigure {

private:
	CGPiece * piece;
public:
	CurvaStd(GLint p, GLint m, GLfloat r0, GLfloat r1, GLuint contador, GLfloat &vx1, GLfloat &vx2, GLfloat &vz1, GLfloat &vz2);

	~CurvaStd();
	virtual int GetNumPieces();
	virtual CGPiece* GetPiece(int i);


};

