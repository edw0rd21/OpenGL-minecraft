#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
//#include "World.h"
#include "Renderer.h"
#include "Camera.h"
#include "Shader.h"

class Application
{

public:
    Application();
    Application(int width, int height, const std::string& title);
    ~Application();

    void run(); 
    void processInput();
    void update();

private:
    Renderer renderer;
    //World world;
    Camera camera;

    //float currentFrame;
    float deltaTime;
    float lastFrame;
    void mainLoop();
    float aspectRatio;
    Shader shader;

    float lastX;
    float lastY;
    bool firstMouse;

    //tried out defining callback functions in Application class to fix issue of input registry 
    // (worked, but not because of what i though)
    //static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    //{
    //    glViewport(0, 0, width, height);
    //}

    //static void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
    //{
    //    Application* application = static_cast<Application*>(glfwGetWindowUserPointer(window));


    //    float xpos = static_cast<float>(xposIn);
    //    float ypos = static_cast<float>(yposIn);

    //    if (application->firstMouse)
    //    {
    //        application->lastX = xpos;
    //        application->lastY = ypos;
    //        application->firstMouse = false;
    //    }

    //    float xoffset = xpos - application->lastX;
    //    float yoffset = application->lastY - ypos;

    //    application->lastX = xpos;
    //    application->lastY = ypos;

    //    application->camera.ProcessMouseMovement(xoffset, yoffset);
    //    std::cout << "mouse" << xpos << "," << ypos << std::endl;
    //}


    //static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
    //{
    //    Application* application = static_cast<Application*>(glfwGetWindowUserPointer(window));
    //    application->camera.ProcessMouseScroll(static_cast<float>(yoffset));
    //}
};
