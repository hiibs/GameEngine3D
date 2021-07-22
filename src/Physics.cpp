#include "Physics.h"

void Physics::update() {
	for (BoxHull* box : boxHulls) {

		glm::vec3 boxMin = -box->halfExtents * box->getScale() + box->getPosition();
		glm::vec3 boxMax = box->halfExtents * box->getScale() + box->getPosition();

		std::vector<glm::vec3> boxCorners = {
			box->getTransform() * glm::vec4(box->halfExtents.x, box->halfExtents.y, box->halfExtents.z, 1.f),
			box->getTransform() * glm::vec4(box->halfExtents.x, box->halfExtents.y, -box->halfExtents.z, 1.f),
			box->getTransform() * glm::vec4(box->halfExtents.x, -box->halfExtents.y, box->halfExtents.z, 1.f),
			box->getTransform() * glm::vec4(box->halfExtents.x, -box->halfExtents.y, -box->halfExtents.z, 1.f),
			box->getTransform() * glm::vec4(-box->halfExtents.x, box->halfExtents.y, box->halfExtents.z, 1.f),
			box->getTransform() * glm::vec4(-box->halfExtents.x, box->halfExtents.y, -box->halfExtents.z, 1.f),
			box->getTransform() * glm::vec4(-box->halfExtents.x, -box->halfExtents.y, box->halfExtents.z, 1.f),
			box->getTransform() * glm::vec4(-box->halfExtents.x, -box->halfExtents.y, -box->halfExtents.z, 1.f)
		};

		for (Mesh* mesh : meshes) {
			const glm::vec3* bounds = mesh->getBounds();
			
			glm::vec3 meshMin = bounds[0];
			glm::vec3 meshMax = bounds[1];

			// Do a quick AABB test
			if (boxMin.x < meshMax.x && boxMax.x > meshMin.x &&
				boxMin.y < meshMax.y && boxMax.y > meshMin.y &&
				boxMin.z < meshMax.z && boxMax.z > meshMin.z) {
				
				std::vector<glm::vec3> meshPoints;
				for (glm::vec3 vert : mesh->getVertices())
					meshPoints.push_back(mesh->getTransform() * glm::vec4(vert, 1.f));

				bool collisionFound = true;

				// Test each face of mesh
				for (int i = 0; i < mesh->getIndices().size(); i += 3) {
					glm::vec3 a = meshPoints[mesh->getIndices()[i]];
					glm::vec3 b = meshPoints[mesh->getIndices()[i+1]];
					glm::vec3 c = meshPoints[mesh->getIndices()[i+2]];

					// Get face normal
					glm::vec3 faceNormal = glm::cross(b-a, c-a);


					if (!testCollision(boxCorners, meshPoints, faceNormal))
						collisionFound = false;
				}
				
				if (!testCollision(meshPoints, boxCorners, glm::vec3(1.f, 0.f, 0.f)))
					collisionFound = false;
				if (!testCollision(meshPoints, boxCorners, glm::vec3(0.f, 1.f, 0.f)))
					collisionFound = false;
				if (!testCollision(meshPoints, boxCorners, glm::vec3(0.f, 0.f, 1.f)))
					collisionFound = false;

				if (collisionFound)
					printf("CollisionFound");
			}


				
				/*
				float xCorrection = (meshMax.x - boxMin.x) < -(meshMin.x - boxMax.x) ? (meshMax.x - boxMin.x) : (meshMin.x - boxMax.x);
				float yCorrection = (meshMax.y - boxMin.y) < -(meshMin.y - boxMax.y) ? (meshMax.y - boxMin.y) : (meshMin.y - boxMax.y);
				float zCorrection = (meshMax.z - boxMin.z) < -(meshMin.z - boxMax.z) ? (meshMax.z - boxMin.z) : (meshMin.z - boxMax.z);

				//printf("%f\n", zCorrection);

				if (abs(xCorrection) < abs(yCorrection) && abs(xCorrection) < abs(zCorrection)) {
					box->move(glm::vec3(xCorrection, 0.f, 0.f));
				}
				else if (abs(yCorrection) < abs(xCorrection) && abs(yCorrection) < abs(zCorrection)){
					box->move(glm::vec3(0.f, yCorrection, 0.f));
				}
				else {
					box->move(glm::vec3(0.f, 0.f, zCorrection));
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

bool Physics::testCollision(const std::vector<glm::vec3>& shapeA, const std::vector<glm::vec3>& shapeB, glm::vec3 normal) {

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

	if (aMin < bMax && aMax > bMin)
		return true;
	else
		return false;
}
