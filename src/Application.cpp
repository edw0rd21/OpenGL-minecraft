#include "Application.h"

Application::Application() : renderer() , aspectRatio(0) , inputHandler() , world(), gui() {}

Application::Application(int width, int height, const std::string& title)
	: camera(glm::vec3(0.0f, 2.0f, 4.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, -25.0f), 
	  renderer(width, height, title, camera, inputHandler), 
	  inputHandler(camera, renderer, width, height),
	  world(camera, renderer),
      gui(renderer, world, inputHandler)
{
	aspectRatio = static_cast<float>(width) / static_cast<float>(height);
	scr_clear_color = glm::vec3(gui.glmScrColor.x, gui.glmScrColor.y, gui.glmScrColor.z);
}

Application::~Application() {}

void Application::run() 
{ 	
	renderer.init();

    gui.init();

	if (camera.hasCameraMoved())
	{
		world.update();
	}

	mainLoop();

}

void Application::update()
{

}

void Application::handleInput(float deltaTime) 
{
	inputHandler.handleKeyboard(deltaTime);
}

void Application::mainLoop()
{
	while (!glfwWindowShouldClose(renderer.getwindow()))
	{	

		inputHandler.handleKeyboard(world.deltaTime);

		renderer.clear();
        gui.newFrame();
		gui.drawFrame();

		world.render(aspectRatio);

		gui.render();

		glfwSwapBuffers(renderer.getwindow());
		glfwPollEvents();
	}
}