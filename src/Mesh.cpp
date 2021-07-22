#include "Mesh.h"
#include "Scene.h"
#include "Engine.h"
#include "Physics.h"
#include <glad/glad.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/DefaultLogger.hpp>
#include <assimp/LogStream.hpp>

Mesh::Mesh(Scene* scene) :
	Object(scene),
	material(nullptr)
{
	name = "Mesh";

	Engine::getInstance()->getPhysics()->addMesh(this);
	Engine::getInstance()->getRenderer()->addMesh(this);
}

Mesh::~Mesh() {
	Engine::getInstance()->getPhysics()->removeMesh(this);
	Engine::getInstance()->getRenderer()->removeMesh(this);
}

void Mesh::loadMesh(std::string fileName) {
	std::string path = "assets/models/" + fileName;

	vertices.clear();
	indices.clear();

	//read file with Assimp
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

	//Check for errors
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
		printf("Error loading model file \"%s\": \"%s\" ", path.c_str(), importer.GetErrorString());
		return;
	}

	processNode(scene->mRootNode, scene);
	

	// Find model boundaries
	float minX = vertices[0].position.x;
	float minY = vertices[0].position.y;
	float minZ = vertices[0].position.z;
	float maxX = vertices[0].position.x;
	float maxY = vertices[0].position.y;
	float maxZ = vertices[0].position.z;

	for (const Vertex& v : vertices) {
		if (v.position.x < minX)
			minX = v.position.x;
		if (v.position.y < minY)
			minY = v.position.y;
		if (v.position.z < minZ)
			minZ = v.position.z;
		if (v.position.x > maxX)
			maxX = v.position.x;
		if (v.position.y > maxY)
			maxY = v.position.y;
		if (v.position.z > maxZ)
			maxZ = v.position.z;
	}

	localBounds[0] = glm::vec3(minX, minY, minZ);
	localBounds[1] = glm::vec3(maxX, maxY, maxZ);

	// create buffers/arrays
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);
	// load data into vertex buffers
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	// set the vertex attribute pointers
	// vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	// vertex texture coords
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
	// vertex normals
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

	glBindVertexArray(0);
}

void Mesh::processNode(aiNode* node, const aiScene* scene) {
	// process all the node's meshes (if any)
	for (int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

		for (int j = 0; j < mesh->mNumVertices; j++) {
			Vertex vertex;
			vertex.position = glm::vec3(mesh->mVertices[j].x, mesh->mVertices[j].y, mesh->mVertices[j].z);

			vertex.normal = glm::vec3(mesh->mNormals[j].x, mesh->mNormals[j].y, mesh->mNormals[j].z);

			if (mesh->HasTextureCoords(0))
				vertex.texCoords = glm::vec2(mesh->mTextureCoords[0][j].x, mesh->mTextureCoords[0][j].y);

			vertices.push_back(vertex);
		}

		for (int j = 0; j < mesh->mNumFaces; j++) {
			aiFace face = mesh->mFaces[j];

			for (unsigned int j = 0; j < face.mNumIndices; j++) {
				indices.push_back(face.mIndices[j]);
			}
		}
	}

	// then do the same for each of its children
	for (int i = 0; i < node->mNumChildren; i++) {
		processNode(node->mChildren[i], scene);
	}
}

const std::vector<Mesh::Vertex> Mesh::getVertices() const {
	return std::vector<Vertex>();
}

const std::vector<unsigned int> Mesh::getIndices() const {
	return indices;
}

const glm::vec3* Mesh::getBounds() {
	glm::vec3 boxMesh[] = {
		glm::vec3(localBounds[0].x, localBounds[0].y, localBounds[0].z),
		glm::vec3(localBounds[0].x, localBounds[0].y, localBounds[1].z),
		glm::vec3(localBounds[0].x, localBounds[1].y, localBounds[0].z),
		glm::vec3(localBounds[0].x, localBounds[1].y, localBounds[1].z),
		glm::vec3(localBounds[1].x, localBounds[0].y, localBounds[0].z),
		glm::vec3(localBounds[1].x, localBounds[0].y, localBounds[1].z),
		glm::vec3(localBounds[1].x, localBounds[1].y, localBounds[0].z),
		glm::vec3(localBounds[1].x, localBounds[1].y, localBounds[1].z),
	};

	glm::mat4 mm = getTransform();

	// Transform to world space
	for (int i = 0; i < 8; i++) {
		boxMesh[i] = mm * glm::vec4(boxMesh[i], 1.f);
	}

	
	float minX = boxMesh[0].x;
	float minY = boxMesh[0].y;
	float minZ = boxMesh[0].z;
	float maxX = boxMesh[0].x;
	float maxY = boxMesh[0].y;
	float maxZ = boxMesh[0].z;


	// Find boundaries
	for (int i = 0; i < 8; i++) {
		if (boxMesh[i].x < minX)
			minX = boxMesh[i].x;
		if (boxMesh[i].y < minY)
			minY = boxMesh[i].y;
		if (boxMesh[i].z < minZ)
			minZ = boxMesh[i].z;
		if (boxMesh[i].x > maxX)
			maxX = boxMesh[i].x;
		if (boxMesh[i].y > maxY)
			maxY = boxMesh[i].y;
		if (boxMesh[i].z > maxZ)
			maxZ = boxMesh[i].z;
	}

	glm::vec3 bounds[] = {
		glm::vec3(minX, minY, minZ),
		glm::vec3(maxX, maxY, maxZ)
	};

	return bounds;
}

const unsigned int Mesh::getVAO() const {
	return vao;
}
