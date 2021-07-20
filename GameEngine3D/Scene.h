#pragma once
#include "Object.h"
#include <vector>

class Scene {
public:
	Scene();
	~Scene();

	void start();
	void update(float deltaTime);
	void postUpdate(float deltaTime);

	void addObject(Object* object);
	void destroyObject(Object* object);

private:
	std::vector<Object*> objects;
};

