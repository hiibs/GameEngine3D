#include "Engine.h"
#include "Mesh.h"
#include "Player.h"
#include "Billboard.h"
#include <glm/glm.hpp>

int main() {
	Engine* engine = new Engine();
	Scene* world = new Scene();
	world->ambientColor = glm::vec3(0.6f, 0.8f, 1.f);
	world->ambientIntensity = 0.5f;

	Texture* floorTex = new Texture("Pavement.png");
	Material* floorMat = new Material("Diffuse", floorTex);

	Texture* wallTex = new Texture("Bricks.png");
	Material* wallMat = new Material("Diffuse", wallTex);
	
	Texture* redTex = new Texture("Red.png");
	Material* redMat = new Material("Diffuse", redTex);

	Mesh* floor = new Mesh(world);
	floor->loadMesh("Box.obj");
	floor->setPosition(glm::vec3(0.f, 0.f, -0.5f));
	floor->setScale(glm::vec3(40.f, 40.f, 1.f));
	floor->material = floorMat;

	Mesh* wall = new Mesh(world);
	wall->loadMesh("Box.obj");
	wall->setPosition(glm::vec3(0.f, 10.f, 2.f));
	wall->setScale(glm::vec3(10.f, 2.f, 4.f));
	wall->material = wallMat;
	wall->setRotation(glm::vec3(30.f, 30.f, 32.f));

	wall = new Mesh(world);
	wall->loadMesh("Box.obj");
	wall->setPosition(glm::vec3(-6.f, 6.f, 3.f));
	wall->setScale(glm::vec3(6.f, 1.5f, 6.f));
	wall->material = wallMat;
	wall->setRotation(glm::vec3(0.f, 0.f, 10.f));

	wall = new Mesh(world);
	wall->loadMesh("Box.obj");
	wall->setPosition(glm::vec3(3.f, 1.f, 0.25f));
	wall->setScale(glm::vec3(4.f, 3.f, 3.f));
	wall->material = wallMat;
	wall->setRotation(glm::vec3(0.f, 0.f, 30.f));

	wall = new Mesh(world);
	wall->loadMesh("Box.obj");
	wall->setPosition(glm::vec3(0.f, -5.f, 0.f));
	wall->setScale(glm::vec3(10.f, 2.f, 4.f));
	wall->material = wallMat;
	wall->setRotation(glm::vec3(70.f, 0.f, 15.f));
	
	Mesh* monke = new Mesh(world);
	monke->setPosition(glm::vec3(0.f, 5.f, 1.f));
	monke->loadMesh("Suzanne.obj");
	monke->material = redMat;
	monke->enableCollision = false;

	PointLight* light = new PointLight(world);
	light->setPosition(glm::vec3(0.f, 0.f, 2.f));
	light->color = glm::vec3(1.f, 0.8f, 0.5f);
	light->intensity = 1.5f;
	light->radius = 30.f;

	Billboard* b = new Billboard(world);
	b->material = floorMat;
	b->setPosition(glm::vec3(0.f, 1.f, 1.f));
	

	Player* player = new Player(world);
	player->setPosition(glm::vec3(0.f, 0.f, 2.f));

	/*
	DirLight* sun = new DirLight(world);
	sun->rotation = glm::vec3(-60.f, 0.f, -30.f);
	sun->intensity = 1.5f;
	sun->color = glm::vec3(0.7f, 0.95f, 1.f);*/

	engine->loadScene(world);
	engine->start();

	return 0;
}