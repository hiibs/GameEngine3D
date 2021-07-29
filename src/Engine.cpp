#include "Engine.h"
#include <iostream>
#include <Windows.h>

Engine::Engine(int width, int height) :
	scene(nullptr),
	window(nullptr)
{
	// Set c++-lambda as error call back function for glfw.
	glfwSetErrorCallback([](int error, const char* description) {
		fprintf(stderr, "Error %d: %s\n", error, description);
		});

	// Try to initialize glfw
	if (!glfwInit()) {
		std::cout << "Failed to initialize glfw!\n";
		return;
	}

	// Create window and check that creation was succesful.
	window = glfwCreateWindow(width, height, "Leka3D", NULL, NULL);
	if (!window) {
		std::cout << "Failed  to create glfw window!";
		glfwTerminate();
	}

	// Set current context
	glfwMakeContextCurrent(window);
	// Load GL functions using glad
	gladLoadGL();

	glfwSetWindowUserPointer(window, this);

	// Specify the key callback as c++-lambda to glfw
	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		// Close window if escape is pressed by the user.
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}
	});

	glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
		void* instance = glfwGetWindowUserPointer(window);
		static_cast<Engine*>(instance)->onWindowSizeChanged(width, height);
	});


	// Enable depth buffering
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	// Backface culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	glEnable(GL_POLYGON_SMOOTH);

	// Enable raw mouse input
	if (glfwRawMouseMotionSupported())
		glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

	input = new Input(window);
	physics = new Physics();
	renderer = new Renderer();
}

Engine::~Engine() {
	delete input;
	delete physics;
	delete renderer;
}

void Engine::loadScene(Scene* scene) {
	if (this->scene)
		delete this->scene;

	int w, h;
	glfwGetWindowSize(window, &w, &h);
	if (renderer->camera)
		renderer->camera->setAspect(w, h);

	this->scene = scene;
	renderer->scene = scene;
}

void Engine::onWindowSizeChanged(int width, int height) {
	glViewport(0, 0, width, height);
	if (renderer->camera)
		renderer->camera->setAspect(width, height);
}

const Input* Engine::getInput() const {
	return input;
}

Physics* Engine::getPhysics() const {
	return physics;
}

Renderer* Engine::getRenderer() const {
	return renderer;
}

void Engine::start() {
	// Get time using glfwGetTime-function, for delta time calculation.
	float prevTime = (float)glfwGetTime();
	float deltaTime = 0.f;

	while (!glfwWindowShouldClose(window)) {
		// Compute application frame time (delta time) and update application
		float curTime = (float)glfwGetTime();
		deltaTime += curTime - prevTime;
		prevTime = curTime;

		if (deltaTime >= 1.0 / 125.f) {
			update(deltaTime);
			deltaTime = 0.f;
		}
			
	}
}

void Engine::update(float deltaTime) {
	if (!scene) {
		printf("No active scene!\n");
		return;
	}

	// Poll other window events.
	glfwPollEvents();



	// Update input
	input->update();

	// Update game logic
	scene->update(deltaTime);
	
	
	// Update physics (3 steps per frame for consistency)
	int subSteps = 1;
	for (int i = 0; i < subSteps; i++) {
		physics->update(deltaTime / (float)subSteps);
		
	}

	
	
	//scene->lateUpdate(deltaTime);

	// Rendering
	glClearColor(0.4f, 0.65f, 0.8f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	renderer->draw();

	glfwSwapBuffers(window);
}
