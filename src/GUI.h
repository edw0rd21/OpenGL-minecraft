#pragma once

#include "Renderer.h"
#include "World.h"
#include "InputHandler.h"

#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw.h"
#include "vendor/imgui/imgui_impl_opengl3.h"

class GUI
{
public:

	GUI();
	GUI(Renderer& renderer, World& m_world, InputHandler& inputHandler);
	~GUI();
	void init();
	void newFrame();
	void drawFrame();
	void render();

private:
	bool show_demo_window;
	bool show_another_window;
	ImVec4 clear_color;
	ImVec4 clear_scr_color;

	ImGuiIO* io;
	World* m_world;
	Renderer* m_renderer;
	InputHandler* m_inputHandler;
};

