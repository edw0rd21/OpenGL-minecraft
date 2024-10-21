#include "Renderer.h"
#include "InputHandler.h"

Renderer::Renderer() : m_SCR_WIDTH(0), m_SCR_HEIGHT(0), camera(camera) , inputHandler(inputHandler){}

Renderer::Renderer(int width, int height, const std::string& windowTitle, Camera& camera, InputHandler& inputHandler)
    : m_SCR_WIDTH(width), m_SCR_HEIGHT(height), m_windowTitle(windowTitle) , camera(camera) , inputHandler(inputHandler)
{
    VBO = 0;
    VAO = 0;
    EBO = 0;
    clr_scr_color = glm::vec3(0.5f, 0.5f, 0.5f);
    renderState = 0;
}

Renderer::~Renderer()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glfwDestroyWindow(window);
    glfwTerminate();
}

GLFWwindow* Renderer::getwindow() const { return window; }

void Renderer::init()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(m_SCR_WIDTH, m_SCR_HEIGHT, m_windowTitle.c_str(), NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, &framebuffer_size_callback);
    glfwSetCursorPosCallback(window, &mouse_callback);
    glfwSetScrollCallback(window, &scroll_callback);
    
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
    glEnable(GL_DEPTH_TEST);

    shader.load("shader/shader.vert", "shader/shader.frag");

    //setupBuffersInstanced(voxel);
    setupBuffers(voxel);
}
void Renderer::update(glm::vec3 glmColor)
{
    clr_scr_color = glm::vec3(glmColor.x, glmColor.y, glmColor.z);
}
void Renderer::updateMode(char state)
{
    renderState = state;
    setupBuffers(voxel);
}

void Renderer::clear()
{
    glClearColor(clr_scr_color.x, clr_scr_color.y, clr_scr_color.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
glm::vec3 Renderer::getScrColor()
{
    return clr_scr_color;
}

void Renderer::draw(const glm::vec3& color, glm::mat4& projection, glm::mat4& view, glm::mat4& model)
{
    shader.use();
    glBindVertexArray(VAO); 

    shader.setVec3("color", color);
    shader.setMat4("projection", projection);
    shader.setMat4("view", view);
    shader.setMat4("model", model);
    if (renderState == 0)
        glDrawElements(GL_TRIANGLES, voxel.c_indexCount, GL_UNSIGNED_INT, 0);
    else if (renderState == 1)
        glDrawElements(GL_TRIANGLES, voxel.p_indexCount, GL_UNSIGNED_INT, 0);

}

void Renderer::setupBuffers(Voxel& voxel)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);        
    
    glBindVertexArray(VAO);

    if(renderState == 0)
    {    
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, voxel.c_size, voxel.c_vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, voxel.c_indexCount * sizeof(unsigned int), voxel.c_indices.data(), GL_STATIC_DRAW);
    }

    else if (renderState == 1)
    {
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, voxel.p_size, voxel.p_vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, voxel.p_indexCount * sizeof(unsigned int), voxel.p_indices.data(), GL_STATIC_DRAW);
    }

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    //glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    //glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Renderer::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Renderer::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    Renderer* renderer = static_cast<Renderer*>(glfwGetWindowUserPointer(window));
    renderer->inputHandler.handleMouse(xpos, ypos);
}


void Renderer::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    Renderer* renderer = static_cast<Renderer*>(glfwGetWindowUserPointer(window));
    renderer->inputHandler.handleScroll(yoffset);
}