#pragma once
#include "Scene.h"
#include "Input.h"
#include "Physics.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Engine {
public:
	Engine(int width = 1280, int height = 720);

	void start();
	void loadScene(Scene* scene);

	void onWindowSizeChanged(int width, int height);

	const Input* getInput() const;
	Physics* getPhysics() const;

private:
	Scene* scene;
	GLFWwindow* window;
	Input* input;
	Physics* physics;

	void update(float deltaTime);
};

