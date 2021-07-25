#pragma once
#include "Object.h"

class BoxHull : public Object {
public:
	BoxHull(Scene* scene);
	~BoxHull();

	virtual void update(float deltaTime) override;

	glm::vec3 halfExtents;
	
	glm::vec3 lastCorrection;
	//bool wasResolved;
	bool isGrounded;
	
	std::vector<glm::vec3> contactNormals;

	glm::vec3 velocity;
	glm::vec3 lastPosition;
};

