#include "Camera.h"
#include <glm/gtx/transform.hpp>

Camera::Camera(Scene* scene) :
	Object(scene),
	fov(80.f),
	nearClip(0.1f),
	farClip(1000.f)
{
	name = "Camera";
	projection = glm::perspectiveFov(glm::radians(fov), 1.f, 1.f, nearClip, farClip);
}

void Camera::setAspect(int width, int height) {
	projection = glm::perspectiveFov(glm::radians(fov), (float)width, (float)height, nearClip, farClip);
}

const glm::mat4 Camera::getProjection() const {
	return projection;
}
