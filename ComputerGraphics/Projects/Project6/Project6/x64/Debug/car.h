#ifndef X64/DEBUG/CAR_H
#define X64/DEBUG/CAR_H

#include "stdafx.h" 
#include <glew.h>
#include "Figure3D.h"
#include "Piece3D.h"

class x64/Debug/car : public Figure3D {
private:
	Piece3D* pieces[0];

public:
	x64/Debug/car();
	~x64/Debug/car();
	virtual int GetNumPieces();
	virtual Piece3D* GetPiece(int i);
};

#endif
