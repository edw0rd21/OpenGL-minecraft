#pragma once

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
    World(Camera& camera, Renderer& renderer) ;


    //void addCube(const Quad& quad);

    void render(float aspectRatio);

    void update(glm::vec3 newColor);

    float deltaTime;
    float lastFrame;

private:
    Quad quad;
    Camera* m_camera;
    Renderer* m_renderer;

    float rotationAngle;

};
