#pragma once
#include <glm/gtx/transform.hpp>
#include <vector>
#include <string>

class Scene;
class Behaviour;

class Object {
public:
	Object(Scene* scene);

	~Object();

	std::string name;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	void start();
	void update(float deltaTime);
	virtual void postUpdate(float deltaTime) {};

	void addBehaviour(Behaviour* behaviour);
	void removeBehaviour(Behaviour* behaviour);

	void setParent(const Object* parent);
	void clearParent();

	glm::mat4 getModelMatrix() const;
	glm::vec3 getForwardVector() const;
	glm::vec3 getRightVector() const;

protected:
	Scene* scene;

private:
	const Object* parent;
	std::vector<Behaviour*> behaviours;
};

