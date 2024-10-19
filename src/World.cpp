#include "World.h"

World::World() : m_camera(), m_renderer() {}

World::World(Camera& camera, Renderer& renderer) : m_camera(&camera), m_renderer(&renderer)
{
    deltaTime = 0.0f;
    lastFrame = 0.0f;
}

//void addCube(const Quad& quad) 
//{
//    quads.push_back(quad);
//}

void World::update(glm::vec3 newColor)
{
   quad.quadColor = newColor;
   //rotationAngle += glm::radians(20.0f * deltaTime);
   //glm::mat4 model = glm::mat4(1.0f);
   //model = glm::rotate(model, rotationAngle, glm::vec3(0.0f, 1.0f, 0.0f));
    
}

void World::render(float aspectRatio)
{
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    glm::mat4 projection = m_camera->getProjectionMatrix(aspectRatio);
    glm::mat4 view = m_camera->getViewMatrix();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(40.0f * currentFrame), glm::vec3(0.0f, 1.0f, 0.0f));

    m_renderer->draw(quad.quadColor, projection, view, model);
}





