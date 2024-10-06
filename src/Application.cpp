#include "Application.h"

Application::Application() : renderer() , aspectRatio(0) {}

Application::Application(int width, int height, const std::string& title) : camera(glm::vec3(0.0f, 2.0f, 4.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, -25.0f), renderer(width, height, title)
{
	aspectRatio = static_cast<float>(width) / static_cast<float>(height);
	deltaTime = 0.0f;
	lastFrame = 0.0f;

}

Application::~Application() {}

void Application::run() 
{ 
	renderer.init();
	mainLoop(); 
}

void update()
{

}
void Application::processInput()
{
    if (glfwGetKey(renderer.getwindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(renderer.getwindow(), true);

    if (glfwGetKey(renderer.getwindow(), GLFW_KEY_P) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    else if (glfwGetKey(renderer.getwindow(), GLFW_KEY_Q) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Set to filled

    if (glfwGetKey(renderer.getwindow(), GLFW_KEY_W) == GLFW_PRESS)
    {
        //std::cout << "W key pressed" << std::endl;
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(renderer.getwindow(), GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(renderer.getwindow(), GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(renderer.getwindow(), GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);

    if (glfwGetKey(renderer.getwindow(), GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.ProcessKeyboard(UP, 4 * deltaTime);
    if (glfwGetKey(renderer.getwindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        std::cout << "Move down" << std::endl;
        camera.ProcessKeyboard(DOWN, 4 * deltaTime);
    }
}
void Application::mainLoop() 
{
	while (!glfwWindowShouldClose(renderer.getwindow()))
	{	
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput();

		renderer.clear();

		//shader.use();
		glm::mat4 projection = camera.getProjectionMatrix(aspectRatio);

		glm::mat4 view = camera.getViewMatrix();
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(20.0f * currentFrame), glm::vec3(0.0f, 1.0f, 0.0f));
		
		renderer.draw(projection, view, model);

		glfwSwapBuffers(renderer.getwindow());
		glfwPollEvents();
	}
}