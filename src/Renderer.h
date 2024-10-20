#pragma once

#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Quad.h"
#include "Camera.h"

class InputHandler;

class Renderer
{
public:
    Renderer();
    Renderer(int width, int height, const std::string& windowTitle, Camera& camera, InputHandler& inputHandler);
    ~Renderer();

    GLFWwindow* getwindow() const;
    void init();
    void clear(ImVec4 scrColor);
    void draw(glm::vec3 quadColor, glm::mat4& projection, glm::mat4& view,  glm::mat4& model);

private:
    GLFWwindow* window;
    unsigned int m_SCR_WIDTH;
    unsigned int m_SCR_HEIGHT;
    std::string m_windowTitle;
    GLuint VBO, VAO, EBO;
    InputHandler& inputHandler;

    Shader shader;
    Quad quad;
    Camera& camera;

    void setupBuffers(const Quad& quad);
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
};
