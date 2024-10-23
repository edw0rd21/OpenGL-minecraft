#pragma once

#include "Renderer.h"
#include "Camera.h"


class InputHandler
{
public:
	InputHandler();
	InputHandler(Camera& camera, Renderer& renderer, int width, int height);
	~InputHandler();

	void handleKeyboard(float deltaTime);
	bool getMouseState();
	void setMouseState(bool state);
	void handleMouse(double xpos, double ypos);
	void handleScroll(double yoffset);

	bool mouseState;

private:
	Renderer& m_renderer;
	Camera& m_camera;

	int SCR_WIDTH;
	int SCR_HEIGHT;
	float lastX;
	float lastY;
	bool firstMouse;
	bool flag;
};

