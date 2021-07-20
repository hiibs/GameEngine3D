#include "Engine.h"
#include "Mesh.h"

int main() {
	Engine* engine = new Engine();
	Scene* world = new Scene();

	Texture* playerTex = new Texture("../Assets/Checkerboard.png");
	Material* playerMat = new Material("Diffuse.glsl", playerTex);

	Mesh* playerMesh = new Mesh(
		world, 
		"Player Mesh", 
		glm::vec3(0.f, 0.f, 0.0f), 
		glm::vec3(0.f, 0.f, 0.f), 
		glm::vec3(1.f, 1.f, 1.f), 
		nullptr, 
		"../Assets/Box.obj", 
		playerMat
	);

	Camera* camera = new Camera(
		world,
		"Camera",
		glm::vec3(0.f, 1.f, 1.f),
		glm::vec3(-30.f, 0.f, 0.f),
		glm::vec3(1.f, 1.f, 1.f),
		nullptr,
		90.f,
		0.1f,
		100.f
	);

	PointLight* light = new PointLight(world);
	light->position = glm::vec3(0.f, 1.f, 0.f);
	light->color = glm::vec3(1.f, 0.8f, 0.5f);
	light->intensity = 10.f;
	light->radius = 5.f;

	world->activeCamera = camera;

	engine->loadScene(world);
	engine->start();

	return 0;
}