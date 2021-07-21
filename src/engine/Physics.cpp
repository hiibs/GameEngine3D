#include "Physics.h"

void Physics::update() {
	
	for (BoxHull* box : boxHulls) {
		for (Mesh* mesh : meshes) {


			glm::vec3 boxMin = box->getModelMatrix() * glm::vec4(-box->halfExtents, 1.f);
			glm::vec3 boxMax = box->getModelMatrix() * glm::vec4(box->halfExtents, 1.f);
			glm::vec3 meshMin = mesh->getModelMatrix() * glm::vec4(mesh->getBoundariesMin(), 1.f);
			glm::vec3 meshMax = mesh->getModelMatrix() * glm::vec4(mesh->getBoundariesMax(), 1.f);


			if (boxMin.x < meshMax.x && boxMax.x > meshMin.x &&
				boxMin.y < meshMax.y && boxMax.y > meshMin.y &&
				boxMin.z < meshMax.z && boxMax.z > meshMin.z) {
				
				float xCorrection = (meshMax.x - boxMin.x) < -(meshMin.x - boxMax.x) ? (meshMax.x - boxMin.x) : (meshMin.x - boxMax.x);
				float yCorrection = (meshMax.y - boxMin.y) < -(meshMin.y - boxMax.y) ? (meshMax.y - boxMin.y) : (meshMin.y - boxMax.y);
				float zCorrection = (meshMax.z - boxMin.z) < -(meshMin.z - boxMax.z) ? (meshMax.z - boxMin.z) : (meshMin.z - boxMax.z);

				printf("Collision detected!\n");

				if (abs(xCorrection) < abs(yCorrection) && abs(xCorrection) < abs(zCorrection)) {
					box->position.x += xCorrection;
				}
				else if (abs(yCorrection) < abs(xCorrection) && abs(yCorrection) < abs(zCorrection)){
					box->position.y += yCorrection;
				}
				else {
					box->position.z += zCorrection;
				}
			}

			/*
			for (int i = 0; i < mesh->getIndices().size(); i += 3) {
				//Check sphere intersection for each face
				glm::vec3 face[] = {
					glm::vec3(mesh->getVertices()[mesh->getIndices()[i]].position),
					glm::vec3(mesh->getVertices()[mesh->getIndices()[i + 1]].position),
					glm::vec3(mesh->getVertices()[mesh->getIndices()[i + 2]].position)
				};
			}*/
		}
	}
}

bool Physics::lineTrace(glm::vec3 start, glm::vec2 end) {
	return false;
}

void Physics::addMesh(Mesh* object) {
	for (Mesh* m : meshes) {
		if (object == m)
			return;
	}

	meshes.push_back(object);
}

void Physics::removeMesh(Mesh* object) {
	for (int i = 0; i < meshes.size(); i++) {
		if (object == meshes[i]) {
			delete object;
			meshes.erase(meshes.begin() + i);
		}
	}
}

void Physics::addBoxHull(BoxHull* object) {
	for (BoxHull* b : boxHulls) {
		if (object == b)
			return;
	}

	boxHulls.push_back(object);
}

void Physics::removeBoxHull(BoxHull* object) {
	for (int i = 0; i < boxHulls.size(); i++) {
		if (object == boxHulls[i]) {
			delete object;
			boxHulls.erase(boxHulls.begin() + i);
		}
	}
}
