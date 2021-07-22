#include "Player.h"
#include "Scene.h"
#include "Engine.h"
#include <glm/gtx/euler_angles.hpp>

Player::Player(Scene* scene) : BoxHull(scene),
	velocity(glm::vec3(0.f))
{
	// Set player size
	halfExtents = glm::vec3(0.4f, 0.4f, 0.9f);

	// Create player camera
	camera = new Camera(scene);
	camera->setParent(this);
	camera->setRotation(glm::vec3(0.f, 0.f, 0.f));
	camera->setPosition(glm::vec3(0.f, 0.f, 0.7f));
	Engine::getInstance()->getRenderer()->camera = camera;

	// Get input
	input = Engine::getInstance()->getInput();
	input->disableCursor();
}

void Player::update(float deltaTime) {
	// Update velocity
	velocity = (getPosition() - lastPosition) / deltaTime;

	lastPosition = getPosition();


	float acceleration = 60.f;
	float friction = 8.f;



	mouseLook();

	if (isGrounded) {
		velocity += getInputDir() * acceleration * deltaTime;
		velocity *= glm::clamp(1.f - friction * deltaTime, 0.f, 1.f);

		if (input->isPressed(JUMP))
			velocity.z = 5.f;
	}
	else {
		velocity.z -= 14.f * deltaTime;

		glm::vec3 oldVel = velocity;


		float oldSpeed = glm::length(glm::vec3(velocity.x, velocity.y, 0.f));
		
		velocity += getInputDir() * acceleration * 0.3f * deltaTime;

		glm::vec3 hVel = glm::vec3(velocity.x, velocity.y, 0.f);
		if (glm::length(glm::vec3(hVel)) > oldSpeed) {
			glm::vec3 newHVel = glm::normalize(hVel) * oldSpeed;
			velocity.x = newHVel.x;
			velocity.y = newHVel.y;
		}
	}
		
	
	
	move(velocity * deltaTime);
}

void Player::setPosition(glm::vec3 position) {
	Object::setPosition(position);
	lastPosition = position;
}

glm::vec3 Player::getInputDir() const {
	glm::vec3 dir = glm::vec3(0.f);

	if (input->isPressed(FORWARD))
		dir += getForwardVector();
	if (input->isPressed(BACK))
		dir += -getForwardVector();
	if (input->isPressed(RIGHT))
		dir += getRightVector();
	if (input->isPressed(LEFT))
		dir += -getRightVector();

	return glm::length(dir) > 0.1f ? glm::normalize(dir) : glm::vec3(0.f);
}

void Player::mouseLook() {
	glm::vec2 mouseDelta = input->getMouseDelta() * 0.1f;
	rotate(glm::vec3(0.f, 0.f, mouseDelta.x));
	camera->rotate(glm::vec3(mouseDelta.y, 0.f, 0.f));;
}
