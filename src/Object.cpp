#include "Object.h"
#include "Scene.h"
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
	scene->removeObject(this);
}

void Object::setParent(const Object* p) {
	if (p->scene == scene)
		this->parent = p;
}

void Object::clearParent(){
	parent = nullptr;
}

const glm::mat4 Object::getModelMatrix() const {
	glm::mat4 t = glm::translate(glm::mat4(1.f), position)
		* glm::eulerAngleZYX(glm::radians(rotation.z), glm::radians(rotation.y), glm::radians(rotation.x))
		* glm::scale(glm::mat4(1.0f), scale);

	return parent ? parent->getModelMatrix() * t : t;
}

glm::vec3 Object::getForwardVector() const {
	glm::vec4 v = getRotationMatrix() * glm::vec4(0.f, 1.f, 0.f, 1.f);
	return parent ? parent->getRotationMatrix() * v : v;
}

glm::vec3 Object::getRightVector() const {
	glm::vec4 v = getRotationMatrix() * glm::vec4(1.f, 0.f, 0.f, 1.f);
	return parent ? parent->getRotationMatrix() * v : v;
}

glm::vec3 Object::getPosition() const {
	return position;
}

glm::vec3 Object::getRotation() const {
	return rotation;
}

glm::vec3 Object::getScale() const {
	return scale;
}

glm::mat4 Object::getRotationMatrix() const {
	return glm::eulerAngleZYX(glm::radians(rotation.z), glm::radians(rotation.y), glm::radians(rotation.x));
}

void Object::setPosition(glm::vec3 position) {
	this->position = position;
}

void Object::setRotation(glm::vec3 rotation) {
	this->rotation = rotation;
}

void Object::setScale(glm::vec3 scale) {
	this->scale = scale;
}

void Object::move(glm::vec3 delta) {
	position += delta;
}

void Object::rotate(glm::vec3 delta) {
	rotation += delta;
}

/*
void Object::updateTransform() {
	glm::mat4 t = glm::translate(glm::mat4(1.f), position)
		* glm::eulerAngleZYX(glm::radians(rotation.z), glm::radians(rotation.y), glm::radians(rotation.x))
		* glm::scale(glm::mat4(1.0f), scale);

	transform = parent ? parent->getTransform() * t : t;
}*/
