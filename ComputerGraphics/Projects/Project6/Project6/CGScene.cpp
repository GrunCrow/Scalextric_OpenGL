// #include "stdafx.h"
#include <GL/glew.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "CGScene.h"
#include "CGShaderProgram.h"
#include "CGFigure.h"
#include "CGGround.h"
#include "Recta.h"
#include "CurvaStd.h"
#include "CurvaInterior.h"
#include "CurvaExterior.h"

#include "CGSkybox.h"
#include "car.h"

#define LongRecta 35.0f
#define LongMediaRecta 17.5f
#define LongCuartoRecta 8.75f
#define RM_CURVA_INT 13.6

#define CurvaInterior1 9.7f
#define CurvaInterior2 17.5f
#define CurvaInteriorAnguloRadianes (M_PI / 4)
#define CurvaInteriorAnguloGrados 45

#define CurvaExterior1 40.9f
#define CurvaExterior2 48.9f
#define CurvaExteriorAnguloRadianes (M_PI / 8)
#define CurvaExteriorAnguloGrados 22.5f

#define CurvaEstandar1 25.3f
#define CurvaEstandar2 33.1f
#define CurvaEstandarAnguloRadianes (M_PI/4)
#define CurvaEstandarAnguloGrados 45

//
// FUNCIÓN: CGScene::CGScene()
//
// PROPÓSITO: Construye el objeto que representa la escena
//
CGScene::CGScene()
{
	GLuint contador = 0;
	GLfloat vx1 = 0, vx2 = 0, vz1 = 0, vz2 = 0;

	skybox = new CGSkybox();
	ground = new CGGround(LongRecta, 15.6f, contador, vx1, vx2, vz1, vz2);

	glm::vec3 Ldir = glm::vec3(1.0f, -0.8f, -1.0f);
	Ldir = glm::normalize(Ldir);

	light = new Light();
	light->SetLightDirection(Ldir);
	light->SetAmbientLight(glm::vec3(0.2f, 0.2f, 0.2f));
	light->SetDifusseLight(glm::vec3(0.8f, 0.8f, 0.8f));
	light->SetSpecularLight(glm::vec3(1.0f, 1.0f, 1.0f));

	//1 = recta estandar
	//2 = media recta 
	//3 = cuarto de recta 
	//4 = curva interior  
	//5 = curva exterior 
	//6 = curva estandar
	int pistas[74][2] = { {1,1},{4,1},{6,1},{ 6,1 },{5,1},{ 1,1 },{5,2},{ 5,2 },{5,2},{2,1},{ 5,2 },{ 5,2 },{ 5,2 },{ 5,2 },{ 5,2 },{1,1},{5,1},{6,1},{6,1},
	{1,1},{5,1},{4,1},{1,1},{1,1},{4,1},{4,1},{3,1},{4,2},{5,2},{2,1},{6,1},{2,1},{6,1},{1,1},{ 1,1 },{ 1,1 },
	{5,2},{6,2},{6,2},{4,2},{1,1},{ 1,1 },{ 1,1 },{ 1,1 },{ 1,1 },{ 1,1 },{ 1,1 },{5,1}, {6,1},{6,1},{1,1},{1,1},{4,1},{6,1},
	{4,1},{1,1},{6,2},{1,1},{1,1},{6,2},{6,2},{1,1},{1,1},{1,1},{6,1},{6,1},{6,1},{ 1,1 },{ 1,1 },{ 1,1 },{ 1,1 },{ 1,1 },{ 1,1 },{ 1,1 }
	};
	glm::mat4 aux;
	int RS = 0, MR = 0, CR = 0, CI = 0, CE = 0, CS = 0;
	GLdouble x = 0;
	GLdouble z = 0;

	for (int i = 0; i < 74; i++){
		int tipo = pistas[i][0];
		int t = pistas[i][1];
		switch (tipo){
		case 1:	// Recta Estandar
			if (RS == 0)
			{
				recta[RS] = new Recta(LongRecta, 15.6f / 2, contador, vx1, vx2, vz1, vz2);
				contador++;
				recta[RS]->desplazamiento_recta(x, z, LongRecta);
				recta[RS]->Translate(glm::vec3(x, 0.0f, z));
				aux = recta[RS]->GetLocation();
				recta[RS]->Translate(glm::vec3(-x, 0.0f, -z));
				RS++;
			}
			if (RS == 30)
			{
				recta[RS] = new Recta(LongRecta + 2, 15.6f / 2, contador, vx1, vx2, vz1, vz2);
				recta[RS]->setLocation(aux);
			}
			else
			{
				recta[RS] = new Recta(LongRecta, 15.6f / 2, contador, vx1, vx2, vz1, vz2);
				contador++;
				recta[RS]->setLocation(aux);
				recta[RS]->desplazamiento_recta(x, z, LongRecta);
				recta[RS]->Translate(glm::vec3(x, 0.0f, z));
				aux = recta[RS]->GetLocation();
				recta[RS]->Translate(glm::vec3(-x, 0.0f, -z));
				RS++;
			}



			break;
		case 2: // media recta
			mediaRecta[MR] = new Recta(LongMediaRecta, 15.6f / 2, contador, vx1, vx2, vz1, vz2);
			mediaRecta[MR]->setLocation(aux);
			mediaRecta[MR]->desplazamiento_recta(x, z, LongMediaRecta);
			mediaRecta[MR]->Translate(glm::vec3(x, 0.0f, z));
			aux = mediaRecta[MR]->GetLocation();
			mediaRecta[MR]->Translate(glm::vec3(-x, 0.0f, -z));
			MR++;
			contador++;
			break;
		case 3: // cuarto de recta
			cuartoRecta = new Recta(LongCuartoRecta, 15.6f / 2, contador, vx1, vx2, vz1, vz2);
			cuartoRecta->setLocation(aux);
			cuartoRecta->desplazamiento_recta(x, z, LongCuartoRecta);
			cuartoRecta->Translate(glm::vec3(x, 0.0f, z));
			aux = cuartoRecta->GetLocation();
			cuartoRecta->Translate(glm::vec3(-x, 0.0f, -z));
			CR++;
			contador++;
			break;
		case 4: //4 = curva interior  
			if (t == 1)
			{
				curvaInterior[CI] = new CurvaInterior(1, 5.0f, 5.8f, 21.4f, contador, vx1, vx2, vz1, vz2);
				curvaInterior[CI]->setLocation(aux);
				curvaInterior[CI]->desplazamiento_curva(x, z, 13.6, (M_PI / 4));
				curvaInterior[CI]->Translate(glm::vec3(x, 0.0f, z));
				curvaInterior[CI]->Rotate(-45, glm::vec3(0.0f, 1.0f, 0.0f));
				aux = curvaInterior[CI]->GetLocation();
				curvaInterior[CI]->Rotate(45, glm::vec3(0.0f, 1.0f, 0.0f));
				curvaInterior[CI]->Translate(glm::vec3(-x, 0.0f, -z));
				CI++;
				contador++;
			}
			else
			{
				curvaInterior[CI] = new CurvaInterior(1, 5.0f, 5.8f, 21.4f, contador, vx1, vx2, vz1, vz2);
				curvaInterior[CI]->setLocation(aux);
				curvaInterior[CI]->Rotate(225, glm::vec3(0.0f, 1.0f, 0.0f));
				curvaInterior[CI]->desplazamiento_curva(x, z, 13.6, (M_PI / 4));
				curvaInterior[CI]->Translate(glm::vec3(-x, 0.0f, -z));
				curvaInterior[CI]->Rotate(-180, glm::vec3(0.0f, 1.0f, 0.0f));
				aux = curvaInterior[CI]->GetLocation();
				curvaInterior[CI]->Rotate(180, glm::vec3(0.0f, 1.0f, 0.0f));
				CI++;
				contador++;
			}

			break;
		case 5: //5 = curva exterior 
			if (t == 1)
			{
				curvaExterior[CE] = new CurvaExterior(1, 5.0f, 37, 52.6, contador, vx1, vx2, vz1, vz2);
				curvaExterior[CE]->setLocation(aux);
				curvaExterior[CE]->desplazamiento_curva(x, z, 44.8, (M_PI / 8));
				curvaExterior[CE]->Translate(glm::vec3(x, 0.0f, z));
				curvaExterior[CE]->Rotate(-22.5, glm::vec3(0.0f, 1.0f, 0.0f));
				aux = curvaExterior[CE]->GetLocation();
				curvaExterior[CE]->Rotate(22.5, glm::vec3(0.0f, 1.0f, 0.0f));
				curvaExterior[CE]->Translate(glm::vec3(-x, 0.0f, -z));
				contador++;
				CE++;
			}
			else
			{
				curvaExterior[CE] = new CurvaExterior(1, 5.0f, 37, 52.6, contador, vx1, vx2, vz1, vz2);
				curvaExterior[CE]->setLocation(aux);
				curvaExterior[CE]->Rotate(202.5, glm::vec3(0.0f, 1.0f, 0.0f));
				curvaExterior[CE]->desplazamiento_curva(x, z, 44.8, (M_PI / 8));
				curvaExterior[CE]->Translate(glm::vec3(-x, 0.0f, -z));
				curvaExterior[CE]->Rotate(-180, glm::vec3(0.0f, 1.0f, 0.0f));
				aux = curvaExterior[CE]->GetLocation();
				curvaExterior[CE]->Rotate(180, glm::vec3(0.0f, 1.0f, 0.0f));
				contador++;
				CE++;
			}
			break;
		case 6: //6 = curva estandar
			if (t == 1)
			{
				curvaStd[CS] = new CurvaStd(1, 5, 21.4, 37.0, contador, vx1, vx2, vz1, vz2);
				curvaStd[CS]->setLocation(aux);
				curvaStd[CS]->desplazamiento_curva(x, z, 29.2, (M_PI / 4));
				curvaStd[CS]->Translate(glm::vec3(x, 0.0f, z));
				curvaStd[CS]->Rotate(-45, glm::vec3(0.0f, 1.0f, 0.0f));
				aux = curvaStd[CS]->GetLocation();
				curvaStd[CS]->Rotate(45, glm::vec3(0.0f, 1.0f, 0.0f));
				curvaStd[CS]->Translate(glm::vec3(-x, 0.0f, -z));
				CS++;
			}
			else
			{
				curvaStd[CS] = new CurvaStd(1, 5, 21.4, 37.0, contador, vx1, vx2, vz1, vz2);
				curvaStd[CS]->setLocation(aux);
				curvaStd[CS]->Rotate(225, glm::vec3(0.0f, 1.0f, 0.0f));
				curvaStd[CS]->desplazamiento_curva(x, z, 29.2, (M_PI / 4));
				curvaStd[CS]->Translate(glm::vec3(-x, 0.0f, -z));
				curvaStd[CS]->Rotate(-180, glm::vec3(0.0f, 1.0f, 0.0f));
				aux = curvaStd[CS]->GetLocation();
				curvaStd[CS]->Rotate(180, glm::vec3(0.0f, 1.0f, 0.0f));
				contador++;
				CS++;
			}
			break;
		}
	}
}

