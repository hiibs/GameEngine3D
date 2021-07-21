#pragma once
#include <GLFW/glfw3.h>

enum Button {
	FORWARD = GLFW_KEY_W,
	BACK = GLFW_KEY_S,
	RIGHT = GLFW_KEY_D,
	LEFT = GLFW_KEY_A,
};

class Input {
public:
	static bool isPressed(Button button);
};

