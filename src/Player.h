#pragma once
#include "BoxHull.h"
#include "Camera.h"
#include "Input.h"

class Player : public BoxHull {
public:
	Player(Scene* scene);

	virtual void update(float deltaTime) override;

	
	virtual void setPosition(glm::vec3 position) override;

private:
	Camera* camera;
	const Input* input;
	glm::vec3 velocity;
	glm::vec3 lastPosition;
	
	glm::vec3 getInputDir() const;
	void mouseLook();
};

