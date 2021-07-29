#pragma once
#include "BoxHull.h"
#include "Camera.h"
#include "Input.h"
#include "Mesh.h"

class Player : public BoxHull {
public:
	Player(Scene* scene);

	virtual void update(float deltaTime) override;
	virtual void setPosition(glm::vec3 position, bool updatePhysics = false) override;
	virtual void move(glm::vec3 delta, bool updatePhysics = false) override;

private:
	Camera* camera;
	Mesh* weapon;
	const Input* input;
	float time;
	bool shoot;
	glm::vec3 weaponPos;
	glm::vec3 cameraPos;

	glm::vec3 getInputDir() const;
	void mouseLook();
	void updateMovement(float deltaTime);
};

