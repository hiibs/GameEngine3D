#pragma once
#include "Material.h"
#include "Camera.h"

class OverlayImage {
public:
	OverlayImage(Camera* camera);
	~OverlayImage();

	glm::vec2 anchorPoint;
	glm::vec2 size;
	glm::vec2 offset;
	Material* material;

	const glm::mat4 getModelMatrix() const;
	unsigned int getVao() const;

private:
	unsigned int vao, positionsVbo, texCoordsVbo;
	Camera* camera;
};

