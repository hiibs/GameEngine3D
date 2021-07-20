#include "Material.h"
#include <glad/glad.h>
#include <fstream>


Material::Material(std::string shaderFile, Texture* colorMap, Texture* normalMap, Texture* roughnessMap, Texture* metalnessMap) :
	shaderFile(shaderFile),
	colorMap(colorMap),
	normalMap(normalMap),
	roughnessMap(roughnessMap),
	metalnessMap(metalnessMap)
{
	compileShader();
}

void Material::compileShader() {
	std::string vertexSourceStr = parseTextFromFile("Vertex.glsl");
	std::string fragmentSourceStr = parseTextFromFile(shaderFile);

	const char* vertexSource = vertexSourceStr.c_str();
	const char* fragmentSource = fragmentSourceStr.c_str();

// Create and compile vertex shader
int vertexShader = glCreateShader(GL_VERTEX_SHADER);
glShaderSource(vertexShader, 1, &vertexSource, NULL);
glCompileShader(vertexShader);

// check for shader compile errors
int success;
char infoLog[512];
glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
if (!success) {
	// If failed, get error string using glGetShaderInfoLog-function.
	glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
	printf("ERROR: Shader compilation failed: \"%s\"\n", infoLog);
}

// Create and compile fragment shader
int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
glCompileShader(fragmentShader);
// check for shader compile errors
glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
if (!success) {
	// If failed, get error string using glGetShaderInfoLog-function.
	glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
	printf("ERROR: Shader compilation failed: \"%s\"\n", infoLog);
}

// link shaders
shaderProgram = glCreateProgram();
glAttachShader(shaderProgram, vertexShader);
glAttachShader(shaderProgram, fragmentShader);
glLinkProgram(shaderProgram);

// check for linking errors
glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
if (!success) {
	// If failed, get error string using glGetProgramInfoLog-function.
	glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
	printf("ERROR: Shader link failed: \"%s\"\n", infoLog);
}

// After linking, the shaders can be deleted.
glDeleteShader(vertexShader);
glDeleteShader(fragmentShader);
}

std::string Material::parseTextFromFile(std::string path) {
	std::ifstream t(path);
	std::string contents;

	if (t.is_open()) {
		std::string str((std::istreambuf_iterator<char>(t)),
			std::istreambuf_iterator<char>());

		contents = str;
	}
	else {
		printf("Could not load file %s\n", path.c_str());
	}
	

	t.close();

	return contents;
}


void Material::setUniform(const std::string& name, glm::vec3 vector) {
	GLint loc = glGetUniformLocation(shaderProgram, name.c_str());
	if (loc < 0) {
		printf("Uniform %s was not found\n", name.c_str());
		return; // Don't set the uniform value, if it not found
	}
	glUniform3f(loc, vector.x, vector.y, vector.z);
}

void Material::setUniform(const std::string& name, glm::vec4 quat) {
	GLint loc = glGetUniformLocation(shaderProgram, name.c_str());
	if (loc < 0) {
		printf("Uniform %s was not found\n", name.c_str());
		return; // Don't set the uniform value, if it not found
	}
	glUniform4f(loc, quat.x, quat.y, quat.z, quat.w);
	GLenum err = glGetError();
	if (err != GL_NO_ERROR) {
		glUniform3f(loc, quat.x, quat.y, quat.z); // Set as 3 component value in case of 4 component set failed.
	}
}

void Material::setUniform(const std::string& name, glm::mat4& m) {
	GLint loc = glGetUniformLocation(shaderProgram, name.c_str());
	if (loc < 0) {
		printf("Uniform %s was not found\n", name.c_str());
		return; // Don't set the uniform value, if it not found
	}
	glUniformMatrix4fv(loc, 1, GL_FALSE, &m[0][0]);
}

void Material::setUniform(const std::string& name, float value) {
	GLint loc = glGetUniformLocation(shaderProgram, name.c_str());
	if (loc < 0) {
		printf("Uniform %s was not found\n", name.c_str());
		return; // Don't set the uniform value, if it not found
	}
	glUniform1f(loc, value);
}

void Material::setUniform(const std::string& name, int value) {
	GLint loc = glGetUniformLocation(shaderProgram, name.c_str());
	if (loc < 0) {
		printf("Uniform %s was not found\n", name.c_str());
		return; // Don't set the uniform value, if it not found
	}
	glUniform1i(loc, value);
}

void Material::setPointLightsUniform(const std::vector<PointLight*>& lights) {
	for (int i = 0; i < std::min(10, (int)lights.size()); i++) {
		setUniform("pointLights[" + std::to_string(i) + "].position", lights[i]->position);
		setUniform("pointLights[" + std::to_string(i) + "].color", lights[i]->color);
		setUniform("pointLights[" + std::to_string(i) + "].intensity", lights[i]->intensity);
		setUniform("pointLights[" + std::to_string(i) + "].radius", lights[i]->radius);
	}
	setUniform("numPointLights", std::min(10, (int)lights.size()));
}
