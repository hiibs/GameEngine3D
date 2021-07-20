#include "PointLight.h"

PointLight::PointLight(std::string name, Vector3 position, Vector3 rotation, Vector3 scale, Object* parent, float intensity, Vector3 color) :
	Light(name, position, rotation, scale, parent, intensity, color)
{
}
