#pragma once

// #include "stdafx.h" 
#include <GL/glew.h>
#include "CGPiece.h"

class Pieza_Recta : public CGPiece
{
public:
	Pieza_Recta(CGMaterial* mtl, GLfloat l1, GLfloat l2, GLfloat &vx1, GLfloat &vx2, GLfloat &vz1, GLfloat &vz2);
	
};