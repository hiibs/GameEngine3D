#include "Physics.h"

void Physics::update(float deltaTime) {
	for (BoxHull* box : boxHulls) {
		box->wasResolved = false;
		box->isGrounded = false;

		glm::vec3 boxMin = -box->halfExtents * box->getScale() + box->getPosition();
		glm::vec3 boxMax = box->halfExtents * box->getScale() + box->getPosition();

		std::vector<glm::vec3> boxCorners = {
			box->getModelMatrix() * glm::vec4(box->halfExtents.x, box->halfExtents.y, box->halfExtents.z, 1.f),
			box->getModelMatrix() * glm::vec4(box->halfExtents.x, box->halfExtents.y, -box->halfExtents.z, 1.f),
			box->getModelMatrix() * glm::vec4(box->halfExtents.x, -box->halfExtents.y, box->halfExtents.z, 1.f),
			box->getModelMatrix() * glm::vec4(box->halfExtents.x, -box->halfExtents.y, -box->halfExtents.z, 1.f),
			box->getModelMatrix() * glm::vec4(-box->halfExtents.x, box->halfExtents.y, box->halfExtents.z, 1.f),
			box->getModelMatrix() * glm::vec4(-box->halfExtents.x, box->halfExtents.y, -box->halfExtents.z, 1.f),
			box->getModelMatrix() * glm::vec4(-box->halfExtents.x, -box->halfExtents.y, box->halfExtents.z, 1.f),
			box->getModelMatrix() * glm::vec4(-box->halfExtents.x, -box->halfExtents.y, -box->halfExtents.z, 1.f)
		};

		for (Mesh* mesh : meshes) {
			if (!mesh->enableCollision)
				continue;

			const glm::vec3* bounds = mesh->getBounds();
			
			glm::vec3 meshMin = bounds[0];
			glm::vec3 meshMax = bounds[1];

			// Do a AABB test
			if (boxMin.x < meshMax.x && boxMax.x > meshMin.x &&
				boxMin.y < meshMax.y && boxMax.y > meshMin.y &&
				boxMin.z < meshMax.z && boxMax.z > meshMin.z) {
				

				std::vector<glm::vec3> meshPoints;
				for (glm::vec3 vert : mesh->getVertices())
					meshPoints.push_back(mesh->getModelMatrix() * glm::vec4(vert, 1.f));
				
				//ool isCorner = false;
				glm::vec3 c(0.f);
				/*
				// Check for overlapping vertices
				if (testVertexOverlap(boxMin, boxMax, meshPoints, c)) {
					bool isCorner = true;
				}*/

				bool collisionFound = true;
				
				float floorNormalZ(-1.f);
				// Do SAT test
				glm::vec3 minCorrection(1000.f);
				
				for (int i = 0; i < mesh->getIndices().size(); i += 3) {
					glm::vec3 a = meshPoints[mesh->getIndices()[i]];
					glm::vec3 b = meshPoints[mesh->getIndices()[i+1]];
					glm::vec3 c = meshPoints[mesh->getIndices()[i+2]];

					// Get face normal
					glm::vec3 faceNormal = glm::normalize(glm::cross(c-a,b-a));

					// Test AABB against mesh on face normal axis
					if (testSatCollision(boxCorners, meshPoints, faceNormal, c)) {
						if (glm::length(c) < glm::length(minCorrection))
							minCorrection = c;
					}
					else
						collisionFound = false;
				}

				// Test mesh against AABB on x, y and z axis
				if (testSatCollision(boxCorners, meshPoints, glm::vec3(1.f, 0.f, 0.f), c)) {
					if (glm::length(c) < glm::length(minCorrection))
						minCorrection = c;
				}
				else
					collisionFound = false;

				if (testSatCollision(boxCorners, meshPoints, glm::vec3(0.f, 1.f, 0.f), c)) {
					if (glm::length(c) < glm::length(minCorrection))
						minCorrection = c;
				}
				else
					collisionFound = false;

				if (testSatCollision(boxCorners, meshPoints, glm::vec3(0.f, 0.f, 1.f), c)) {
					if (glm::length(c) < glm::length(minCorrection))
						minCorrection = c;
				}
				else
					collisionFound = false;

				box->lastCorrection = glm::vec3(0.f);
				if (collisionFound) {
					/*
					if (glm::length(minCorrection) > 5.f * deltaTime)
						box->wasResolved = true;*/

					box->move(minCorrection);
					box->lastCorrection = minCorrection;

					if (glm::normalize(minCorrection).z > 0.7f)
						box->isGrounded = true;
				}
			}
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
		if (object == b) {
			return;
		}
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

bool Physics::testVertexOverlap(glm::vec3 boxMin, glm::vec3 boxMax, const std::vector<glm::vec3>& points, glm::vec3& correction) {
	for (glm::vec3 point : points) {
		if (point.x < boxMax.x && point.x > boxMin.x &&
			point.y < boxMax.y && point.y > boxMin.y &&
			point.z < boxMax.z && point.z > boxMin.z) {

			return true;
		}
	}
	return false;
}

bool Physics::testSatCollision(const std::vector<glm::vec3>& shapeA, const std::vector<glm::vec3>& shapeB, glm::vec3 normal, glm::vec3& correction) {

	float aMin = glm::dot(shapeA[0], normal);
	float aMax = aMin;

	for (glm::vec3 point : shapeA) {
		float dot = glm::dot(point, normal);
		if (dot < aMin)
			aMin = dot;
		if (dot > aMax)
			aMax = dot;
	}

	float bMin = glm::dot(shapeB[0], normal);
	float bMax = bMin;

	for (glm::vec3 point : shapeB) {
		float dot = glm::dot(point, normal);
		if (dot < bMin)
			bMin = dot;
		if (dot > bMax)
			bMax = dot;
	}

	if (aMin < bMax && aMax > bMin) {
		float c = abs(bMax - aMin) < abs(bMin - aMax) ? bMax - aMin : bMin - aMax;
		correction = c * normal;
		return true;
	}
	else
		return false;
}
