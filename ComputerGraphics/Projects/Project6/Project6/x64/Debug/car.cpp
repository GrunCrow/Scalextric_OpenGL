#include "stdafx.h" 
#include <glew.h>
#include "Figure3D.h"
#include "Piece3D.h"
#include "x64/Debug/car.h"
#include "x64/Debug/car_pieces.h"

x64/Debug/car::x64/Debug/car()
{
}

x64/Debug/car::~x64/Debug/car()
{
	for (int i = 0; i < 0; i++) delete pieces[i];
}

int x64/Debug/car::GetNumPieces()
{
	return 0;
}

Piece3D* x64/Debug/car::GetPiece(int index)
{
	return pieces[index];
}

