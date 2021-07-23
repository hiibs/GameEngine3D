#pragma once
#include "Object.h"

class BoxHull : public Object {
public:
	BoxHull(Scene* scene);
	~BoxHull();

	virtual void setPosition(glm::vec3 position) override;
	virtual void update(float deltaTime) override;

	glm::vec3 halfExtents;
	glm::vec3 velocity;
	glm::vec3 lastCorrection;
	bool wasResolved;
	bool isGrounded;
	glm::vec3 lastPosition;
};

