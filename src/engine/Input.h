#pragma once
#include <glm/glm.hpp>

class GLFWwindow;

enum Button {
	LEFT_CLICK = 0,
	RIGHT_CLICK = 1,
	FORWARD = 87,
	BACK = 83,
	RIGHT = 68,
	LEFT = 65
};

class Input {
public:
	Input(GLFWwindow* window);

	void update();

	const bool isPressed(Button button) const;
	const glm::vec2 getMouseDelta() const;
	const void enableCursor() const;
	const void disableCursor() const;

private:
	GLFWwindow* window;
	glm::vec2 mouseDelta;
	glm::vec2 prevMousePos;
};

