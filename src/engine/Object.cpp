#include "Object.h"
#include "Scene.h"
#include "Behaviour.h"
#include <glm/gtx/euler_angles.hpp>

Object::Object(Scene* scene) :
	scene(scene),
	name("Object"),
	position(glm::vec3(0.f)),
	rotation(glm::vec3(0.f)),
	scale(glm::vec3(1.f)),
	parent(nullptr)
{
	// Objects cannot exist outside a scene
	if (!this->scene) {
		delete this;
		return;
	}

	this->scene->addObject(this);
}

Object::~Object() {
	for (Behaviour* b : behaviours)
		delete b;

	scene->removeObject(this);
}

void Object::start() {
	for (Behaviour* b : behaviours)
		b->start();
}

void Object::update(float deltaTime) {
	for (Behaviour* b : behaviours)
		b->update(deltaTime);
}

void Object::addBehaviour(Behaviour* behaviour) {
	// Ensure we aren't adding the same behaviour twice
	for (Behaviour* b : behaviours) {
		if (b == behaviour)
			return;
	}

	behaviours.push_back(behaviour);
}

void Object::removeBehaviour(Behaviour* behaviour) {
	for (int i = 0; i < behaviours.size(); i++) {
		if (behaviour == behaviours[i]) {
			delete behaviour;
			behaviours.erase(behaviours.begin() + i);
			return;
		}
	}
}

void Object::setParent(const Object* p) {
	if (p->scene == scene)
		this->parent = p;
}

void Object::clearParent(){
	parent = nullptr;
}

glm::mat4 Object::getModelMatrix() const {
	glm::mat4 mm = glm::translate(glm::mat4(1.f), position)
		* glm::eulerAngleZYX(glm::radians(rotation.z), glm::radians(rotation.y), glm::radians(rotation.x))
		* glm::scale(glm::mat4(1.0f), scale);

	return parent ? parent->getModelMatrix() * mm : mm;
}

glm::vec3 Object::getForwardVector() const {
	return glm::eulerAngleZYX(glm::radians(rotation.z), glm::radians(rotation.y), glm::radians(rotation.x)) * glm::vec4(0.f, 1.f, 0.f, 1.f);
}

glm::vec3 Object::getRightVector() const {
	return glm::eulerAngleZYX(glm::radians(rotation.z), glm::radians(rotation.y), glm::radians(rotation.x)) * glm::vec4(1.f, 0.f, 0.f, 1.f);
}
