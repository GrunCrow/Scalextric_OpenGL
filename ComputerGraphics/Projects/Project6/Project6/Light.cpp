// #include "stdafx.h"
#include <glm/glm.hpp>
#include "Light.h"

Light::Light()
{
	Ldir = glm::vec3(0.0f, 0.0f, -1.0f);
	La = glm::vec3(1.0f, 1.0f, 1.0f);
	Ld = glm::vec3(1.0f, 1.0f, 1.0f);
	Ls = glm::vec3(0.0f, 0.0f, 0.0f);
}

void Light::SetLightDirection(glm::vec3 d)
{
	Ldir = d;
}

void Light::SetAmbientLight(glm::vec3 a)
{
	La = a;
}

void Light::SetDifusseLight(glm::vec3 d)
{
	Ld = d;
}

void Light::SetSpecularLight(glm::vec3 s)
{
	Ls = s;
}

void Light::SetUniforms(CGShaderProgram* program)
{
	program->SetUniformVec3("Light.Ldir", Ldir);
	program->SetUniformVec3("Light.La", La);
	program->SetUniformVec3("Light.Ld", Ld);
	program->SetUniformVec3("Light.Ls", Ls);
}