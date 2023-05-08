#ifndef CGFIGURE_H

#define CGFIGURE_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "CGShaderProgram.h"
#include "CGPiece.h"

//
// CLASE: CGFigure
//
// DESCRIPCIÓN: Clase abstracta que representa un objeto 
// formado por varias piezas
// 
class CGFigure {
protected:
	glm::mat4 model; // Model matrix

private:
	glm::vec3 m_direction;

public:
	CGFigure();
	void ResetLocation();
	void Translate(glm::vec3 t);
	void Rotate(GLfloat angle, glm::vec3 axis);
	void SetLocation(glm::mat4 loc);
	glm::mat4 GetLocation();

	void setLocation(glm::mat4 aux) { model = aux; };

	void desplazamiento_recta(GLdouble& x, GLdouble& z, GLdouble longitudrecta);
	void desplazamiento_curva(GLdouble& x, GLdouble& z, GLdouble radio, GLdouble angulo);

	void Draw(CGShaderProgram* program, glm::mat4 projection, glm::mat4 view);
	virtual int GetNumPieces() = 0;
	virtual CGPiece* GetPiece(int i) = 0;

	glm::vec3 GetDirection() const {return m_direction;}
};

#endif