#pragma once
#include <gtx/transform.hpp>
#include <vector>
#include <string>

class Scene;

class Object {
public:
	Object(
		Scene* scene,
		std::string name = "Object",
		glm::vec3 position = glm::vec3(0.f, 0.f, 0.f),
		glm::vec3 rotation = glm::vec3(0.f, 0.f, 0.f),
		glm::vec3 scale = glm::vec3(1.f, 1.f, 1.f),
		Object* parent = nullptr
	);

	~Object();

	std::string name;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	virtual void start() {};
	virtual void update(float deltaTime) {};
	virtual void postUpdate(float deltaTime) {};

	void setParent(Object* parent);
	void clearParent();

	glm::mat4 getModelMatrix() const;

protected:
	Object* parent;
	Scene* scene;
};

