#include <Chunk.h>

Chunk::Chunk() 
{
    //generateHeightmap();
    //populateBlocks();
    //generateMesh();
    VBO = 0;
    VAO = 0;
    EBO = 0;
}

Chunk::~Chunk()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}



bool Chunk::isBlockAt(int x, int y, int z) const 
{
    if (x < 0 || x >= CHUNK_SIZE || y < 0 || y >= CHUNK_SIZE || z < 0 || z >= CHUNK_SIZE) 
        return false;
    
    return blocks[x + y * CHUNK_SIZE + z * CHUNK_SIZE * CHUNK_SIZE];
    //return blocks[x][y][z];
}

bool Chunk::shouldRenderFace(int x, int y, int z, int faceIndex) const
{
    static constexpr int  adjacentOffsets[6][3] = {
        {0, 0, -1},  // Back face
        {0, 0, 1},   // Front face
        {-1, 0, 0},  // Left face
        {1, 0, 0},   // Right face
        {0, -1, 0},  // Bottom face
        {0, 1, 0}    // Top face
    };

    const auto& offset = adjacentOffsets[faceIndex];
    int adjX = x + offset[0];
    int adjY = y + offset[1];
    int adjZ = z + offset[2];

    return !isBlockAt(adjX, adjY, adjZ);
}

void Chunk::generateHeightmap(const FastNoiseLite& noise)
{
    //FastNoiseLite noise;

    //noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    //noise.SetSeed(1337);  // Fixed seed for consistency
    //noise.SetFrequency(0.08f);

    heightmap.resize(CHUNK_SIZE * CHUNK_SIZE);

    for (int x = 0; x < CHUNK_SIZE; ++x) 
    {
        for (int z = 0; z < CHUNK_SIZE; ++z) 
        {
            // Convert to world coordinates
            float worldX = position.x + (x * voxelDist);
            float worldZ = position.z + (z * voxelDist);

            // Multi-octave noise
            float noiseValue =
                noise.GetNoise(worldX * 0.01f, worldZ * 0.01f) * 1.0f +  // Low frequency
                noise.GetNoise(worldX * 0.05f, worldZ * 0.05f) * 0.5f +  // Medium frequency
                noise.GetNoise(worldX * 0.1f, worldZ * 0.1f) * 0.25f;    // High frequency

            // Normalize and scale
            noiseValue = (noiseValue + 1.0f) * 0.5f;  // [-1,1] -> [0,1]
            noiseValue = pow(noiseValue, 2.2f);       // Sharpen peaks

            heightmap[x + z * CHUNK_SIZE] =
                static_cast<int>(noiseValue * 25.0f);
        }
    }
}

void Chunk::populateBlocks()
{

    blocks.resize(CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE, false);

    for (int x = 0; x < CHUNK_SIZE; ++x) 
    {
        for (int z = 0; z < CHUNK_SIZE; ++z) 
        {
            const int height = heightmap[x + z * CHUNK_SIZE];

            for (int y = 0; y < height; ++y)
            {
                blocks[x + y * CHUNK_SIZE + z * CHUNK_SIZE * CHUNK_SIZE] = true;
                //blocks[x][y][z] = true;
            }
        }
    }
}

void Chunk::generateMesh()
{
    vertices.clear();
    indices.clear();

    static constexpr int faceIndices[6][6] = {
           {0, 1, 2, 2, 3, 0},     // Back
           {4, 5, 6, 6, 7, 4},     // Front
           {8, 9, 10, 10, 11, 8},   // Left
           {12, 13, 14, 14, 15, 12}, // Right
           {16, 17, 18, 18, 19, 16}, // Bottom
           {20, 21, 22, 22, 23, 20}  // Top
    };

    int vertexOffset = 0;

    const glm::vec3 chunkWorldPos = position;

    for (int x = 0; x < CHUNK_SIZE; ++x) 
    {
        for (int z = 0; z < CHUNK_SIZE; ++z)
        {
            for (int y = 0; y < CHUNK_SIZE; ++y)
            {
                if (blocks[x + y * CHUNK_SIZE + z * CHUNK_SIZE * CHUNK_SIZE])
                {
                    // Calculate world position for this voxel
                    const glm::vec3 voxelWorldPos = chunkWorldPos +
                        glm::vec3(x * voxelDist, y * voxelDist, z * voxelDist);

                    for (int i = 0; i < 6; ++i)
                    {
                        if (shouldRenderFace(x, y, z, i))
                        {
                            for (int j = 0; j < 4; ++j)
                            {
                                int baseIndex = i * 4 + j;

                                vertices.emplace_back(
                                    voxel.c_vertices[baseIndex * 4] + voxelWorldPos.x,
                                    voxel.c_vertices[baseIndex * 4 + 1] + voxelWorldPos.y,
                                    voxel.c_vertices[baseIndex * 4 + 2] + voxelWorldPos.z,
                                    voxel.c_vertices[baseIndex * 4 + 3]
                                );
                                //glm::vec4 vertexData(
                                //    voxel.c_vertices[baseIndex * 4],
                                //    voxel.c_vertices[baseIndex * 4 + 1],
                                //    voxel.c_vertices[baseIndex * 4 + 2],
                                //    voxel.c_vertices[baseIndex * 4 + 3]
                                //);

                                //glm::vec3 cubePos = glm::vec3(vertexData) +
                                //    glm::vec3(x * voxelDist, y * voxelDist, z * voxelDist);

                                //vertices.push_back(glm::vec4(cubePos, vertexData.w));

                            }

                            for (int k = 0; k < 6; ++k)
                            {
                                indices.push_back(faceIndices[i][k] % 4 + vertexOffset);
                            }
                            vertexOffset += 4;
                        }
                    }
                }
            }
        }
    }

    vertexSize = vertices.size() * sizeof(glm::vec4);
    indexCount = indices.size();
}

void Chunk::setupBuffers()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec4), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    //position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);
    glEnableVertexAttribArray(0);

    //lighting/color attribute
    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

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
}