#ifndef CGSCENE_H

#define CGSCENE_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "CGShaderProgram.h"
#include "CGFigure.h"
#include "CGLight.h"
#include "CGSkybox.h"

class CGScene {
public:
	CGScene();
	~CGScene();
	void Draw(CGShaderProgram* program, glm::mat4 proj, glm::mat4 view);
	void desplazar(GLfloat& x, GLfloat& z, GLfloat& inclinacion, GLint direccion, GLfloat radio);

private:
	CGFigure* ground;
	int cantidadRectas = 0;
	CGFigure* recta[31];
	CGFigure* mediaRecta[3];
	CGFigure* cuartoRecta;
	CGFigure* curvaInterior[8];
	CGFigure* curvaStd[17];
	CGFigure* curvaExterior[14];
	CGFigure* coche;
	CGLight* light;
	CGSkybox* skybox;
};

#endif