#pragma once
#include "Texture.h"
#include "PointLight.h"
#include "DirLight.h"
#include <glm/glm.hpp>
#include <string>
#include <vector>

class Material {
public:
	Material(std::string shaderName, Texture* colorMapnormalMap = nullptr, Texture* normalMap = nullptr, Texture* roughnessMap = nullptr, Texture* metalnessMap = nullptr);

	Texture* colorMap;
	Texture* normalMap;
	Texture* roughnessMap;
	Texture* metalnessMap;

	int shaderProgram;
	std::string shaderName;

	void compileShader();

	void setUniform(const std::string& name, glm::vec3 vector);
	void setUniform(const std::string& name, glm::vec4 quat);
	void setUniform(const std::string& name, const glm::mat4& m);
	void setUniform(const std::string& name, float value);
	void setUniform(const std::string& name, int value);
	void setPointLightsUniform(const std::vector<PointLight*>& lights);
	void setDirLightsUniform(const std::vector<DirLight*>& lights);

private:
	std::string parseTextFromFile(std::string path);
};

