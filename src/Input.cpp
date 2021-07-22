#include "Input.h"
#include <GLFW/glfw3.h>


Input::Input(GLFWwindow* window) :
	window(window),
	mouseDelta(glm::vec2(0.f))
{
	double x, y;
	glfwGetCursorPos(glfwGetCurrentContext(), &x, &y);
	prevMousePos = glm::vec2(x, y);
}

void Input::update() {
	if (!window)
		return;

	double x, y;
	glfwGetCursorPos(glfwGetCurrentContext(), &x, &y);
	glm::vec2 pos = glm::vec2(x, y);

	mouseDelta = pos - prevMousePos;
	prevMousePos = pos;
}

const bool Input::isPressed(Button button) const {
	if (button == LEFT_CLICK || button == RIGHT_CLICK)
		return glfwGetMouseButton(glfwGetCurrentContext(), button) == GLFW_PRESS ? true : false;
	else
		return glfwGetKey(glfwGetCurrentContext(), button) == GLFW_PRESS ? true : false;
}

const glm::vec2 Input::getMouseDelta() const {
	return -mouseDelta;
}

const void Input::enableCursor() const {
	glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

const void Input::disableCursor() const {
	glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}
