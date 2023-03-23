#pragma once
// #include "stdafx.h" 
#include <GL/glew.h>
#include "CGPiece.h"

class Pieza_CurvaSTD : public CGPiece
{
public:
	Pieza_CurvaSTD(CGMaterial* mtl, GLfloat p, GLfloat m, GLfloat r0, GLfloat r1, GLfloat &vx1, GLfloat &vx2, GLfloat &vz1, GLfloat &vz2);

};
