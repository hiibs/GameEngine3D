#pragma once
#include <glm/gtx/transform.hpp>
#include <vector>
#include <string>

class Scene;

class Object {
public:
	Object(Scene* scene);

	~Object();

	std::string name;

	void start() {};
	virtual void update(float deltaTime) {};
	virtual void lateUpdate(float deltaTime) {};

	void setParent(const Object* parent);
	void clearParent();

	const glm::mat4 getModelMatrix() const;

	glm::vec3 getForwardVector() const;
	glm::vec3 getRightVector() const;

	glm::vec3 getPosition() const;
	glm::vec3 getRotation() const;
	glm::vec3 getScale() const;

	glm::vec3 getWorldPosition() const;

	glm::mat4 getRotationMatrix() const;

	virtual void setPosition(glm::vec3 position, bool updatePhysics = false);
	virtual void setRotation(glm::vec3 rotation);
	virtual void setScale(glm::vec3 scale);

	virtual void move(glm::vec3 delta, bool updatePhysics = false);
	void rotate(glm::vec3 delta);

protected:
	Scene* scene;

private:
	const Object* parent;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	//glm::mat4 transform;

	//void updateTransform();
};

