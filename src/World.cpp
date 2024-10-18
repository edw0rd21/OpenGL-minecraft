#include "World.h"

World::World() : camera(camera), renderer(renderer) {}

World::World(Camera& camera, Renderer& renderer) : camera(camera), renderer(renderer)
{
    deltaTime = 0.0f;
    lastFrame = 0.0f;
}

//void addCube(const Quad& quad) {
//    quads.push_back(quad);
//}


void World::render(float aspectRatio)
{
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    glm::mat4 projection = camera.getProjectionMatrix(aspectRatio);
    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(40.0f * currentFrame), glm::vec3(0.0f, 1.0f, 0.0f));

    renderer.draw(projection, view, model);
}


void World::update(float deltaTime)
{

   rotationAngle += glm::radians(20.0f * deltaTime);
   glm::mat4 model = glm::mat4(1.0f);
   model = glm::rotate(model, rotationAngle, glm::vec3(0.0f, 1.0f, 0.0f));
    
}


