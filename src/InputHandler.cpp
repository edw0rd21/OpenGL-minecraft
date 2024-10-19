#include "InputHandler.h"

InputHandler::InputHandler(): m_camera(m_camera), m_renderer(m_renderer) {}

InputHandler::InputHandler(Camera& camera, Renderer& renderer, int width, int height) : m_camera(camera), m_renderer(renderer), SCR_WIDTH(width), SCR_HEIGHT(height)
{
    lastX = SCR_WIDTH / 2.0f;
    lastY = SCR_HEIGHT / 2.0f;
    firstMouse = true;
    processMouseMovement = false;
}

InputHandler::~InputHandler(){}

bool InputHandler::getMouseState() const
{
    return processMouseMovement;
}

void InputHandler::setMouseState(bool state)
{
    processMouseMovement = state;
}

void InputHandler::handleKeyboard(float deltaTime)
{
    if (glfwGetKey(m_renderer.getwindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_renderer.getwindow(), true);

    if (glfwGetKey(m_renderer.getwindow(), GLFW_KEY_P) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    else if (glfwGetKey(m_renderer.getwindow(), GLFW_KEY_Q) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Set to filled

    if (glfwGetKey(m_renderer.getwindow(), GLFW_KEY_W) == GLFW_PRESS)
    {
        //std::cout << "W key pressed" << std::endl;
        m_camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(m_renderer.getwindow(), GLFW_KEY_S) == GLFW_PRESS)
        m_camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(m_renderer.getwindow(), GLFW_KEY_A) == GLFW_PRESS)
        m_camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(m_renderer.getwindow(), GLFW_KEY_D) == GLFW_PRESS)
        m_camera.ProcessKeyboard(RIGHT, deltaTime);

    if (glfwGetKey(m_renderer.getwindow(), GLFW_KEY_SPACE) == GLFW_PRESS)
        m_camera.ProcessKeyboard(UP, 4 * deltaTime);
    if (glfwGetKey(m_renderer.getwindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        std::cout << "Move down" << std::endl;
        m_camera.ProcessKeyboard(DOWN, 4 * deltaTime);
    }
}
void InputHandler::handleMouse(double xpos, double ypos) 
{
    if (!processMouseMovement)
        return;

    float xposFloat = static_cast<float>(xpos);
    float yposFloat = static_cast<float>(ypos);

    if (firstMouse) {
        lastX = xposFloat;
        lastY = yposFloat;
        firstMouse = false;
    }

    float xoffset = xposFloat - lastX;
    float yoffset = lastY - yposFloat; // reversed since y-coordinates go from bottom to top

    lastX = xposFloat;
    lastY = yposFloat;

    m_camera.ProcessMouseMovement(xoffset, yoffset);
}

void InputHandler::handleScroll(double yoffset) 
{
    m_camera.ProcessMouseScroll(static_cast<float>(yoffset));
}