#include "InputHandler.h"

InputHandler::InputHandler(): m_camera(m_camera), m_renderer(m_renderer) {}

InputHandler::InputHandler(Camera& camera, Renderer& renderer, int width, int height) : m_camera(camera), m_renderer(renderer), SCR_WIDTH(width), SCR_HEIGHT(height)
{
    lastX = SCR_WIDTH / 2.0f;
    lastY = SCR_HEIGHT / 2.0f;
    firstMouse = true;
    mouseState = false;
    flag = false;
}

InputHandler::~InputHandler(){}

void InputHandler::setMouseState(bool state)
{
    mouseState = state;
    flag = !flag;
}

bool InputHandler::getMouseState()
{
    return mouseState;
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
        m_camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(m_renderer.getwindow(), GLFW_KEY_S) == GLFW_PRESS)
        m_camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(m_renderer.getwindow(), GLFW_KEY_A) == GLFW_PRESS)
        m_camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(m_renderer.getwindow(), GLFW_KEY_D) == GLFW_PRESS)
        m_camera.ProcessKeyboard(RIGHT, deltaTime);

    if (glfwGetKey(m_renderer.getwindow(), GLFW_KEY_SPACE) == GLFW_PRESS)
        m_camera.ProcessKeyboard(UP,  deltaTime);
    if (glfwGetKey(m_renderer.getwindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        m_camera.ProcessKeyboard(DOWN, deltaTime);
    }

    if(flag == false)
    {
        if (glfwGetKey(m_renderer.getwindow(), GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
        {
            glfwSetInputMode(m_renderer.getwindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            mouseState = true;
        }

        if (glfwGetKey(m_renderer.getwindow(), GLFW_KEY_LEFT_ALT) == GLFW_RELEASE)
        {
            glfwSetInputMode(m_renderer.getwindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            mouseState = false;
        }
    }
    else 
    {
        if (glfwGetKey(m_renderer.getwindow(), GLFW_KEY_E) == GLFW_PRESS)
        {
            setMouseState(false);
            std::cout << "Mouse State:" << (mouseState ? "true" : "false") << std::endl;
        }
    }
}
void InputHandler::handleMouse(double xpos, double ypos) 
{
    if (!mouseState)
        return;

    float xposFloat = static_cast<float>(xpos);
    float yposFloat = static_cast<float>(ypos);

    if (firstMouse) 
    {
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