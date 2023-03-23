#pragma once


// #include "stdafx.h" 
#include <GL/glew.h>
#include "CGPiece.h"
#define RM_CURV_EXT 44.8

class Pieza_CurvaExt : public CGPiece
{
public:
	Pieza_CurvaExt(CGMaterial* mtl, GLfloat p, GLfloat m, GLfloat r0, GLfloat r1, GLfloat &vx1, GLfloat &vx2, GLfloat &vz1, GLfloat &vz2);
	
};


