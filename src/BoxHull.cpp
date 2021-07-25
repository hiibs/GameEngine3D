#include "BoxHull.h"
#include "Engine.h"

BoxHull::BoxHull(Scene* scene) :
	Object(scene),
	halfExtents(glm::vec3(0.5f, 0.5f, 0.5f)),
	lastCorrection(glm::vec3(0.f)),
	velocity(glm::vec3(0.f)),
	lastPosition(glm::vec3(0.f))
{
	Engine* engine = static_cast<Engine*>(glfwGetWindowUserPointer(glfwGetCurrentContext()));
	engine->getPhysics()->addBoxHull(this);
}

BoxHull::~BoxHull() {
	Engine* engine = static_cast<Engine*>(glfwGetWindowUserPointer(glfwGetCurrentContext()));
	engine->getPhysics()->removeBoxHull(this);

	
}

void BoxHull::update(float deltaTime) {
	


	/*
		float projectedVel = glm::dot(velocity, glm::normalize(lastCorrection));
		if (projectedVel > 0.001f)
			velocity -= glm::normalize(lastCorrection) * projectedVel;*/
}
