#ifndef CGMODEL_H

#define CGMODEL_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "CGScene.h"
#include "CGCamera.h"
#include "CGShaderProgram.h"

class CGModel {
public:
	void Initialize(GLsizei w, GLsizei h);
	void Finalize();
	void RenderScene();
	void KeyboardAction(int virtualKey);

	void Update();

	void MouseButton(int button, int action);
	void MouseMove(double xpos, double ypos);

	void ReSize(GLsizei w, GLsizei h);

private:
	glm::vec3 posBeg;
	glm::vec3 dirBeg;
	glm::vec3 upBeg;
	glm::mat4 matseg;
	glm::mat4 projection;
	glm::mat4 view;

	CGShaderProgram* program;
	CGScene* scene;
	CGCamera* camera;
	CGFigure* Coche1;
	CGFigure* Coche2;

	bool f2 = false;
	int seleccion = 1;
	int Indice_1 = 0;
	int Indice_2 = 0;

	GLfloat Dist_Recorrida1 = 0;
	GLfloat Dist_Recorrida2 = 0;
	GLfloat velocidad = 0;
	GLfloat velocidad2 = 0;
	GLfloat Dist_CocheX1 = 0;
	GLfloat Dist_CocheX2 = 0;
	GLfloat Dist_CocheZ1 = 0;
	GLfloat Dist_CocheZ2 = 0;

	int Pistas[74][2] = { { 1,1 },{ 1,1 },{ 4,1 },{ 6,1 },{ 6,1 },{ 5,1 },{ 1,1 },{ 5,2 },{ 5,2 },{ 5,2 },{ 2,1 },{ 5,2 },{ 5,2 },{ 5,2 },{ 5,2 },{ 5,2 },{ 1,1 },{ 5,1 },{ 6,1 },{ 6,1 },
	{ 1,1 },{ 5,1 },{ 4,1 },{ 1,1 },{ 1,1 },{ 4,1 },{ 4,1 },{ 3,1 },{ 4,2 },{ 5,2 },{ 2,1 },{ 6,1 },{ 2,1 },{ 6,1 },{ 1,1 },{ 1,1 },{ 1,1 },
	{ 5,2 },{ 6,2 },{ 6,2 },{ 4,2 },{ 1,1 },{ 1,1 },{ 1,1 },{ 1,1 },{ 1,1 },{ 1,1 },{ 1,1 },{ 5,1 },{ 6,1 },{ 6,1 },{ 1,1 },{ 1,1 },{ 4,1 },{ 6,1 },
	{ 4,1 },{ 1,1 },{ 6,2 },{ 1,1 },{ 1,1 },{ 6,2 },{ 6,2 },{ 1,1 },{ 1,1 },{ 1,1 },{ 6,1 },{ 6,1 },{ 6,1 },{ 1,1 },{ 1,1 },{ 1,1 },{ 1,1 },{ 1,1 },{ 1,1 }
	};

	void InitTexture(GLuint id, const char* filename);
	void CameraConstraints();
};

#endif
