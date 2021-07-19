#pragma once
#include "Vector3.h"
#include "Quaternion.h"

#include <vector>
#include <string>

class Object {
public:
	Object(std::string name = "Unnamed Object", Vector3 position = Vector3(), Quaternion rotation = Quaternion(), Object* parent = nullptr);

	std::string name;
	Vector3 position;
	Quaternion rotation;

private:
	Object* parent;
	std::vector<Object*> children;
};

