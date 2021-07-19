#include "Light.h"

Light::Light(std::string name, Vector3 position, Quaternion rotation, Vector3 scale, Object* parent, float intensity, Vector3 color) :
	Object(name, position, rotation, scale, parent),
	intensity(intensity),
	color(color)
{
}
