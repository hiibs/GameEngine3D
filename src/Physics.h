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

private:
	std::vector<Mesh*> meshes;
	std::vector<BoxHull*> boxHulls;
};

