#pragma once
#include "PointLight.h"
#include "Camera.h"
#include <vector>

class Scene {
public:
	Scene();
	~Scene();

	glm::vec3 ambientColor;
	float ambientIntensity;
	Camera* activeCamera;

	void start();
	void update(float deltaTime);
	void postUpdate(float deltaTime);

	void addObject(Object* object);
	void removeObject(Object* object);

	void addPointLight(PointLight* object);
	void removePointLight(PointLight* object);

	const std::vector<PointLight*> getPointLights() const;

private:
	std::vector<Object*> objects;
	std::vector<PointLight*> pointLights;
};

