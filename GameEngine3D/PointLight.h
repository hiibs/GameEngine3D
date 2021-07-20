#pragma once
#include "Light.h"

class PointLight : public Light {
public:
	PointLight(
		std::string name = "Point Light",
		Vector3 position = Vector3(0.f, 0.f, 0.f),
		Vector3 rotation = Vector3(0.f, 0.f, 0.f),
		Vector3 scale = Vector3(1.f, 1.f, 1.f),
		Object* parent = nullptr,
		float intensity = 1.f,
		Vector3 color = Vector3(1.f, 1.f, 1.f)
	);
};

