#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene() {
	for (Object* obj : objects)
		delete obj;
}

void Scene::start() {
	for (Object* obj : objects)
		obj->start();
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
	objects.push_back(object);
}

void Scene::destroyObject(Object* object) {
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i] == object) {
			objects.erase(objects.begin() + i);
			delete object;
		}
	}
}
