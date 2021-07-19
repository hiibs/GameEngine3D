#pragma once
#include "Object.h"
#include <vector>

class Scene {
public:
	Scene();
	~Scene();

private:
	std::vector<Object*> objects;
};

