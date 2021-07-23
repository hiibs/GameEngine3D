#pragma once
#include "BoxHull.h"
#include "Camera.h"
#include "Input.h"
#include "Mesh.h"

class Player : public BoxHull {
public:
	Player(Scene* scene);

	virtual void update(float deltaTime) override;


private:
	Camera* camera;
	Mesh* weapon;
	const Input* input;
	float time;
	glm::vec3 weaponPos;
	glm::vec3 cameraPos;

	glm::vec3 getInputDir() const;
	void mouseLook();
	void updateMovement(float deltaTime);
};

