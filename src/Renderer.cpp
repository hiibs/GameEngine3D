#include "Renderer.h"
#include "OverlayImage.h"
#include <glad/glad.h>
#include <glm/gtx/euler_angles.hpp>

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


	

	glEnable(GL_BLEND);

	glm::vec3 camPos = camera->getWorldPosition();
	std::sort(billboards.begin(), billboards.end(), [camPos](const Billboard* a, const Billboard* b) -> bool {
		return glm::length(a->getWorldPosition() - camPos) > glm::length(b->getWorldPosition() - camPos);
	});

	for (auto billboard : billboards) {
		drawBillboard(billboard, camera->getProjection() * glm::inverse(camera->getModelMatrix()));
	}


	glDisable(GL_BLEND);
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
			return;
		}
	}
}

void Renderer::addBillboard(const Billboard* billboard) {
	for (auto b : billboards) {
		if (b == billboard)
			return;
	}
	billboards.push_back(billboard);
}

void Renderer::removeBillboard(const Billboard* billboard) {
	int count = billboards.size();
	for (int i = 0; i < count; i++) {
		if (billboards[i] == billboard) {
			billboards.erase(billboards.begin() + i);
			return;
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

	mesh->material->setUniform("tint", mesh->material->tint);

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

void Renderer::drawBillboard(const Billboard* billboard, glm::mat4 vp) {
	glUseProgram(billboard->material->shaderProgram);
	glm::mat4 m = billboard->getBillboardMatrix(camera->getWorldPosition(), glm::vec3(0.f, 0.f, 1.f));
	//lm::mat4 m = glm::translate(billboard->getWorldPosition());//
	glm::mat4 mvp = vp * m;


	billboard->material->setUniform("MVP", mvp);
	billboard->material->setUniform("M", m);

	billboard->material->setUniform("tint", billboard->material->tint);

	billboard->material->setUniform("ambientColor", scene->ambientColor);
	billboard->material->setUniform("ambientIntensity", scene->ambientIntensity);
	billboard->material->setPointLightsUniform(scene->getPointLights());
	billboard->material->setDirLightsUniform(scene->getDirLights());

	// Set the texture uniform, if texture exists
	if (billboard->material->colorMap->id > 0) {
		billboard->material->setUniform("colorMap", 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, billboard->material->colorMap->id);
	}

	// draw billboard
	glBindVertexArray(billboard->getVao());
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);

	// always good practice to set everything back to defaults once configured.
	glActiveTexture(GL_TEXTURE0);
}

void Renderer::drawOverlay(OverlayImage* overlay) {
	glUseProgram(overlay->material->shaderProgram);


	overlay->material->setUniform("MP", camera->getUiProjection() * overlay->getModelMatrix());
	overlay->material->setUniform("tint", overlay->material->tint);

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
