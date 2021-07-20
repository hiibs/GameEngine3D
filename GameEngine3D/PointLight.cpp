#include "PointLight.h"

PointLight::PointLight(Scene* scene, std::string name, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, Object* parent, float intensity, glm::vec3 color) :
	Object(scene, name, position, rotation, scale, parent),
	intensity(intensity),
	color(color)
{
}
