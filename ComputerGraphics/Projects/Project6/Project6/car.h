#pragma once

#include <GL/glew.h>
#include "car.h"
#include "CGPiece.h"
#include "CGFigure.h"

class car : public CGFigure {
private:
	CGPiece* pieces[69];

public:
	car();
	~car();
	virtual int GetNumPieces();
	virtual CGPiece* GetPiece(int i);
};

