// #include "stdafx.h"
// Archivos de encabezado de Windows:
// Archivos de encabezado en tiempo de ejecución de C
#include <windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

#define WIN32_LEAN_AND_MEAN             // Excluir material rara vez utilizado de encabezados de Windows

#include <GL/glew.h>
#include <FreeImage.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SDKDDKVer.h>
#include <GLFW/glfw3.h>

#include "CGModel.h"
#include "CGCamera.h"
#include "CGScene.h"
#include "CGShaderProgram.h"
#include "car.h"


#include <iostream>
#include <string>


#define LongRecta 35.0f
#define LongMediaRecta 17.5f
#define LongCuartoRecta 8.75f


void printError(char* msg)
{
	//Método para redactar un mensaje de error en  "ErrorLog.txt"
	FILE* f;
	fopen_s(&f, "ErrorLog.txt", "w");
	fprintf(f, "%s", msg);
	fclose(f);
}



void CGModel::Initialize(GLsizei w, GLsizei h)
{
	//Método que inicializa el modelo 3D a generar


		// Parte para crear el programa
	program = new CGShaderProgram();
	if (program->IsLinked() == GL_TRUE) program->Use();
	else printError(program->GetLog());


	// Parte para cargar la textura
	GLuint textureId;
	glGenTextures(1, &textureId);
	glActiveTexture(GL_TEXTURE0);
	// AÑADIDO:
	//glBindTexture(GL_TEXTURE_2D, textureId);
	//glEnable(GL_TEXTURE_2D);

	InitTexture(textureId, "textures/Road/RectaStd.jpg");
	program->SetUniformI("BaseTex", 0);

	// Parte para crear la "camera"
	camera = new CGCamera();

	camera->SetPosition(0.0f, 5.0f, 30.0f);

	posBeg = camera->GetPosition();
	dirBeg = camera->GetDirection();

	// Parte para crear la matriz View de la "camera"
	view = camera->ViewMatrix();

	// Parte para inicializar las posiciones de las figuras (coche y coche2)
	scene = new CGScene();

	Coche1 = new car();
	Coche1->Translate(glm::vec3(0, 1.0f, 3.9f));
	Coche1->Rotate(90, glm::vec3(0.0f, 0.0f, 1.0f));
	Coche1->Rotate(90, glm::vec3(0.0f, 1.0f, 0.0f));
	Coche2 = new car();
	Coche2->Translate(glm::vec3(0.0f, 1.0f, -3.9f));
	Coche2->Rotate(90, glm::vec3(0.0f, 0.0f, 1.0f));
	Coche2->Rotate(90, glm::vec3(0.0f, 1.0f, 0.0f));


	// Parte que asocia el viewport y el Clipping Volume
	ReSize(w, h);


	// Parte para las opciones del dibujo
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);	
	glFrontFace(GL_CCW);
	glPolygonMode(GL_FRONT, GL_FILL);
	glDepthFunc(GL_LEQUAL);


	// Parte del antialiasing
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_POLYGON_SMOOTH);
	matseg = Coche1->GetLocation();
}


void CGModel::InitTexture(GLuint texture, const char* filename)
{
	//Método donde se cargan las texturas del programa
	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(filename, 0);
	FIBITMAP* bitmap = FreeImage_Load(format, filename);
	FIBITMAP* pImage = FreeImage_ConvertTo32Bits(bitmap);
	int nWidth = FreeImage_GetWidth(pImage);
	int nHeight = FreeImage_GetHeight(pImage);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, nWidth, nHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(pImage));
	FreeImage_Unload(pImage);
}


void CGModel::Finalize()
{
	//Método que libera la memoria reservada (delete)
	delete camera;
	delete scene;
	delete program;
	delete Coche1;
	delete Coche2;

	// AÑADIDO
	//glDisable(GL_TEXTURE_2D);
}


