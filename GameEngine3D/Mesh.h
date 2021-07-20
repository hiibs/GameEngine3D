#pragma once
#include "Object.h"
#include "Mesh.h"
#include "Material.h"
#include <assimp/scene.h>
#include <glm.hpp>

class Mesh : public Object {
public:
	Mesh(
		std::string name = "Mesh",
		Vector3 position = Vector3(0.f, 0.f, 0.f),
		Vector3 rotation = Vector3(0.f, 0.f, 0.f),
		Vector3 scale = Vector3(1.f, 1.f, 1.f),
		Object* parent = nullptr,
		std::string sourceFile = "",
		Material* material = nullptr
	);

	std::string sourceFile;
	Material* material;

	void postUpdate(float deltaTime) override { draw(); }

	void load();
	void processNode(aiNode* node, const aiScene* scene);
	void draw();

	struct Vertex {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texCoords;
	};

private:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	unsigned int ebo, vao, vbo;
};

