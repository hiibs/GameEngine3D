#include "CameraController.h"
#include "Input.h"
#include <glm/glm.hpp>

void CameraController::update(float deltaTime) {

	float turnSpeed = 120.f;
	float moveSpeed = 5.f;
	float sensitivity = 0.1f;

	if (getInput()->isPressed(RIGHT_CLICK)) {
		getInput()->disableCursor();


		// Movement
		if (getInput()->isPressed(FORWARD))
			owner->position += owner->getForwardVector() * moveSpeed * deltaTime;
		else if (getInput()->isPressed(BACK))
			owner->position += -owner->getForwardVector() * moveSpeed * deltaTime;
		if (getInput()->isPressed(RIGHT))
			owner->position += owner->getRightVector() * moveSpeed * deltaTime;
		else if (getInput()->isPressed(LEFT))
			owner->position += -owner->getRightVector() * moveSpeed * deltaTime;

		glm::vec2 mouseDelta = sensitivity * getInput()->getMouseDelta();
		owner->rotation.z += mouseDelta.x;
		owner->rotation.x += mouseDelta.y;
	}
	else {
		getInput()->enableCursor();
	}
}
