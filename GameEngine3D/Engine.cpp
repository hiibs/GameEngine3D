#include "Engine.h"
#include <iostream>

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
	window = glfwCreateWindow(width, height, "OpenGL window", NULL, NULL);
	if (!window) {
		std::cout << "Failed  to create glfw window!";
		glfwTerminate();
	}

	// Set current context
	glfwMakeContextCurrent(window);
	// Load GL functions using glad
	gladLoadGL();

	// Specify the key callback as c++-lambda to glfw
	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		// Close window if escape is pressed by the user.
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}
	});


	// Enable depth buffering
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	// Backface culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
}

void Engine::loadScene(Scene* scene) {
	if (this->scene)
		delete this->scene;

	this->scene = scene;
}

void Engine::start() {
	// Get time using glfwGetTime-function, for delta time calculation.
	float prevTime = (float)glfwGetTime();

	while (!glfwWindowShouldClose(window)) {
		// Compute application frame time (delta time) and update application
		float curTime = (float)glfwGetTime();
		float deltaTime = curTime - prevTime;
		prevTime = curTime;

		update(deltaTime);
	}
}

void Engine::update(float deltaTime) {
	if (!scene) {
		printf("No active scene!\n");
		return;
	}

	// Poll other window events.
	glfwPollEvents();

	// Update event (Game logic)
	scene->update(deltaTime);

	
	// Query the size of the framebuffer (window content) from glfw.
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	// Setup the opengl wiewport (i.e specify area to draw)
	glViewport(0, 0, width, height);
	// Set color to be used when clearing the screen
	glClearColor(0.f, 0.f, 0.f, 1.0f);
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	// Post-Update event (drawing objects in scene) 
	scene->postUpdate(deltaTime);

	glfwSwapBuffers(window);
}
