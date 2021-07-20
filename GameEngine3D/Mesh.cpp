#include "Mesh.h"
#include "Scene.h"
#include <glad/glad.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/DefaultLogger.hpp>
#include <assimp/LogStream.hpp>

Mesh::Mesh(Scene* scene, std::string name, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, Object* parent, std::string sourceFile, Material* material) :
	Object(scene, name, position, rotation, scale, parent),
	sourceFile(sourceFile),
	material(material)
{
	if (sourceFile != "")
		load();
}

void Mesh::load() {
	vertices.clear();
	indices.clear();

	//read file with Assimp
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(sourceFile, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

	//Check for errors
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
		printf("Error loading model file \"%s\": \"%s\" ", sourceFile.c_str(), importer.GetErrorString());
		return;
	}

	processNode(scene->mRootNode, scene);

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

void Mesh::draw() {
	if (!scene->activeCamera) {
		printf("Scene has no active camera!\n");
		return;
	}

	glUseProgram(material->shaderProgram);

	glm::mat4 mvp = scene->activeCamera->projection * glm::inverse(scene->activeCamera->getModelMatrix()) * getModelMatrix();
	glm::mat4 m = getModelMatrix();

	material->setUniform("MVP", mvp);
	material->setUniform("M", m);
	material->setUniform("viewPos", scene->activeCamera->position);
	material->setUniform("ambientColor", scene->ambientColor);
	material->setUniform("ambientIntensity", scene->ambientIntensity);

	material->setPointLightsUniform(scene->getPointLights());

	// Set the texture uniform, if texture exists
	if (material->colorMap->id > 0) {
		material->setUniform("colorMap", 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, material->colorMap->id);
	}

	// draw mesh
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	// always good practice to set everything back to defaults once configured.
	glActiveTexture(GL_TEXTURE0);
}
