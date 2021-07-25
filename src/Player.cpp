#include "Player.h"
#include "Scene.h"
#include "Engine.h"
#include "OverlayImage.h"
#include <glm/gtx/euler_angles.hpp>

Player::Player(Scene* scene) : BoxHull(scene),
	time(0.f),
	weaponPos(glm::vec3(0.05f, 0.15f, -0.12f)),
	cameraPos(glm::vec3(0.f, 0.f, 0.7f))
{
	// Set player size
	halfExtents = glm::vec3(0.4f, 0.4f, 0.9f);

	// Create player camera
	camera = new Camera(scene);
	camera->setParent(this);
	camera->setPosition(cameraPos);
	Engine::getInstance()->getRenderer()->camera = camera;


	Texture* tex = new Texture("Shotgun.png");
	Material* mat = new Material("Diffuse", tex);
	weapon = new Mesh(scene);
	weapon->loadMesh("Shotgun.obj");
	weapon->setParent(camera);
	weapon->setPosition(weaponPos);
	weapon->material = mat;
	weapon->enableCollision = false;
	weapon->fpModel = true;


	Texture* chTex = new Texture("Crosshair.png");
	OverlayImage* crosshair = new OverlayImage(camera);
	crosshair->material = new Material("UI", chTex);
	crosshair->anchorPoint = glm::vec2(0.f);
	crosshair->size = glm::vec2(32.f);
	crosshair->offset = glm::vec2(0.f);

	// Get input
	input = Engine::getInstance()->getInput();
	input->disableCursor();
}

void Player::update(float deltaTime) {
	

	mouseLook();
	updateMovement(deltaTime);

	// View bobbing
	
	time += deltaTime * 1.5f;
	time += glm::length(velocity) / 200.f;
	float intensity = 0.1f;
	float wepOffset = glm::sin(time * 0.8f) * intensity / 5.f - intensity / 10.f;
	float camOffset = glm::sin(time * 1.6f) * intensity * glm::length(velocity) / 10.f - intensity / 2.f;
	weapon->setPosition(glm::vec3(weaponPos.x, weaponPos.y + wepOffset, weaponPos.z));
	if (isGrounded) {
		camera->setPosition(glm::vec3(camera->getPosition().x, camera->getPosition().y, cameraPos.z + camOffset));
	}

}

void Player::lateUpdate(float deltaTime) {
	move(velocity * deltaTime, true);
}

void Player::setPosition(glm::vec3 position, bool updatePhysics) {
	if (!updatePhysics) {
		glm::vec3 delta = position - getPosition();
		lastPosition += delta;
	}
	
	Object::setPosition(position, updatePhysics);
}

void Player::move(glm::vec3 delta, bool updatePhysics) {
	if (!updatePhysics)
		lastPosition += delta;
	Object::move(delta, updatePhysics);
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
	//weapon->setPosition(glm::vec3(weaponPos.x - (mouseDelta.x/1000.f), weapon->getPosition().y, weapon->getPosition().z));
}

void Player::updateMovement(float deltaTime) {
	velocity = (getPosition() - lastPosition) / deltaTime;
	lastPosition = getPosition();


	float acceleration = 120.f;
	float friction = 60.f;
	float runSpeed = 10.f;
	bool crouched = false;
	
	//velocity -= lastCorrection;

	if (input->isPressed(CROUCH)) {
		halfExtents.z = 0.45f;
		runSpeed = 4.f;
		crouched = true;
	}
	else {
		if (halfExtents.z == 0.45f) {
			halfExtents.z = 0.9;
			//move(glm::vec3(0.f, 0.f, 0.45f));
		}
	}

	if (isGrounded) {
		velocity += getInputDir() * acceleration * deltaTime;

		glm::vec3 hVel = glm::vec3(velocity.x, velocity.y, 0.f);
		if (glm::length(glm::vec3(hVel)) > runSpeed) {
			glm::vec3 newHVel = glm::normalize(hVel) * runSpeed;
			velocity.x = newHVel.x;
			velocity.y = newHVel.y;
		}

		
		if (glm::length(hVel) - friction * deltaTime > 0.f)
			velocity -= glm::normalize(hVel) * friction * deltaTime;
		else
			velocity = glm::vec3(0.f);
		
		/*
		if (glm::length(velocity) < 40.f * deltaTime)
			velocity = glm::vec3(0.f);
		*/
		if (input->isPressed(JUMP) && !crouched) {
			move(glm::vec3(0.f, 0.f, 0.1f));
			velocity.z = 6.f;
		}
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
}
