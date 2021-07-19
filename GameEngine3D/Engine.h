#pragma once
#include "Scene.h"

class Engine {
public:
	Engine(int width = 1280, int height = 720);

	void loadScene(Scene* scene);

private:
	Scene* scene;

	void initialize();
	void update(float deltaTime);
};

