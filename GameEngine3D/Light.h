#pragma once
#include "Object.h"

class Light : public Object {
public:
	Light(
		std::string name = "Light", 
		Vector3 position = Vector3(), 
		Quaternion rotation = Quaternion(), 
		Vector3 scale = Vector3(1.f, 1.f, 1.f),
		Object* parent = nullptr,
		float intensity = 1.f,
		Vector3 color = Vector3(1.f, 1.f, 1.f)
	);

	float intensity;
	Vector3 color;
};

