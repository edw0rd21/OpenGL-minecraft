#pragma once
#include "Voxel.h"

struct Chunk
{
	glm::vec3 position;
	std::vector<Voxel> voxels;
};
