#include "Object.h"

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
