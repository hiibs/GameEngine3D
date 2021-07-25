#include "Renderer.h"
#include "OverlayImage.h"
#include <glad/glad.h>

void Renderer::draw(){
	if (!camera) {
		printf("Renderer: No camera has been set\n");
		return;
	}

	glDisable(GL_BLEND);

	std::vector<const Mesh*> fpModels;
	for (const Mesh* mesh : meshes) {
		if (mesh->fpModel) {
			fpModels.push_back(mesh);
			continue;
		}

		drawMesh(mesh, camera->getProjection() * glm::inverse(camera->getModelMatrix()));
	}

	glClear(GL_DEPTH_BUFFER_BIT);
	for (const Mesh* mesh : fpModels) {
		drawMesh(mesh, camera->getFpModelProjection() * glm::inverse(camera->getModelMatrix()));
	}

	glEnable(GL_BLEND);
	glClear(GL_DEPTH_BUFFER_BIT);
	for (auto overlay : camera->getOverlays()) {
		drawOverlay(overlay);
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

void Renderer::drawMesh(const Mesh* mesh, glm::mat4 vp) {
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
	glBindVertexArray(mesh->getVao());
	glDrawElements(GL_TRIANGLES, mesh->getIndices().size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	// always good practice to set everything back to defaults once configured.
	glActiveTexture(GL_TEXTURE0);
}

void Renderer::drawOverlay(OverlayImage* overlay) {
	glUseProgram(overlay->material->shaderProgram);


	overlay->material->setUniform("MP", camera->getUiProjection() * overlay->getModelMatrix());

	// Set the texture uniform, if texture exists
	if (overlay->material->colorMap->id > 0) {
		overlay->material->setUniform("colorMap", 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, overlay->material->colorMap->id);
	}

	// draw overlay
	glBindVertexArray(overlay->getVao());
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);

}
