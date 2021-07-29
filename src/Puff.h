#pragma once
#include "Billboard.h"
class Puff : public Billboard {
public:
	Puff(Scene* scene);

	glm::vec3 direction;

	virtual void update(float deltaTime) override;

private:
	float lifetime, timer;
};

