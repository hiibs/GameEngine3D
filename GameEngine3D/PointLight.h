#pragma once
#include "Light.h"

class PointLight : public Light {
public:
	PointLight(
		std::string name = "Light",
		Vector3 position = Vector3(),
		Quaternion rotation = Quaternion(),
		Vector3 scale = Vector3(1.f, 1.f, 1.f),
		Object* parent = nullptr,
		float intensity = 1.f,
		Vector3 color = Vector3(1.f, 1.f, 1.f)
	);
};

