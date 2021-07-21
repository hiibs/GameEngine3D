#include "Engine.h"
#include "Mesh.h"
#include "CameraController.h"
#include <glm/glm.hpp>

int main() {
	Engine* engine = new Engine();
	Scene* world = new Scene();

	Texture* floorTex = new Texture("Checkerboard.png");
	Material* floorMat = new Material(floorTex);

	Mesh* floor = new Mesh(world);
	floor->loadMesh("Box.obj");
	floor->position = glm::vec3(0.f, 0.f, -0.5f);
	floor->scale = glm::vec3(40.f, 40.f, 1.f);
	floor->material = floorMat;

	Mesh* wall = new Mesh(world);
	wall->loadMesh("Box.obj");
	wall->position = glm::vec3(0.f, 10.f, 1.5f);
	wall->scale = glm::vec3(10.f, 1.f, 3.f);
	wall->material = floorMat;

	BoxHull* cameraParent = new BoxHull(world);
	CameraController* controller = new CameraController(cameraParent);

	Camera* camera = new Camera(world);
	camera->setParent(cameraParent);
	camera->position = glm::vec3(0.f, 0.f, 1.6f);
	camera->rotation = glm::vec3(90.f, 00.f, 0.f);
	
	PointLight* light = new PointLight(world);
	light->position = glm::vec3(0.f, 0.f, 2.f);
	light->color = glm::vec3(1.f, 0.8f, 0.5f);
	light->intensity = 1.f;
	light->radius = 20.f;

	light = new PointLight(world);
	light->position = glm::vec3(0.f, 15.f, 2.f);
	light->color = glm::vec3(1.f, 0.8f, 0.5f);
	light->intensity = 1.f;
	light->radius = 20.f;
	/*
	DirLight* sun = new DirLight(world);
	sun->rotation = glm::vec3(-60.f, 0.f, -30.f);
	sun->intensity = 1.5f;
	sun->color = glm::vec3(0.7f, 0.95f, 1.f);*/

	

	world->activeCamera = camera;

	engine->loadScene(world);
	engine->start();

	return 0;
}