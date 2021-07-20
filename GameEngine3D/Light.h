#pragma once
#include "Object.h"

class Light : public Object {
public:
	Light(
		std::string name = "Light", 
		Vector3 position = Vector3(0.f, 0.f, 0.f), 
		Vector3 rotation = Vector3(0.f, 0.f, 0.f),
		Vector3 scale = Vector3(1.f, 1.f, 1.f),
		Object* parent = nullptr,
		float intensity = 1.f,
		Vector3 color = Vector3(1.f, 1.f, 1.f)
	);

	float intensity;
	Vector3 color;
};

