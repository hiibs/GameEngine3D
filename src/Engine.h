#pragma once
#include "Scene.h"
#include "Input.h"
#include "Physics.h"
#include "Renderer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>


class Engine {
public:
	Engine(int width = 1280, int height = 720);
	~Engine();

	static Engine* getInstance() { return static_cast<Engine*>(glfwGetWindowUserPointer(glfwGetCurrentContext())); }

	void start();
	void loadScene(Scene* scene);

	void onWindowSizeChanged(int width, int height);

	const Input* getInput() const;
	Physics* getPhysics() const;
	Renderer* getRenderer() const;

private:
	Scene* scene;
	GLFWwindow* window;
	Input* input;
	Physics* physics;
	Renderer* renderer;

	void update(float deltaTime);
};

