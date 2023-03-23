#pragma once

// #include "stdafx.h" 
#include <GL/glew.h>
#include "CGFigure.h"

//
// CLASE: CGGround
//
// DESCRIPCIÓN: Representa un cuadrado dibujado en el suelo
// 
class Pieza_Ground : public CGPiece {
public:
	Pieza_Ground(CGMaterial* mtl, GLfloat l1, GLfloat l2, GLfloat &vx1, GLfloat &vx2, GLfloat &vz1, GLfloat &vz2);
};

