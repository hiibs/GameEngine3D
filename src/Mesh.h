#pragma once
#include "Object.h"
#include "Mesh.h"
#include "Material.h"
#include <assimp/scene.h>
#include <glm/glm.hpp>

class Mesh : public Object {
public:
	Mesh(Scene* scene);
	~Mesh();

	
	Material* material;

	bool enableCollision;
	bool fpModel;

	void loadMesh(std::string path);
	void processNode(aiNode* node, const aiScene* scene);

	const std::vector<glm::vec3>& getVertices() const;
	const std::vector<unsigned int>& getIndices() const;

	const glm::vec3* getBounds();

	const unsigned int getVAO() const;

private:
	//std::vector<Vertex> vertices;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texCoords;
	
	std::vector<glm::vec3> globalVertPositions;

	std::vector<unsigned int> indices;
	unsigned int ebo, vao, positionsVbo, normalsVbo, texCoordsVbo;

	glm::vec3 localBounds[2];
};

