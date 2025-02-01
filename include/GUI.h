#pragma once

#include "Renderer.h"
#include "World.h"
#include "InputHandler.h"
#include "Voxel.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

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
	glm::vec3 glmScrColor;

private:
	bool show_demo_window;
	bool show_another_window;
	bool renderMode_window;
	ImVec4 clear_scr_color;
	ImVec4 clear_color;

	Voxel voxel;
	Chunk chunk;

	ImGuiIO* io;
	World* m_world;
	Renderer* m_renderer;
	InputHandler* m_inputHandler;
};