//
// FUNCIÓN: CGScene::~CGScene()
//
// PROPÓSITO: Destruye el objeto que representa la escena
//
CGScene::~CGScene()
{
	/*delete ground;*/
	for (int i = 0; i < 31; i++)
	{
		delete recta[i];
	}
	for (int i = 0; i < 8; i++)
	{
		delete curvaInterior[i];
	}
	for (int i = 0; i < 3; i++)
	{
		delete mediaRecta[i];
	}

	delete ground;
	delete skybox;
	for (int i = 0; i < 17; i++)
	{
		delete curvaStd[i];
	}
	for (int i = 0; i < 14; i++)
	{
		delete curvaExterior[i];
	}

	delete cuartoRecta;
}

//
// FUNCIÓN: CGScene::Draw()
//
// PROPÓSITO: Dibuja la escena
//
void CGScene::Draw(CGShaderProgram* program, glm::mat4 proj, glm::mat4 view)
{
	light->SetUniforms(program);
	skybox->Draw(program, proj, view);
	ground->Draw(program, proj, view);
	for (int i = 0; i < 31; i++)
	{
		recta[i]->Draw(program, proj, view);
	}

	for (int i = 0; i < 8; i++)
	{
		curvaInterior[i]->Draw(program, proj, view);
	}
	for (int i = 0; i < 17; i++)
	{
		curvaStd[i]->Draw(program, proj, view);
	}
	for (int i = 0; i < 14; i++)
	{
		curvaExterior[i]->Draw(program, proj, view);
	}
	for (int i = 0; i < 3; i++)
	{
		mediaRecta[i]->Draw(program, proj, view);
	}
	cuartoRecta->Draw(program, proj, view);
}

