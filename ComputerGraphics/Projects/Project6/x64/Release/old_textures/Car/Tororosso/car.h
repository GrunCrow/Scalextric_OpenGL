#pragma once

#include <GL/glew.h>
#include "CGObject.h"
#include "CGPiece.h"

class car : public CGObject {
private:
	CGPiece* pieces[69];

public:
	car();
	~car();
	virtual int GetNumPieces();
	virtual CGPiece* GetPiece(int i);
};

