#pragma once
#include "Object.h"
#include <glm.hpp>

class PointLight : public Object {
public:
	PointLight(
		Scene* scene,
		std::string name = "Point Light",
		glm::vec3 position = glm::vec3(0.f, 0.f, 0.f),
		glm::vec3 rotation = glm::vec3(0.f, 0.f, 0.f),
		glm::vec3 scale = glm::vec3(1.f, 1.f, 1.f),
		Object* parent = nullptr,
		float intensity = 1.f,
		glm::vec3 color = glm::vec3(1.f, 1.f, 1.f),
		float radius = 10.f
	);

	~PointLight();

	float intensity;
	glm::vec3 color;
	float radius;
};

