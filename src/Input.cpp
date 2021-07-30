#include "Input.h"
#include <GLFW/glfw3.h>


Input::Input(GLFWwindow* window) :
	window(window),
	mouseDelta(glm::vec2(0.f))
{
	double x, y;
	glfwGetCursorPos(glfwGetCurrentContext(), &x, &y);
	prevMousePos = glm::vec2(x, y);

	buttons.push_back(Button{ "Fire", GLFW_MOUSE_BUTTON_1 });
	buttons.push_back(Button{ "AltFire", GLFW_MOUSE_BUTTON_2 });
	buttons.push_back(Button{ "Forward", GLFW_KEY_W });
	buttons.push_back(Button{ "Back", GLFW_KEY_S });
	buttons.push_back(Button{ "Right", GLFW_KEY_D });
	buttons.push_back(Button{ "Left", GLFW_KEY_A });
	buttons.push_back(Button{ "Jump", GLFW_KEY_SPACE });
	buttons.push_back(Button{ "Crouch", GLFW_KEY_LEFT_CONTROL });

	for (int i = 0; i < buttons.size(); i++) {
		buttonStates.push_back(ButtonState::Up);
		prevButtonStates.push_back(ButtonState::Up);
		printf("%s\n", buttons[i].name.c_str());
	}
}

void Input::update() {
	if (!window)
		return;

	double x, y;
	glfwGetCursorPos(glfwGetCurrentContext(), &x, &y);
	glm::vec2 pos = glm::vec2(x, y);

	mouseDelta = pos - prevMousePos;
	prevMousePos = pos;

	setButtonStates();
}

void Input::setButtonStates() {
	for (int i = 0; i < buttons.size(); i++) {
		prevButtonStates[i] = buttonStates[i];
		
		if (prevButtonStates[i] == ButtonState::Pressed)
			prevButtonStates[i] = ButtonState::Down;
		else if (prevButtonStates[i] == ButtonState::Released)
			prevButtonStates[i] = ButtonState::Up;

		if (buttons[i].keyCode <= 7)
			buttonStates[i] = glfwGetMouseButton(glfwGetCurrentContext(), buttons[i].keyCode) == GLFW_PRESS ? ButtonState::Down : ButtonState::Up;
		else
			buttonStates[i] = glfwGetKey(glfwGetCurrentContext(), buttons[i].keyCode) == GLFW_PRESS ? ButtonState::Down : ButtonState::Up;


		if (buttonStates[i] != prevButtonStates[i]) {
			buttonStates[i] = buttonStates[i] == ButtonState::Down ? ButtonState::Pressed : ButtonState::Released;
		}
	}
}

bool Input::getButton(std::string buttonName) const {
	for (int i = 0; i < buttons.size(); i++) {
		if (buttons[i].name == buttonName)
			return (buttonStates[i] == ButtonState::Down || buttonStates[i] == ButtonState::Pressed);
	}
	printf("Button %s was not found!\n", buttonName.c_str());
	return false;
}

bool Input::getButtonPressed(std::string buttonName) const {
	for (int i = 0; i < buttons.size(); i++) {
		if (buttons[i].name == buttonName)
			return (buttonStates[i] == ButtonState::Pressed);
	}
	printf("Button %s was not found!\n", buttonName.c_str());
	return false;
}

glm::vec2 Input::getMouseDelta() const {
	return -mouseDelta;
}

void Input::enableCursor() const {
	glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Input::disableCursor() const {
	glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}
