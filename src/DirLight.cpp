#include "DirLight.h"
#include "Scene.h"

DirLight::DirLight(Scene* scene) :
	Object(scene),
	intensity(1.f),
	color(glm::vec3(1.f, 1.f, 1.f))
{
	name = "Directional Light";
	scene->addDirLight(this);
}

DirLight::~DirLight() {
	scene->removeDirLight(this);
}
