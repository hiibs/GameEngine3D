#include "Scene.h"

Scene::Scene() :
	ambientColor(glm::vec3(0.7f, 0.7f, 1.0f)),
	ambientIntensity(0.05f)
{
}

Scene::~Scene() {
	for (Object* obj : objects)
		delete obj;
}

void Scene::start() {
	
}

void Scene::update(float deltaTime) {
	for (Object* obj : objects)
		obj->update(deltaTime);
}

void Scene::postUpdate(float deltaTime) {
	for (Object* obj : objects)
		obj->postUpdate(deltaTime);
}

void Scene::addObject(Object* object) {
	// Ensure not adding same object twice
	for (Object* o : objects) {
		if (o == object)
			return;
	}

	objects.push_back(object);
	object->start();
}

void Scene::removeObject(Object* object) {
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i] == object) {
			delete object;
			objects.erase(objects.begin() + i);
			return;
		}
	}
}

void Scene::addPointLight(PointLight* object) {
	pointLights.push_back(object);
}

void Scene::removePointLight(PointLight* object) {
	for (int i = 0; i < pointLights.size(); i++) {
		if (pointLights[i] == object) {
			objects.erase(objects.begin() + i);
		}
	}
}

const std::vector<PointLight*> Scene::getPointLights() const {
	return pointLights;
}

void Scene::addDirLight(DirLight* object) {
	dirLights.push_back(object);
}

void Scene::removeDirLight(DirLight* object) {
	for (int i = 0; i < pointLights.size(); i++) {
		if (dirLights[i] == object) {
			objects.erase(objects.begin() + i);
		}
	}
}

const std::vector<DirLight*> Scene::getDirLights() const {
	return dirLights;
}
