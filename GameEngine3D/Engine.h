#pragma once
#include "Scene.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Engine {
public:
	Engine(int width = 1280, int height = 720);

	void start();
	void loadScene(Scene* scene);

private:
	Scene* scene;
	GLFWwindow* window;
	
	void update(float deltaTime);
};

