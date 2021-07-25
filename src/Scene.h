#pragma once
#include "PointLight.h"
#include "DirLight.h"
#include "Camera.h"
#include "Mesh.h"
#include <vector>


class Scene {
public:
	Scene();
	~Scene();

	glm::vec3 ambientColor;
	float ambientIntensity;
	

	void start();
	void update(float deltaTime);
	void lateUpdate(float deltaTime);

	void addObject(Object* object);
	void removeObject(Object* object);

	void addPointLight(PointLight* object);
	void removePointLight(PointLight* object);
	const std::vector<PointLight*> getPointLights() const;

	void addDirLight(DirLight* object);
	void removeDirLight(DirLight* object);
	const std::vector<DirLight*> getDirLights() const;

private:
	std::vector<Object*> objects;
	std::vector<PointLight*> pointLights;
	std::vector<DirLight*> dirLights;
};

