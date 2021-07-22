#include "Camera.h"
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>

Camera::Camera(Scene* scene) :
	Object(scene),
	fov(80.f),
	nearClip(0.1f),
	farClip(1000.f)
{
	name = "Camera";
	projection = glm::mat4();
}

void Camera::setAspect(int width, int height) {
	projection = glm::perspectiveFov(glm::radians(fov), (float)width, (float)height, nearClip, farClip) * glm::eulerAngleXYZ(-glm::half_pi<float>(), 0.f, 0.f);
}

const glm::mat4 Camera::getProjection() const {
	return projection;
}
