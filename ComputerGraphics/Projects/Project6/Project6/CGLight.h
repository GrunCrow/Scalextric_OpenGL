#ifndef CGLIGHT_H

#define CGLIGHT_H

#include <glm/glm.hpp>
#include "CGShaderProgram.h"

class CGLight {

private:
	glm::vec3 Ldir;	// CGLight direction
	glm::vec3 La;   // Ambient intensity
	glm::vec3 Ld;   // Difusse intensity
	glm::vec3 Ls;   // Specular intensity

public:
	CGLight();
	void SetLightDirection(glm::vec3 d);
	void SetAmbientLight(glm::vec3 a);
	void SetDifusseLight(glm::vec3 d);
	void SetSpecularLight(glm::vec3 s);
	void SetUniforms(CGShaderProgram* program);
};

#endif