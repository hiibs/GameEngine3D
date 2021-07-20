#pragma once
#include "Texture.h"
#include <glm.hpp>
#include <string>

class Material {
public:
	Material(std::string shaderFile, Texture* colorMapnormalMap = nullptr, Texture* normalMap = nullptr, Texture* roughnessMap = nullptr, Texture* metalnessMap = nullptr);

	Texture* colorMap;
	Texture* normalMap;
	Texture* roughnessMap;
	Texture* metalnessMap;

	std::string shaderFile;

	void compileShader();

	void setUniform(const std::string& name, glm::vec3 vector);
	void setUniform(const std::string& name, glm::vec4 quat);
	void setUniform(const std::string& name, glm::mat4& m);
	void setUniform(const std::string& name, float value);
	void setUniform(const std::string& name, int value);

private:
	int shaderProgram;

	const char* parseTextFromFile(std::string path);
};

