#pragma once
#include "Object.h"
#include "Material.h"

class Billboard : public Object {
public:
	Billboard(Scene* scene);
	~Billboard();

	Material* material;

	glm::mat4 getBillboardMatrix(glm::vec3 viewPos, glm::vec3 up) const;

	unsigned int getVao() const;

private:
	unsigned int vao, positionsVbo, texCoordsVbo;
};

