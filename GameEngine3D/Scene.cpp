#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene() {
	for (Object* obj : objects)
		delete obj;
}
