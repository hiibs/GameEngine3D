#pragma once
#include "Mesh.h"
#include "BoxHull.h"
#include <glm/glm.hpp>
#include <vector>

class Physics {
public:
	void update();
	bool lineTrace(glm::vec3 start, glm::vec2 end);

	void addMesh(Mesh* object);
	void removeMesh(Mesh* object);

	void addBoxHull(BoxHull* object);
	void removeBoxHull(BoxHull* object);

	bool testVertexOverlap(glm::vec3 boxMin, glm::vec3 boxMax, const std::vector<glm::vec3>& points, glm::vec3& correction);
	bool testSatCollision(const std::vector<glm::vec3>& shapeA, const std::vector<glm::vec3>& shapeB, glm::vec3 normal, glm::vec3& correction);

private:
	std::vector<Mesh*> meshes;
	std::vector<BoxHull*> boxHulls;
};

