#pragma once

#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Voxel.h"
#include "Chunk.h"
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
    void setScrClr(glm::vec3 glmColor);
    void updateMode(char currentState);
    void clear();
    glm::vec3 getScrColor();
    void draw(Voxel& voxel, glm::vec3 color, glm::mat4& projection, glm::mat4& view,  glm::mat4& model);
    void draw(Chunk& chunk, glm::vec3 color, glm::mat4& projection, glm::mat4& view, glm::mat4& model);
    char renderState;

    void setupBuffers(Voxel& voxel);
    void setupBuffers(Chunk& chunk);

private:
    GLFWwindow* window;
    unsigned int m_SCR_WIDTH;
    unsigned int m_SCR_HEIGHT;
    std::string m_windowTitle;
    GLuint VBO, VAO, EBO;
    InputHandler& inputHandler;
    glm::vec3 clr_scr_color;

    Shader shader;
    Voxel voxel;
    Chunk chunk;
    Camera& camera;

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
};
