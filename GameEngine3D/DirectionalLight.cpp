#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(std::string name, Vector3 position, Quaternion rotation, Vector3 scale, Object* parent, float intensity, Vector3 color) :
	Light(name, position, rotation, scale, parent, intensity, color)
{
}
