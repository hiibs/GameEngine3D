#pragma once
#include "Vector3.h"
#include "Quaternion.h"

#include <vector>
#include <string>

class Object {
public:
	Object(
		std::string name = "Object",
		Vector3 position = Vector3(0.f, 0.f, 0.f),
		Vector3 rotation = Vector3(0.f, 0.f, 0.f),
		Vector3 scale = Vector3(1.f, 1.f, 1.f), 
		Object* parent = nullptr
	);

	std::string name;
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;

	virtual void start() {};
	virtual void update(float deltaTime) {};
	virtual void postUpdate(float deltaTime) {};

	void setParent(Object* parent);
	void clearParent();

private:
	Object* parent;
};

