#pragma once
#include "Object.h"

class BoxHull : public Object {
public:
	BoxHull(Scene* scene);
	~BoxHull();

	glm::vec3 halfExtents;
	bool wasResolved;
	bool isGrounded;
};

