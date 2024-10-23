#include "Chunk.h"

Chunk::Chunk()
{
    voxelDist = voxel.getvoxelDist();
    genChunkData();
}


Chunk::~Chunk() {}

void Chunk::genChunkData()
{
    vertices.clear();
    indices.clear();

    int vertexOffset = 0;
    for (int x = 0; x < CHUNK_SIZE; ++x) 
    {
        for (int y = 0; y < CHUNK_SIZE; ++y) 
        {
            for (int z = 0; z < CHUNK_SIZE; ++z)
            {
                for (size_t i = 0; i < voxel.c_vertices.size(); i += 3)
                {
                    glm::vec3 vertexPos(voxel.c_vertices[i], voxel.c_vertices[i + 1], voxel.c_vertices[i + 2]);
                    glm::vec3 cubePos = vertexPos + glm::vec3(x * voxelDist, y * voxelDist, z* voxelDist);
                    vertices.push_back(cubePos);
                }
                for (const unsigned int& index : voxel.c_indices)
                {
                    indices.push_back(index + vertexOffset);
                }

                vertexOffset += voxel.c_vertices.size() / 3;
            }
        }
    }

    vertexSize = vertices.size() * sizeof(glm::vec3);
    indexCount = indices.size();
}

void Chunk::setupBuffers()
{
    glGenVertexArrays(1, &chunkVAO);
    glGenBuffers(1, &chunkVBO);
    glGenBuffers(1, &chunkEBO);

    glBindVertexArray(chunkVAO);

    glBindBuffer(GL_ARRAY_BUFFER, chunkVBO);
    glBufferData(GL_ARRAY_BUFFER, vertexSize, vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, chunkEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

int Chunk::getChunkSize()
{
    return CHUNK_SIZE;
}

void Chunk::setChunkSize(int value)
{
    CHUNK_SIZE = value;
    //genChunkData();    
}