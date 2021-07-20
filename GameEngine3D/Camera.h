#pragma once
#include "Object.h"
#include <glm.hpp>

class Camera : public Object {
public:
	Camera(
		Scene* scene,
		std::string name = "Object",
		glm::vec3 position = glm::vec3(0.f, 0.f, 0.f),
		glm::vec3 rotation = glm::vec3(0.f, 0.f, 0.f),
		glm::vec3 scale = glm::vec3(1.f, 1.f, 1.f),
		Object* parent = nullptr,
		float fov = 90.f,
		float nearClip = 0.1f,
		float farClip = 100.f
	);

	glm::mat4 projection;
};