void CGModel::ReSize(GLsizei w, GLsizei h)
{
	//Método que modifica la configuracion del viewport al cambiar el windowsize
	double fov = 15.0 * M_PI / 180.0;
	double sin_fov = sin(fov);
	double cos_fov = cos(fov);
	if (h == 0) h = 1;
	GLfloat aspectRatio = (GLfloat)w / (GLfloat)h;
	GLfloat wHeight = (GLfloat)(sin_fov * 0.2 / cos_fov);
	GLfloat wWidth = wHeight * aspectRatio;

	glViewport(0, 0, w, h);
	projection = glm::frustum(-wWidth, wWidth, -wHeight, wHeight, 0.2f, 2000.0f);
}


void CGModel::RenderScene()
{
	//Método que genera la imagen
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	view = camera->ViewMatrix();
	scene->Draw(program, projection, view);
	Coche1->Draw(program, projection, view);
	Coche2->Draw(program, projection, view);
}


void CGModel::Update()
{
	//Método que se encarga de dar animación a la escena
	int t = Pistas[Indice_1][1];
	int tt = Pistas[Indice_2][1];
	Dist_Recorrida1 = (velocidad * 0.02);
	Dist_Recorrida2 = (velocidad2 * 0.02);

	if (Pistas[Indice_1][0] == 3 || Pistas[Indice_1][0] == 2 || Pistas[Indice_1][0] == 1)
	{

		if (Pistas[Indice_1][0] == 1)
		{
			if (velocidad < 7 && velocidad != 0) velocidad++;
			GLdouble dx = 0, dz = 0;
			Dist_CocheX1 = Dist_CocheX1 + Dist_Recorrida1;

			if (Dist_CocheX1 <= LongRecta)
			{
				Coche1->Translate(glm::vec3(0, -Dist_Recorrida1, 0));
				posBeg -= glm::vec3(0, -Dist_Recorrida1, 0);
			}
			else
			{
				Dist_Recorrida1 = 0;
				Indice_1++;
				Dist_CocheX1 = 0;
				Coche1->Translate(glm::vec3(0, -Dist_Recorrida1, 0));
				posBeg -= glm::vec3(0, -Dist_Recorrida1, 0);
			}
		}
		if (Pistas[Indice_1][0] == 2)
		{
			if (velocidad < 7 && velocidad != 0) velocidad++;
			Dist_CocheX1 = Dist_CocheX1 + Dist_Recorrida1;

			if (Dist_CocheX1 <= LongMediaRecta)
			{
				Coche1->Translate(glm::vec3(0, -Dist_Recorrida1, 0));
			}
			else
			{
				Dist_Recorrida1 = 0;
				Indice_1++;
				Dist_CocheX1 = 0;
				Coche1->Translate(glm::vec3(0, -Dist_Recorrida1, 0));
			}
		}
		if (Pistas[Indice_1][0] == 3)
		{
			if (velocidad < 7 && velocidad != 0) velocidad++;
			Dist_CocheX1 = Dist_CocheX1 + Dist_Recorrida1;

			if (Dist_CocheX1 <= LongCuartoRecta)
			{
				Coche1->Translate(glm::vec3(0, -Dist_Recorrida1, 0));
			}
			else
			{
				Dist_Recorrida1 = 0;
				Indice_1++;
				Dist_CocheX1 = 0;
				Coche1->Translate(glm::vec3(0, -Dist_Recorrida1, 0));
			}
		}
	}
	else
	{

		if (Pistas[Indice_1][0] == 4)
		{
			if (velocidad > 7 && velocidad != 0)
				velocidad = velocidad - 3;

			if (t == 1)
			{
				GLdouble x = 0, z = 0, dx = 0, dz = 0;;
				GLdouble angulo = 0;
				Coche1->desplazamiento_curva(x, z, 9.7, M_PI / 4);
				Dist_CocheX1 = Dist_CocheX1 + Dist_Recorrida1;
				Dist_CocheZ1 = Dist_CocheZ1 + Dist_Recorrida1;
				angulo = angulo + (((45) * Dist_Recorrida1) / x);
				GLdouble ang = (angulo * (M_PI / 4)) / 45;
				Coche1->desplazamiento_curva(dx, dz, 9.7, ang);

				if (Dist_CocheX1 <= x && angulo <= 45)
				{
					Coche1->Translate(glm::vec3(dz, -dx, 0));
					Coche1->Rotate(-angulo, glm::vec3(0.0f, 0.0f, 1.0f));
				}
				else
				{
					Dist_Recorrida1 = 0;
					Indice_1++;
					Coche1->Rotate(-angulo, glm::vec3(0.0f, 0.0f, 1.0f));
					Dist_CocheX1 = 0;
					Dist_CocheZ1 = 0;
				}
			}
			else
			{
				GLdouble x = 0, z = 0, dx = 0, dz = 0;;
				GLdouble angulo = 0;
				Coche1->desplazamiento_curva(x, z, 17.5, M_PI / 4);
				Dist_CocheX1 = Dist_CocheX1 + Dist_Recorrida1;
				Dist_CocheZ1 = Dist_CocheZ1 + Dist_Recorrida1;
				angulo = angulo + (((45) * Dist_Recorrida1) / x);
				GLdouble ang = (angulo * (M_PI / 4)) / 45;
				Coche1->desplazamiento_curva(dx, dz, 17.5, ang);

				if (Dist_CocheX1 <= x && angulo <= 45)
				{
					Coche1->Translate(glm::vec3(dz, -dx, 0));
					Coche1->Rotate(angulo, glm::vec3(0.0f, 0.0f, 1.0f));
				}
				else
				{
					Dist_Recorrida1 = 0;
					Indice_1++;
					Coche1->Rotate(angulo, glm::vec3(0.0f, 0.0f, 1.0f));
					Dist_CocheX1 = 0;
					Dist_CocheZ1 = 0;
				}
			}
		}
		if (Pistas[Indice_1][0] == 6)
		{
			if (velocidad > 7 && velocidad != 0) velocidad - 3;

			if (t == 1)
			{
				GLdouble x = 0, z = 0, dx = 0, dz = 0;;
				GLdouble angulo = 0;
				Coche1->desplazamiento_curva(x, z, 25.3, M_PI / 4);
				Dist_CocheX1 = Dist_CocheX1 + Dist_Recorrida1;
				Dist_CocheZ1 = Dist_CocheZ1 + Dist_Recorrida1;
				angulo = angulo + (((45) * Dist_Recorrida1) / x);
				GLdouble ang = (angulo * (M_PI / 4)) / 45;
				Coche1->desplazamiento_curva(dx, dz, 25.3, ang);

				if (Dist_CocheX1 <= x && angulo <= 45)
				{
					Coche1->Translate(glm::vec3(dz, -dx, 0));
					Coche1->Rotate(-angulo, glm::vec3(0.0f, 0.0f, 1.0f));
				}
				else
				{
					Dist_Recorrida1 = 0;
					Indice_1++;
					Coche1->Rotate(-angulo, glm::vec3(0.0f, 0.0f, 1.0f));
					Dist_CocheX1 = 0;
					Dist_CocheZ1 = 0;
				}
			}
			else
			{

				GLdouble x = 0, z = 0, dx = 0, dz = 0;;
				GLdouble angulo = 0;
				Coche1->desplazamiento_curva(x, z, 33.1, M_PI / 4);
				Dist_CocheX1 = Dist_CocheX1 + Dist_Recorrida1;
				Dist_CocheZ1 = Dist_CocheZ1 + Dist_Recorrida1;
				angulo = angulo + (((45) * Dist_Recorrida1) / x);
				GLdouble ang = (angulo * (M_PI / 4)) / 45;
				Coche1->desplazamiento_curva(dx, dz, 33.1, ang);

				if (Dist_CocheX1 <= x && angulo <= 45)
				{
					Coche1->Translate(glm::vec3(dz, -dx, 0));
					Coche1->Rotate(angulo, glm::vec3(0.0f, 0.0f, 1.0f));
				}
				else
				{
					Dist_Recorrida1 = 0;
					Indice_1++;
					Coche1->Rotate(angulo, glm::vec3(0.0f, 0.0f, 1.0f));
					Dist_CocheX1 = 0;
					Dist_CocheZ1 = 0;
				}
			}
		}
		if (Pistas[Indice_1][0] == 5)
		{
			if (velocidad > 7 && velocidad != 0) velocidad - 3;

			if (t == 1)
			{
				GLdouble x = 0, z = 0, dx = 0, dz = 0;;
				GLdouble angulo = 0;
				Coche1->desplazamiento_curva(x, z, 40.9, M_PI / 8);
				Dist_CocheX1 = Dist_CocheX1 + Dist_Recorrida1;
				Dist_CocheZ1 = Dist_CocheZ1 + Dist_Recorrida1;
				angulo = angulo + (((22.5) * Dist_Recorrida1) / x);
				GLdouble ang = (angulo * (M_PI / 8)) / 22.5;
				Coche1->desplazamiento_curva(dx, dz, 40.9, ang);

				if (Dist_CocheX1 <= x && angulo <= 22.5)
				{
					Coche1->Translate(glm::vec3(dz, -dx, 0));
					Coche1->Rotate(-angulo, glm::vec3(0.0f, 0.0f, 1.0f));
				}
				else
				{
					Dist_Recorrida1 = 0;
					Indice_1++;
					Coche1->Rotate(-angulo, glm::vec3(0.0f, 0.0f, 1.0f));
					Dist_CocheX1 = 0;
					Dist_CocheZ1 = 0;
				}
			}
			else
			{

				GLdouble x = 0, z = 0, dx = 0, dz = 0;;
				GLdouble angulo = 0;
				Coche1->desplazamiento_curva(x, z, 48.9, M_PI / 8);
				Dist_CocheX1 = Dist_CocheX1 + Dist_Recorrida1;
				angulo = angulo + (((22.5) * Dist_Recorrida1) / x);
				GLdouble ang = (angulo * (M_PI / 8)) / 22.5;
				Coche1->desplazamiento_curva(dx, dz, 48.9, ang);
				Dist_CocheZ1 = Dist_CocheZ1 + dz;

				if (Dist_CocheX1 <= x && angulo <= 22.5 && Dist_CocheZ1 <= z)
				{
					Coche1->Rotate(angulo, glm::vec3(0.0f, 0.0f, 1.0f));
					Coche1->Translate(glm::vec3(dz, -dx, 0));
				}
				else
				{
					Dist_Recorrida1 = 0;
					Indice_1++;
					Coche1->Rotate(angulo, glm::vec3(0.0f, 0.0f, 1.0f));
					Dist_CocheX1 = 0;
					Dist_CocheZ1 = 0;
				}
			}
		}
	}

	if (Pistas[Indice_2][0] == 1 || Pistas[Indice_2][0] == 2 || Pistas[Indice_2][0] == 3)
	{
		if (Pistas[Indice_2][0] == 1)
		{
			if (velocidad2 < 7 && velocidad2 != 0) velocidad2++;
			GLdouble dx = 0, dz = 0;
			Dist_CocheX2 = Dist_CocheX2 + Dist_Recorrida2;

			if (Dist_CocheX2 <= LongRecta)
			{
				Coche2->Translate(glm::vec3(0, -Dist_Recorrida2, 0));
			}
			else
			{
				Dist_Recorrida2 = 0;
				Indice_2++;
				Dist_CocheX2 = 0;
				Coche2->Translate(glm::vec3(0, -Dist_Recorrida2, 0));
			}
		}
		if (Pistas[Indice_2][0] == 2)
		{
			if (velocidad2 < 7 && velocidad2 != 0) velocidad2++;
			Dist_CocheX2 = Dist_CocheX2 + Dist_Recorrida2;

			if (Dist_CocheX2 <= LongMediaRecta)
			{
				Coche2->Translate(glm::vec3(0, -Dist_Recorrida2, 0));
			}
			else
			{
				Dist_Recorrida2 = 0;
				Indice_2++;
				Dist_CocheX2 = 0;
				Coche2->Translate(glm::vec3(0, -Dist_Recorrida2, 0));
			}
		}
		if (Pistas[Indice_2][0] == 3)
		{
			if (velocidad2 < 7 && velocidad2 != 0) velocidad2++;
			Dist_CocheX2 = Dist_CocheX2 + Dist_Recorrida2;

			if (Dist_CocheX2 <= LongCuartoRecta)
			{
				Coche2->Translate(glm::vec3(0, -Dist_Recorrida2, 0));
			}
			else
			{
				Dist_Recorrida2 = 0;
				Indice_2++;
				Dist_CocheX2 = 0;
				Coche2->Translate(glm::vec3(0, -Dist_Recorrida2, 0));
			}
		}
	}
	else
	{

		if (Pistas[Indice_2][0] == 4)
		{
			if (velocidad2 > 7 && velocidad2 != 0) velocidad2 - 3;

			if (tt == 2)
			{
				GLdouble x = 0, z = 0, dx = 0, dz = 0;;
				GLdouble angulo = 0;
				Coche2->desplazamiento_curva(x, z, 9.7, M_PI / 4);
				Dist_CocheX2 = Dist_CocheX2 + Dist_Recorrida2;
				Dist_CocheZ2 = Dist_CocheZ2 + Dist_Recorrida2;
				angulo = angulo + (((45) * Dist_Recorrida2) / x);
				GLdouble ang = (angulo * (M_PI / 4)) / 45;
				Coche2->desplazamiento_curva(dx, dz, 9.7, ang);

				if (Dist_CocheX2 <= x && angulo <= 45)
				{
					Coche2->Translate(glm::vec3(dz, -dx, 0));
					Coche2->Rotate(angulo, glm::vec3(0.0f, 0.0f, 1.0f));
				}
				else
				{
					Dist_Recorrida2 = 0;
					Indice_2++;
					Coche2->Rotate(angulo, glm::vec3(0.0f, 0.0f, 1.0f));
					Dist_CocheX2 = 0;
					Dist_CocheZ2 = 0;
				}
			}
			else
			{
				GLdouble x = 0, z = 0, dx = 0, dz = 0;;
				GLdouble angulo = 0;
				Coche2->desplazamiento_curva(x, z, 17.5, M_PI / 4);
				Dist_CocheX2 = Dist_CocheX2 + Dist_Recorrida2;
				Dist_CocheZ2 = Dist_CocheZ2 + Dist_Recorrida2;
				angulo = angulo + (((45) * Dist_Recorrida2) / x);
				GLdouble ang = (angulo * (M_PI / 4)) / 45;
				Coche2->desplazamiento_curva(dx, dz, 17.5, ang);

				if (Dist_CocheX2 <= x && angulo <= 45)
				{
					Coche2->Translate(glm::vec3(dz, -dx, 0));
					Coche2->Rotate(-angulo, glm::vec3(0.0f, 0.0f, 1.0f));
				}
				else
				{
					Dist_Recorrida2 = 0;
					Indice_2++;
					Coche2->Rotate(-angulo, glm::vec3(0.0f, 0.0f, 1.0f));
					Dist_CocheX2 = 0;
					Dist_CocheZ2 = 0;
				}
			}
		}
		if (Pistas[Indice_2][0] == 6)
		{
			if (velocidad2 > 7 && velocidad2 != 0)velocidad2 - 3;

			if (tt == 2)
			{
				GLdouble x = 0, z = 0, dx = 0, dz = 0;;
				GLdouble angulo = 0;
				Coche2->desplazamiento_curva(x, z, 25.3, M_PI / 4);
				Dist_CocheX2 = Dist_CocheX2 + Dist_Recorrida2;
				Dist_CocheZ2 = Dist_CocheZ2 + Dist_Recorrida2;
				angulo = angulo + (((45) * Dist_Recorrida2) / x);
				GLdouble ang = (angulo * (M_PI / 4)) / 45;
				Coche2->desplazamiento_curva(dx, dz, 25.3, ang);

				if (Dist_CocheX2 <= x && angulo <= 45)
				{
					Coche2->Translate(glm::vec3(dz, -dx, 0));
					Coche2->Rotate(angulo, glm::vec3(0.0f, 0.0f, 1.0f));
				}
				else
				{
					Dist_Recorrida2 = 0;
					Indice_2++;
					Coche2->Rotate(angulo, glm::vec3(0.0f, 0.0f, 1.0f));
					Dist_CocheX2 = 0;
					Dist_CocheZ2 = 0;
				}
			}
			else
			{
				GLdouble x = 0, z = 0, dx = 0, dz = 0;;
				GLdouble angulo = 0;
				Coche2->desplazamiento_curva(x, z, 33.1, M_PI / 4);
				Dist_CocheX2 = Dist_CocheX2 + Dist_Recorrida2;
				Dist_CocheZ2 = Dist_CocheZ2 + Dist_Recorrida2;
				angulo = angulo + (((45) * Dist_Recorrida2) / x);
				GLdouble ang = (angulo * (M_PI / 4)) / 45;
				Coche2->desplazamiento_curva(dx, dz, 33.1, ang);

				if (Dist_CocheX2 <= x && angulo <= 45)
				{
					Coche2->Translate(glm::vec3(dz, -dx, 0));
					Coche2->Rotate(-angulo, glm::vec3(0.0f, 0.0f, 1.0f));
				}
				else
				{
					Dist_Recorrida2 = 0;
					Indice_2++;
					Coche2->Rotate(-angulo, glm::vec3(0.0f, 0.0f, 1.0f));
					Dist_CocheX2 = 0;
					Dist_CocheZ2 = 0;
				}
			}
		}
		if (Pistas[Indice_2][0] == 5)
		{
			if (velocidad2 > 7 && velocidad2 != 0) velocidad2 - 3;
			if (tt == 2)
			{
				GLdouble x = 0, z = 0, dx = 0, dz = 0;;
				GLdouble angulo = 0;
				Coche2->desplazamiento_curva(x, z, 40.9, M_PI / 8);
				Dist_CocheX2 = Dist_CocheX2 + Dist_Recorrida2;
				Dist_CocheZ2 = Dist_CocheZ2 + Dist_Recorrida2;
				angulo = angulo + (((22.5) * Dist_Recorrida2) / x);
				GLdouble ang = (angulo * (M_PI / 8)) / 22.5;
				Coche2->desplazamiento_curva(dx, dz, 40.9, ang);

				if (Dist_CocheX2 <= x && angulo <= 22.5)
				{
					Coche2->Translate(glm::vec3(dz, -dx, 0));
					Coche2->Rotate(angulo, glm::vec3(0.0f, 0.0f, 1.0f));
				}
				else
				{
					Dist_Recorrida2 = 0;
					Indice_2++;
					Coche2->Rotate(angulo, glm::vec3(0.0f, 0.0f, 1.0f));
					Dist_CocheX2 = 0;
					Dist_CocheZ2 = 0;
				}
			}
			else
			{
				GLdouble x = 0, z = 0, dx = 0, dz = 0;;
				GLdouble angulo = 0;
				Coche2->desplazamiento_curva(x, z, 48.9, M_PI / 8);
				Dist_CocheX2 = Dist_CocheX2 + Dist_Recorrida2;
				angulo = angulo + (((22.5) * Dist_Recorrida2) / x);
				GLdouble ang = (angulo * (M_PI / 8)) / 22.5;
				Coche2->desplazamiento_curva(dx, dz, 48.9, ang);
				Dist_CocheZ2 = Dist_CocheZ2 + dz;

				if (Dist_CocheX2 <= x && angulo <= 22.5 && Dist_CocheZ2 <= z)
				{
					Coche2->Rotate(-angulo, glm::vec3(0.0f, 0.0f, 1.0f));
					Coche2->Translate(glm::vec3(dz, -dx, 0));
				}
				else
				{
					Dist_Recorrida2 = 0;
					Indice_2++;
					Coche2->Rotate(-angulo, glm::vec3(0.0f, 0.0f, 1.0f));
					Dist_CocheX2 = 0;
					Dist_CocheZ2 = 0;
				}
			}
		}
	}
	if (seleccion == 1){
		matseg = Coche1->GetLocation();
		camera->SetPosition(matseg[3][0]-5.0f, matseg[3][1] + 2.0f, matseg[3][2]);
		camera->SetDirection(matseg[1][0], matseg[1][1], matseg[1][2], matseg[2][0], matseg[2][1], matseg[2][2]);
	}
	if (seleccion == 2){
		matseg = Coche2->GetLocation();
		camera->SetPosition(matseg[3][0]-5.0f, matseg[3][1] + 2.0f, matseg[3][2]);
		camera->SetDirection(matseg[1][0], matseg[1][1], matseg[1][2], matseg[2][0], matseg[2][1], matseg[2][2]);
	}
}




