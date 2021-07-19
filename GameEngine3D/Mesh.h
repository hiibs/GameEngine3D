#pragma once
#include "Object.h"
#include "Mesh.h"
#include "Material.h"

class Mesh : public Object {
public:
	Mesh(
		std::string name = "Mesh",
		Vector3 position = Vector3(0.f, 0.f, 0.f),
		Quaternion rotation = Quaternion(),
		Vector3 scale = Vector3(1.f, 1.f, 1.f),
		Object* parent = nullptr,
		std::string sourceFile = NULL,
		Material* material = nullptr
	);

	std::string sourceFile;
	Material* material;
};

