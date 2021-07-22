#pragma once
#include "Object.h"
#include <glm/glm.hpp>

class PointLight : public Object {
public:
	PointLight(Scene* scene);

	~PointLight();

	float intensity;
	glm::vec3 color;
	float radius;
};

