#include "Object.h"

Object::Object(std::string name, Vector3 position, Vector3 rotation, Vector3 scale, Object* parent) :
	position(position),
	rotation(rotation),
	scale(scale),
	parent(parent)
{
}

void Object::setParent(Object* parent)
{
}

void Object::clearParent()
{
}