//
// FUNCIÓN: Model3D::KeyboardAction(int)
//
// PROPÓSITO: respuesta a acciones de teclado
//
void CGModel::KeyboardAction(int virtualKey)
{
	GLfloat cam_pos_x;
	GLfloat cam_pos_y;
	GLfloat cam_pos_z;
	GLfloat cam_turn_step;
	//Método de respuesta para las teclas (Asociar teclas a ciertas acciones)
	
	/*switch (virtualKey)
	{
	case VK_UP:
		camera->TurnDown();
		break;
	case VK_DOWN:
		camera->TurnUp();
		break;
	case VK_LEFT:
		camera->TurnCCW();
		break;
	case VK_RIGHT:
		camera->TurnCW();
		break;
	case 'S':
		seleccion = 1;
		break;
	case VK_OEM_PLUS:
		camera->SetMoveStep(camera->GetMoveStep() + 2.0f);
		break;
	case VK_OEM_MINUS:
		camera->SetMoveStep(camera->GetMoveStep() - 2.0f);
		break;
	case 'Q':
		if (velocidad < 10)
		{
			velocidad++;
		}
		break;
	case 'A':
		if (velocidad > 0)
		{
			velocidad--;
		}
		break;
	case 'O':
		if (velocidad2 < 10)
		{
			velocidad2++;
		}
		break;
	case 'L':
		if (velocidad2 > 0)
		{
			velocidad2--;
		}
		break;
	case VK_F1:
		seleccion = 3;
		camera->SetTurnStep(90);
		camera->SetPosition(-70, 900, 130);
		camera->SetTurnStep(0.1f);
		break;
	case VK_F2:
		seleccion = 1;
		break;
	case VK_F3:
		seleccion = 2;
		break;
	case 'C':
		velocidad = 5;
		break;
	}*/

	
	
	switch (virtualKey){
		// MOVIMIENTO IZQ-DCHA- ARRIBA-ABAJO
		case GLFW_KEY_UP: //VK_UP:
			camera->TurnDown();
			break;
		case GLFW_KEY_DOWN: //VK_DOWN:
			camera->TurnUp();
			break;
		case GLFW_KEY_LEFT: //VK_LEFT:
			camera->TurnLeft();
			//camera->TurnCCW();
			break;
		case GLFW_KEY_RIGHT: //VK_RIGHT:
			camera->TurnRight();
			break;

		// GIRAR
		case GLFW_KEY_Z: //VK_LEFT:
			//camera->TurnLeft();
			camera->TurnCCW();
			break;
		case GLFW_KEY_X: //VK_RIGHT:
			camera->TurnCW();
			break;
		
		// SELECCION
		case GLFW_KEY_S: //'S':
			seleccion = 1;
			break;

		// MOVIMIENTO RECTO
		case GLFW_KEY_PERIOD: //VK_OEM_PLUS:
			camera->SetMoveStep(camera->GetMoveStep() + 2.0f);
			//glm::vec3 pos = camera->GetPosition();
			//camera->SetPosition(pos.x +1.0f, pos.y, pos.z);
			break;
		case GLFW_KEY_COMMA: //VK_OEM_MINUS:
			camera->SetMoveStep(camera->GetMoveStep() - 2.0f);
			//glm::vec3 pos = camera->GetPosition();
			//camera->SetPosition(pos.x + 1.0f, pos.y, pos.z);
			break;

		// VELOCIDADES
		case GLFW_KEY_Q: //'Q':
			if (velocidad < 10){
				velocidad++;
			}
			break;
		case GLFW_KEY_A: //'A':
			if (velocidad > 0){
				velocidad--;
			}
			break;
		case GLFW_KEY_O: //'O':
			if (velocidad2 < 10){
				velocidad2++;
			}
			break;
		case GLFW_KEY_L: //'L':
			if (velocidad2 > 0){
				velocidad2--;
			}
			break;

		// VISTAS
		case GLFW_KEY_F1: //VK_F1:
			seleccion = 3;
			camera->SetTurnStep(90);
			camera->TurnDown();
			camera->SetPosition(-70, 900, 130);
			camera->SetTurnStep(0.0f);
			break;
		case GLFW_KEY_F5: //VK_F1:
			cam_pos_x = camera->GetPosition_X();
			cam_pos_y = camera->GetPosition_Y();
			cam_pos_z = camera->GetPosition_Z();
			cam_turn_step = camera->GetTurnStep();
			// cam_direction = camera->GetDirection();
			std::cout << cam_pos_x << " " << cam_pos_y << " " << cam_pos_z << std::endl;
			std::cout << cam_turn_step << std::endl;
			//std::cout << (camera->GetPosition()) << std::endl;
			break;
		case GLFW_KEY_F2: //VK_F2:
			seleccion = 1;
			break;
		case GLFW_KEY_F3: //VK_F3:
			seleccion = 2;
			break;
		case GLFW_KEY_F4: //VK_F3:
			seleccion = 3;
			camera->SetTurnStep(100);
			// camera->SetPosition(-70, 900, 130);
			//camera->SetPosition(camera->GetPosition());
			camera->SetTurnStep(1.0f);
			break;

		// AMBOS A LA VEZ PARA EL TEST DE LA CURVATURA
		case GLFW_KEY_C: //'C':
			//vel = 5;
			velocidad = 5;
			velocidad2 = 5;
			break;
	}

	
	// */

}

