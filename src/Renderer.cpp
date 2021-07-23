#include "Renderer.h"
#include <glad/glad.h>

void Renderer::drawMeshes(){
	if (!camera) {
		printf("Renderer: No camera has been set\n");
		return;
	}

	std::vector<const Mesh*> fpModels;
	for (const Mesh* mesh : meshes) {
		if (mesh->fpModel) {
			fpModels.push_back(mesh);
			continue;
		}

		draw(mesh, camera->getProjection() * glm::inverse(camera->getModelMatrix()));
	}

	// Draw first person models in front
	glClear(GL_DEPTH_BUFFER_BIT);

	for (const Mesh* mesh : fpModels) {
		draw(mesh, camera->getFpModelProjection() * glm::inverse(camera->getModelMatrix()));
	}
}

void Renderer::addMesh(const Mesh* mesh) {
	for (const Mesh* m : meshes) {
		if (m == mesh)
			return;
	}
	meshes.push_back(mesh);
}

void Renderer::removeMesh(const Mesh* mesh) {
	for (int i = 0; i < meshes.size(); i++) {
		if (meshes[i] = mesh) {
			delete mesh;
			meshes.erase(meshes.begin() + i);
		}
	}
}

void Renderer::draw(const Mesh* mesh, glm::mat4 vp) {
	glUseProgram(mesh->material->shaderProgram);

	glm::mat4 m = mesh->getModelMatrix();
	glm::mat4 mvp = vp * m;


	mesh->material->setUniform("MVP", mvp);
	mesh->material->setUniform("M", m);

	mesh->material->setUniform("ambientColor", scene->ambientColor);
	mesh->material->setUniform("ambientIntensity", scene->ambientIntensity);

	mesh->material->setPointLightsUniform(scene->getPointLights());
	mesh->material->setDirLightsUniform(scene->getDirLights());

	// Set the texture uniform, if texture exists
	if (mesh->material->colorMap->id > 0) {
		mesh->material->setUniform("colorMap", 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->material->colorMap->id);
	}

	// draw mesh
	glBindVertexArray(mesh->getVAO());
	glDrawElements(GL_TRIANGLES, mesh->getIndices().size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	// always good practice to set everything back to defaults once configured.
	glActiveTexture(GL_TEXTURE0);
}
