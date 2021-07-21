#include "Input.h"

bool Input::isPressed(Button button) {
	return glfwGetKey(glfwGetCurrentContext(), button) == GLFW_PRESS ? true : false;
}
