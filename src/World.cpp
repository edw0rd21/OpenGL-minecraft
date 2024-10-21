#include "World.h"

World::World() : m_camera(), m_renderer() {}

World::World(Camera& camera, Renderer& renderer, Quad& quad) : m_camera(&camera), m_renderer(&renderer), m_quad(&quad)
{
    deltaTime = 0.0f;
    lastFrame = 0.0f;
    chunkSize = 1;
    rotationState = false;
    //loadChunk();
}

//void addCube(const Quad& quad) 
//{
//    quads.push_back(quad);
//}
void World::loadChunk()
{
    cubePositions.clear();
    for (int x = 0; x < chunkSize; ++x) 
    {
        for (int y = 0; y < chunkSize; ++y)
        {
            for (int z = 0; z < chunkSize; ++z)
            {
                //cubePositions.push_back(glm::vec3(x, y, z));
                glm::vec3 cubePos(x, y, z);
                if (isPointInFrustum(cubePos) != World::OUTSIDE)
                    cubePositions.push_back(cubePos);

            }
        }
    }
}

void World::unloadChunk()
{

    auto it = cubePositions.begin();
    while (it != cubePositions.end())
    {
        if (isPointInFrustum(*it) == World::OUTSIDE)
        {
            it = cubePositions.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void World::setChunkSize(int value)
{
    chunkSize = value;
    //loadChunk();
}

void World::update(glm::vec3 newColor)
{
   m_quad->quadColor = newColor;
   //rotationAngle += glm::radians(20.0f * deltaTime);
   //glm::mat4 model = glm::mat4(1.0f);
   //model = glm::rotate(model, rotationAngle, glm::vec3(0.0f, 1.0f, 0.0f));
}

void World::calculateFrustumPlanes(glm::mat4& projectionViewMatrix)
{
    planes[0] = glm::vec4(projectionViewMatrix[0][3] + projectionViewMatrix[0][0],
        projectionViewMatrix[1][3] + projectionViewMatrix[1][0],
        projectionViewMatrix[2][3] + projectionViewMatrix[2][0],
        projectionViewMatrix[3][3] + projectionViewMatrix[3][0]);

    // Right plane
    planes[1] = glm::vec4(projectionViewMatrix[0][3] - projectionViewMatrix[0][0],
        projectionViewMatrix[1][3] - projectionViewMatrix[1][0],
        projectionViewMatrix[2][3] - projectionViewMatrix[2][0],
        projectionViewMatrix[3][3] - projectionViewMatrix[3][0]);

    // Bottom plane
    planes[2] = glm::vec4(projectionViewMatrix[0][3] + projectionViewMatrix[0][1],
        projectionViewMatrix[1][3] + projectionViewMatrix[1][1],
        projectionViewMatrix[2][3] + projectionViewMatrix[2][1],
        projectionViewMatrix[3][3] + projectionViewMatrix[3][1]);

    // Top plane
    planes[3] = glm::vec4(projectionViewMatrix[0][3] - projectionViewMatrix[0][1],
        projectionViewMatrix[1][3] - projectionViewMatrix[1][1],
        projectionViewMatrix[2][3] - projectionViewMatrix[2][1],
        projectionViewMatrix[3][3] - projectionViewMatrix[3][1]);

    // Near plane
    planes[4] = glm::vec4(projectionViewMatrix[0][3] + projectionViewMatrix[0][2],
        projectionViewMatrix[1][3] + projectionViewMatrix[1][2],
        projectionViewMatrix[2][3] + projectionViewMatrix[2][2],
        projectionViewMatrix[3][3] + projectionViewMatrix[3][2]);

    // Far plane
    planes[5] = glm::vec4(projectionViewMatrix[0][3] - projectionViewMatrix[0][2],
        projectionViewMatrix[1][3] - projectionViewMatrix[1][2],
        projectionViewMatrix[2][3] - projectionViewMatrix[2][2],
        projectionViewMatrix[3][3] - projectionViewMatrix[3][2]);

    // Normalize all planes (to keep proper distances)
    for (int i = 0; i < 6; i++)
    {
        float length = glm::length(glm::vec3(planes[i]));
        planes[i] /= length;
    }
}

int World::isPointInFrustum(const glm::vec3& point) const
{
    for (int i = 0; i < 6; i++)
    {
        if (glm::dot(glm::vec3(planes[i]), point) + planes[i].w < 0)
            return OUTSIDE;
    }
    return INSIDE;
}

void World::render(float aspectRatio)
{
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    glm::mat4 projection = m_camera->getProjectionMatrix(aspectRatio);
    glm::mat4 view = m_camera->getViewMatrix();
    glm::mat4 projectionViewMatrix = projection * view;

    calculateFrustumPlanes(projectionViewMatrix);

    unloadChunk();
    loadChunk();

    glm::mat4 model = glm::mat4(1.0f);

    for (const auto& position : cubePositions)
    {

        model = glm::translate(glm::mat4(1.0f), position);
        if (rotationState == true)
          model = glm::rotate(model, glm::radians(40.0f * currentFrame), glm::vec3(0.0f, 1.0f, 0.0f));

        m_renderer->draw(m_quad->quadColor, projection, view, model);
    }
}





