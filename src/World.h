#pragma once
#include <array>
#include <map>
#include <functional>
#include <unordered_map>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "vendor/imgui/imgui.h"
#include "Voxel.h"   
#include "Chunk.h"
#include "Renderer.h"
#include "Camera.h"

struct Vec3Hash {
    std::size_t operator()(const glm::vec3& vec) const {
        return std::hash<float>()(vec.x) ^ (std::hash<float>()(vec.y) << 1) ^ (std::hash<float>()(vec.z) << 2);
    }
};

class World {
public:
    World();
    World(Camera& camera, Renderer& renderer) ;

    enum { OUTSIDE, INTERSECT, INSIDE };
    glm::vec4 planes[6];
    //void addCube(const Quad& quad);
    void loadChunk();
    void unloadChunk();

    void render(float aspectRatio);

    void update(glm::vec3 newColor);

    void setChunkNum(int value);
    void setChunkSize(int value);

    void calculateFrustumPlanes(glm::mat4& projectionViewMatrix);
    int isPointInFrustum(const glm::vec3& point) const;

    float deltaTime;
    float lastFrame; 
    bool rotationState;

private:
    std::vector<Chunk> chunks;
    //std::unordered_map<glm::vec3, Chunk, Vec3Hash> chunks;

    Voxel voxel;
    Camera* m_camera;
    Renderer* m_renderer;
    glm::vec3 newColor;
    float rotationAngle;
    int numChunks;
    int numCubes;

};
