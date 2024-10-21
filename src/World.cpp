#include "World.h"

World::World() : m_camera(), m_renderer() {}

World::World(Camera& camera, Renderer& renderer) : m_camera(&camera), m_renderer(&renderer)
{
    deltaTime = 0.0f;
    lastFrame = 0.0f;
    numChunks = 1;
    numCubes = 1;
    rotationState = false;
    //loadChunk();
}

//void addCube(const Quad& quad) 
//{
//    quads.push_back(quad);
//}
void World::loadChunk()
{
    chunks.clear();

    //chunk creation
    for (int x = 0; x < numChunks; ++x)
    {
        for (int y = 0; y < numChunks; ++y)
        {
            for (int z = 0; z < numChunks; ++z)
            {
                Chunk chunk;
                chunk.position = glm::vec3(x * numCubes, y * numCubes, z * numCubes);

                // populating each chunk with cube positions
                for (int i = 0; i < numCubes; ++i)
                {
                    for (int j = 0; j < numCubes; ++j)
                    {
                        for (int k = 0; k < numCubes; ++k)
                        {
                            glm::vec3 cubePos = chunk.position + glm::vec3(i, j, k);

                            if (isPointInFrustum(cubePos) != World::OUTSIDE)
                            {
                                Voxel voxel;
                                voxel.position = cubePos; 
                                chunk.voxels.push_back(voxel);
                            }
                        }
                    }
                }
                if (!chunk.voxels.empty())
                {
                    chunks.push_back(chunk);
                    //chunks[chunk.position] = chunk;  //unordered map
                }
            }
        }
    }
}

void World::unloadChunk()
{

    auto it = chunks.begin();
    while (it != chunks.end())
    {
        if (isPointInFrustum(it->position) == World::OUTSIDE)
        //if (isPointInFrustum(it->second.position) == World::OUTSIDE)  //unordered map
        {
            it = chunks.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void World::setChunkNum(int value)
{
    numChunks = value;
    loadChunk();
}

void World::setChunkSize(int value)
{
    numCubes = value;
    loadChunk();
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

void World::update(glm::vec3 newColor)
{
    //voxel.color = newColor;
    for (auto& chunk : chunks)
    {
        for (auto& voxel : chunk.voxels) 
        {
            voxel.color = newColor;
        }
    }
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

    glm::mat4 model = glm::mat4(1.0f);

    for (auto& chunk : chunks)
    {
        if (isPointInFrustum(chunk.position) == World::INSIDE)
        {
            for (auto& voxel : chunk.voxels)
            {
                model = glm::translate(glm::mat4(1.0f), voxel.position);

                if (rotationState == true)
                    model = glm::rotate(model, glm::radians(40.0f * currentFrame), glm::vec3(0.0f, 1.0f, 0.0f));

                m_renderer->draw(voxel.color, projection, view, model);
            }
        }
    }
}






