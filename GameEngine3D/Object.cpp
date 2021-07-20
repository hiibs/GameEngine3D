#include "Object.h"
#include "Scene.h"

Object::Object(Scene* scene, std::string name, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, Object* parent) :
	scene(scene),
	position(position),
	rotation(rotation),
	scale(scale),
	parent(parent)
{
	this->scene->addObject(this);
}

Object::~Object() {
	scene->removeObject(this);
}

void Object::setParent(Object* parent)
{
}

void Object::clearParent()
{
}

glm::mat4 Object::getModelMatrix() const {
	return
		glm::translate(glm::mat4(1.f), position)
		* glm::rotate(glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f))
		* glm::rotate(glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f))
		* glm::rotate(glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f))
		* glm::scale(glm::mat4(1.0f), scale);
}
