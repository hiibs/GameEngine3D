#pragma once
#include "Texture.h"
#include <string>

class Material {
public:
	Material(std::string shaderFile, Texture* colorMapnormalMap = nullptr, Texture* normalMap = nullptr, Texture* roughnessMap = nullptr, Texture* metalnessMap = nullptr);

	Texture* colorMap;
	Texture* normalMap;
	Texture* roughnessMap;
	Texture* metalnessMap;

	std::string shaderFile;
};

