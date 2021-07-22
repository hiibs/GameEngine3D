#include "BoxHull.h"
#include "Engine.h"

BoxHull::BoxHull(Scene* scene) :
	Object(scene),
	halfExtents(glm::vec3(0.5f, 0.5f, 0.5f))
{
	Engine* engine = static_cast<Engine*>(glfwGetWindowUserPointer(glfwGetCurrentContext()));
	engine->getPhysics()->addBoxHull(this);
}

BoxHull::~BoxHull() {
	Engine* engine = static_cast<Engine*>(glfwGetWindowUserPointer(glfwGetCurrentContext()));
	engine->getPhysics()->removeBoxHull(this);
}
