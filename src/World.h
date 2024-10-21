#pragma once
#include <array>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "vendor/imgui/imgui.h"
#include "Quad.h"   
#include "Renderer.h"
#include "Camera.h"

class World {
public:
    World();
    World(Camera& camera, Renderer& renderer, Quad& quad) ;

    enum { OUTSIDE, INTERSECT, INSIDE };
    glm::vec4 planes[6];
    //void addCube(const Quad& quad);
    void loadChunk();
    void unloadChunk();

    void render(float aspectRatio);

    void update(glm::vec3 newColor);

    void setChunkSize(int value);
    void calculateFrustumPlanes(glm::mat4& projectionViewMatrix);
    int isPointInFrustum(const glm::vec3& point) const;

    float deltaTime;
    float lastFrame; 
    bool rotationState;

private:
    std::vector<glm::vec3> cubePositions;

    Quad* m_quad;
    Camera* m_camera;
    Renderer* m_renderer;
    glm::vec3 newColor;
    float rotationAngle;
    int chunkSize;

};
