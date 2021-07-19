#include "Object.h"

Object::Object(std::string name, Vector3 position, Quaternion rotation, Object* parent) :
	position(position),
	rotation(rotation),
	parent(parent)
{
}
