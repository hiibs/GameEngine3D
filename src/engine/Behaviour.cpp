#include "Behaviour.h"
#include "Engine.h"
#include <GLFW/glfw3.h>

Behaviour::Behaviour(Object* owner) :
	owner(owner)
{
	owner->addBehaviour(this);
}

Behaviour::~Behaviour() {
	owner->removeBehaviour(this);
}

const Input* Behaviour::getInput() const {
	return static_cast<Engine*>(glfwGetWindowUserPointer(glfwGetCurrentContext()))->getInput();
}
