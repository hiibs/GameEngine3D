#pragma once
#include "Object.h"
#include "Camera.h"
#include <vector>

class Scene {
public:
	Scene();
	~Scene();

	void start();
	void update(float deltaTime);
	void postUpdate(float deltaTime);

	void addObject(Object* object);
	void removeObject(Object* object);

	Camera* activeCamera;

private:
	std::vector<Object*> objects;
};

