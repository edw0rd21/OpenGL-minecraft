#pragma once


#include <chrono>

#include <glm/glm.hpp>
#include <unordered_map>
#include "Voxel.h"
#include "Shader.h"

#include <FastNoiseLite.h>

class Chunk
{
public:
	Chunk();
	~Chunk();

	glm::vec3 position;
	std::vector<int> heightMap;
	glm::vec3 color = glm::vec3(0.0f, 1.0f, 1.0f);
	std::vector<Voxel> voxels;
	std::vector<bool> blocks;

	std::vector<glm::vec4> vertices; 
	std::vector<unsigned int> indices; 
	GLsizeiptr vertexSize;
	std::size_t indexCount;

	void generateHeightmap(const FastNoiseLite& noise);
	void populateBlocks();
	void generateMesh();
	void setChunkSize(int value);
	int getChunkSize();

	GLuint VAO, VBO, EBO; 
	void setupBuffers();

private:
	Voxel voxel;
	int CHUNK_SIZE = 16;
	int voxelDist = voxel.getvoxelDist();
	Shader shader;
	std::vector<int> heightmap;
	bool isBlockAt(int x, int y, int z) const;
	bool shouldRenderFace(int x, int y, int z, int faceIndex) const;

};