/*void CGModel::MouseAction(int button, int state, int x, int y)
{
}*/

void CGModel::MouseButton(int button, int action)
{
	//std::cout << button << "," << action << "\n";
}

//
//  FUNCIÓN: CGModel::mouse_move(double xpos, double ypos)
//
//  PROPÓSITO: Respuesta del modelo a un movimiento del ratón.
//
void CGModel::MouseMove(double xpos, double ypos)
{
	//std::cout << xpos << "," << ypos << "\n";
}

void CGModel::CameraConstraints()
{
	glm::vec3 pos = camera->GetPosition();
	int constraint = 0;
	if (pos.y < 1.0f) { pos.y = 1.0f; constraint = 1; }
	if (pos.y > 500.0f) { pos.y = 750.0f; constraint = 1; }
	if (pos.x > 500.0f) { pos.x = 500.0f; constraint = 1; }
	if (pos.x < -500.0f) { pos.x = -500.0f; constraint = 1; }
	if (pos.z > 500.0f) { pos.z = 500.0f; constraint = 1; }
	if (pos.z < -500.0f) { pos.z = -500.0f; constraint = 1; }
	if (constraint == 1)
	{
		camera->SetPosition(pos.x, pos.y, pos.z);
		camera->SetMoveStep(0.0f);
	}
}



