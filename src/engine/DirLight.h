#pragma once
#include "Object.h"
#include <glm/glm.hpp>

class DirLight : public Object {
public:
	DirLight(Scene* scene);

	~DirLight();

	float intensity;
	glm::vec3 color;
};

