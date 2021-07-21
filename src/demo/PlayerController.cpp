#include "PlayerController.h"
#include "Input.h"
#include <glm/glm.hpp>

void PlayerController::update(float deltaTime) {

	float turnSpeed = 120.f;
	float moveSpeed = 5.f;

	// Turning
	if (Input::isPressed(RIGHT))
		owner->rotation += -glm::vec3(0.f, 0.f, turnSpeed * deltaTime);
	else if (Input::isPressed(LEFT))
		owner->rotation += glm::vec3(0.f, 0.f, turnSpeed * deltaTime);

	// Movement
	if (Input::isPressed(FORWARD))
		owner->position += owner->getForwardVector() * moveSpeed * deltaTime;
	else if (Input::isPressed(BACK))
		owner->position += -owner->getForwardVector() * moveSpeed * deltaTime;
	 
}
