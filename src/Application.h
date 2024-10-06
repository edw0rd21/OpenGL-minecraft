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
};
