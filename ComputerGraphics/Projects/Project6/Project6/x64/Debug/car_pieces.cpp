#include "stdafx.h" 
#include <glew.h>
#include "Figure3D.h"
#include "Piece3D.h"
#include "x64/Debug/car_pieces.h"
#include "x64/Debug/car_pieces_pieces.h"

x64/Debug/car_pieces::x64/Debug/car_pieces()
{
}

x64/Debug/car_pieces::~x64/Debug/car_pieces()
{
	for (int i = 0; i < 0; i++) delete pieces[i];
}

int x64/Debug/car_pieces::GetNumPieces()
{
	return 0;
}

Piece3D* x64/Debug/car_pieces::GetPiece(int index)
{
	return pieces[index];
}

