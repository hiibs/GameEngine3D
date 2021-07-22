#include "Player.h"
#include "Scene.h"
#include "Engine.h"

Player::Player(Scene* scene) : BoxHull(scene),
	velocity(glm::vec3(0.f))
{
	// Set player size
	halfExtents = glm::vec3(0.4f, 0.4f, 0.9f);

	// Create player camera
	camera = new Camera(scene);
	camera->setParent(this);
	camera->setRotation(glm::vec3(90.f, 0.f, 0.f));
	camera->setPosition(glm::vec3(0.f, 0.f, 0.7f));
	Engine::getInstance()->getRenderer()->camera = camera;

	// Get input
	input = Engine::getInstance()->getInput();
	input->disableCursor();
}

void Player::update(float deltaTime) {
	// Update velocity
	//printf("%f\n", velocity.z);
	velocity = (getPosition() - lastPosition) / deltaTime;
	lastPosition = getPosition();

	float acceleration = 20.f;
	float friction = 6.f;

	float moveSpeed = 5.f;
	float sensitivity = 0.1f;


	mouseLook();

	velocity += getInputDir() * moveSpeed * deltaTime;

	if (input->isPressed(JUMP))
		velocity.z += 20.f * deltaTime;
		
	velocity.z -= 10.f * deltaTime;
	
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
