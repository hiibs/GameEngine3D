#include "PointLight.h"
#include "Scene.h"

PointLight::PointLight(Scene* scene) :
	Object(scene),
	intensity(1.f),
	color(glm::vec3(1.f)),
	radius(10.f)
{
	name = "Point Light";
	scene->addPointLight(this);
}

PointLight::~PointLight() {
	scene->removePointLight(this);
}
