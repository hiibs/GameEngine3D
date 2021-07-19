#pragma once
#include "Light.h"

class DirectionalLight : public Light {
public:
	DirectionalLight(
		std::string name = "Light",
		Vector3 position = Vector3(),
		Quaternion rotation = Quaternion(),
		Vector3 scale = Vector3(1.f, 1.f, 1.f),
		Object* parent = nullptr,
		float intensity = 1.f,
		Vector3 color = Vector3(1.f, 1.f, 1.f)
	);
};

