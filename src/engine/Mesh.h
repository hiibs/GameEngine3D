#pragma once
#include "Object.h"
#include "Mesh.h"
#include "Material.h"
#include <assimp/scene.h>
#include <glm/glm.hpp>

class Mesh : public Object {
public:
	struct Vertex {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texCoords;
	};

	Mesh(Scene* scene);
	~Mesh();

	
	Material* material;

	void postUpdate(float deltaTime) override { draw(); }

	void loadMesh(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	void draw();

	void generateShadow();
	void configureShaderAndMatrices();
	void renderScene();

	const std::vector<Vertex> getVertices() const;
	const std::vector<unsigned int> getIndices() const;

	const glm::vec3* getBounds();

private:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	unsigned int ebo, vao, vbo;

	glm::vec3 localBounds[2];
};

