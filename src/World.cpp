#include "World.h"

World::World() : m_camera(), m_renderer(){}

World::World(Camera& camera, Renderer& renderer) : m_camera(&camera), m_renderer(&renderer)
{
    deltaTime = 0.0f;
    lastFrame = 0.0f;
    numChunks = 10;
    numCubes = chunk.getChunkSize();
    voxelDist = voxel.getvoxelDist();
    chunkColor = chunk.color;
    rotationState = false;

    m_worldNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    m_worldNoise.SetSeed(1337);  // Fixed seed for consistency
    m_worldNoise.SetFrequency(0.08f);
}


void World::loadChunk()
{
    chunks.clear();
    chunks.reserve(numChunks* numChunks * numChunks);

    const int chunkSpan = numChunks / 2;

    //chunk creationss
    for (int x = 0; x < numChunks; ++x)
    {
        for (int z = 0; z < numChunks; ++z)
        {
            Chunk chunk;

            chunk.position = glm::vec3( x * numCubes * voxelDist, 0, z * numCubes * voxelDist);

            chunk.generateHeightmap(m_worldNoise);
            chunk.populateBlocks();
            chunk.generateMesh();
            chunk.setupBuffers();
            chunks.push_back(chunk);
        }
    }
}


void World::unloadChunk()
{
    for (auto& chunk : chunks)
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
}

Voxel& World::getVoxel()
{
    for (auto& chunk : chunks)
    {
        for (auto& voxel : chunk.voxels)
        {
            return voxel;
        }
    }
}

void World::update()
{    
    loadChunk();
    unloadChunk();

    std::cout << "Chunks after update: " << chunks.size() << std::endl;
    printDrawCalls = true;
}

void World::setChunkNum(int value)
{
    numChunks = value;
    update();
}

void World::setChunkSize(int value)
{
    numCubes = value;
    update();
}

void World::setVoxelDist(float value)
{
    voxelDist = value;
    update();
}

void World::setVoxelColor(glm::vec3 newColor)
{
    chunkColor = newColor;
    //for (auto& chunk : chunks)
    //{
    //    chunk.color = newColor;
    //}

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

int World::isChunkInFrustum(const Chunk& chunk) const
{
    glm::vec3 minBound = chunk.position;  
    glm::vec3 maxBound = chunk.position + glm::vec3(numCubes * voxelDist); 

    for (int i = 0; i < 6; i++)
    {

        if (isPointInFrustum(minBound) == World::OUTSIDE &&
            isPointInFrustum(maxBound) == World::OUTSIDE)
        {
            return OUTSIDE;  
        }
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

    int drawcalls = 0;

    for (auto& chunk : chunks)
    {
        if (isChunkInFrustum(chunk) == World::INSIDE)
        {
            glm::mat4 chunkModel = glm::translate(glm::mat4(1.0f), chunk.position);

            if (rotationState == true)
                chunkModel = glm::rotate(chunkModel, glm::radians(40.0f * currentFrame), glm::vec3(0.0f, 1.0f, 0.0f));

            m_renderer->draw(chunk, chunkColor, projection, view, chunkModel);
            drawcalls++;        
        }
    }
    if(printDrawCalls)
    {
        std::cout << "Number of draw calls:" << drawcalls<<std::endl;
        printDrawCalls = false;
    }
}