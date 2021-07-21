#include "Mesh.h"
#include "Scene.h"
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

	glm::mat4 mvp = scene->activeCamera->getProjection() * glm::inverse(scene->activeCamera->getModelMatrix()) * getModelMatrix();
	glm::mat4 m = getModelMatrix();

	material->setUniform("MVP", mvp);
	material->setUniform("M", m);
	
	material->setUniform("ambientColor", scene->ambientColor);
	material->setUniform("ambientIntensity", scene->ambientIntensity);

	material->setPointLightsUniform(scene->getPointLights());
	material->setDirLightsUniform(scene->getDirLights());

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

void Mesh::generateShadow() {
	// First we'll create a framebuffer object for rendering the depth map
	unsigned int depthMapFBO;
	glGenFramebuffers(1, &depthMapFBO);


	// Next we create a 2D texture that we'll use as the framebuffer's depth buffer
	const unsigned int WIDTH = 1024, HEIGHT = 1024;
	unsigned int depthMap;
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, WIDTH, HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// With the generated depth texture we can attach it as the framebuffer's depth buffer
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// 1. first render to depth map
	glViewport(0, 0, WIDTH, HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glClear(GL_DEPTH_BUFFER_BIT);
	configureShaderAndMatrices();
	renderScene();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	/*
	// 2. then render scene as normal with shadow mapping (using depth map)
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	configureShaderAndMatrices();
	glBindTexture(GL_TEXTURE_2D, depthMap);
	renderScene();*/
}

void Mesh::configureShaderAndMatrices()
{
}

void Mesh::renderScene()
{
}
