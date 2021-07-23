#pragma once
#include "Object.h"
#include <glm/glm.hpp>

class Camera : public Object {
public:
	Camera(Scene* scene);

	void setAspect(int width, int height);

	const glm::mat4 getProjection() const;
	const glm::mat4 getFpModelProjection();

private:
	glm::mat4 projection, fpModelProjection;
	float fov, nearClip, farClip, fpModelFov;
};

