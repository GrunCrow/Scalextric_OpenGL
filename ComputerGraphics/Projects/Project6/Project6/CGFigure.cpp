// #include "stdafx.h"
#include <GL/glew.h>
#include <FreeImage.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "CGFigure.h"


CGFigure::CGFigure()
{
	// ...
	m_direction = glm::vec3(0.0f, 0.0f, 1.0f); // Inicializa la dirección hacia adelante en el eje Z
}

void CGFigure::ResetLocation()
{
	model = glm::mat4(1.0f);
}

void CGFigure::SetLocation(glm::mat4 loc)
{
	model = loc;
}

glm::mat4 CGFigure::GetLocation(){
	return model;
}

void CGFigure::Translate(glm::vec3 t)
{
	model = glm::translate(model, t);
}

void CGFigure::Rotate(GLfloat angle, glm::vec3 axis)
{
	model = glm::rotate(model, glm::radians(angle), axis);
	m_direction = glm::mat3(model) * glm::vec3(0.0f, 0.0f, 1.0f);
}

void CGFigure::Draw(CGShaderProgram* program, glm::mat4 projection, glm::mat4 view, glm::mat4 shadowViewMatrix)
{
	int num = GetNumPieces();
	for (int i = 0; i < num; i++)
	{
		GetPiece(i)->Draw(program, projection, view, model, shadowViewMatrix);
	}
}

void CGFigure::desplazamiento_recta(GLdouble& x, GLdouble& z, GLdouble longitudrecta)
{
	x = longitudrecta * cos(0);
	z = longitudrecta * sin(0);
}

void CGFigure::desplazamiento_curva(GLdouble& x, GLdouble& z, GLdouble radio, GLdouble angulo)
{
	z = radio * (1 - cos((angulo)));
	x = radio * sin((angulo));
}