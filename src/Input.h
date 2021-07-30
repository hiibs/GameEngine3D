#pragma once
#include <glm/glm.hpp>
#include <string>
#include <vector>

class GLFWwindow;



class Input {
public:
	Input(GLFWwindow* window);

	void update();
	void setButtonStates();

	bool getButton(std::string buttonName) const;
	bool getButtonPressed(std::string buttonName) const;
	glm::vec2 getMouseDelta() const;
	void enableCursor() const;
	void disableCursor() const;

private:

	enum class ButtonState {
		Pressed,
		Released,
		Down,
		Up
	};

	struct Button {
		std::string name;
		int keyCode;
	};

	GLFWwindow* window;
	glm::vec2 mouseDelta;
	glm::vec2 prevMousePos;
	std::vector<Button> buttons;
	std::vector<ButtonState> buttonStates;
	std::vector<ButtonState> prevButtonStates;
};

