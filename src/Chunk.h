#pragma once

#include <glm/glm.hpp>

#include "Voxel.h"

class Chunk
{
public:
	Chunk();
	~Chunk();

	glm::vec3 position;
	float height;
	glm::vec3 color = glm::vec3(0.0f, 1.0f, 1.0f);
	std::vector<Voxel> voxels;

	std::vector<glm::vec3> vertices; 
	std::vector<unsigned int> indices; 
	GLsizeiptr vertexSize;
	std::size_t indexCount;
	GLuint chunkVAO = 0, chunkVBO = 0 , chunkEBO = 0;

	void genChunkData();
	void setChunkSize(int value);
	int getChunkSize();

	void setupBuffers();

private:
	Voxel voxel;
	int CHUNK_SIZE = 5;
	int voxelDist;
};

