#include "Camera.h"
#include <gtx/transform.hpp>

Camera::Camera(Scene* scene, std::string name, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, Object* parent, float fov, float nearClip, float farClip) :
	Object(scene, name, position, rotation, scale, parent) {
	projection = glm::perspectiveFov(glm::radians(fov), 1280.f, 720.f, nearClip, farClip);
}