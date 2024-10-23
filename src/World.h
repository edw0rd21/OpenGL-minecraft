#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "vendor/imgui/imgui.h"
#include "Voxel.h"   
#include "Chunk.h"
#include "Renderer.h"
#include "Camera.h"


class World {
public:
    World();
    World(Camera& camera, Renderer& renderer) ;

    enum { OUTSIDE, INTERSECT, INSIDE };
    glm::vec4 planes[6];
    void loadVoxel();
    void loadChunk();
    void unloadChunk();

    void render(float aspectRatio);

    void update();

    Voxel& getVoxel();
    void setChunkNum(int value);
    void setChunkSize(int value);
    void setVoxelColor(glm::vec3 newColor);

    float deltaTime;
    float lastFrame; 
    bool rotationState;
    void setVoxelDist(float value);

private:
    Chunk chunk;
    std::vector<Chunk> chunks;
    //std::unordered_map<glm::vec3, Chunk, Vec3Hash> chunks;

    Voxel voxel;
    Camera* m_camera;
    Renderer* m_renderer;
    glm::vec3 newColor;
    glm::vec3 previousPos, previousFront;
    float rotationAngle;
    int numChunks;
    int numCubes;
    int voxelDist;

    void calculateFrustumPlanes(glm::mat4& projectionViewMatrix);
    int isChunkInFrustum(const Chunk& chunk) const;
    int isPointInFrustum(const glm::vec3& point) const;
};
