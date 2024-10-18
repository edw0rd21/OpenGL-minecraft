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
	void handleMouse(double xpos, double ypos);
	void handleScroll(double yoffset);

private:
	Renderer& m_renderer;
	Camera& m_camera;

	int SCR_WIDTH;
	int SCR_HEIGHT;
	float lastX;
	float lastY;
	bool firstMouse;
};

